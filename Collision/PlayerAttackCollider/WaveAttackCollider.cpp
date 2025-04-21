#include "WaveAttackCollider.h"
#include "Character/Player/Player.h"
#include "Math/Line.h"
#include "Field/Field.h"

const float LifeSpan{ 60.0f * 5.0f };
const float Speed{ 1.5f };

WaveAttackCollider::WaveAttackCollider(IWorld* world,const BoundingSphere& collider, const GSvector3& velocity, int damage,int stan_damage, std::string name) {
	//ワールド設定
	m_World = world;
	//タグ設定
	m_Tag = st_PlayerAttackTag;
	//名前設定
	m_Name = name;
	//ディレイ
	m_DelayTimer = 0.f;
	//ダメージ量
	m_Damage = damage;
	//スタンポイント
	m_StanValue = stan_damage;
	//寿命
	m_LifespanTimer = LifeSpan;
	//コライダ―の大きさ設定
	m_Collider = BoundingSphere{ collider.m_Radius };
	//初期位置
	m_Transform.position(collider.m_Center);
	//移動量設定
	m_Velocity = velocity;
	//回転させる
	m_Transform.rotation(GSquaternion::lookRotation(velocity));
	//エフェクト
	m_EffectHandle = gsPlayEffect(Effect_Arrow, &collider.m_Center);
}

void WaveAttackCollider::Update(float delta_time){
	if (m_LifespanTimer <= 0.f) {
		gsStopEffect(m_EffectHandle);
		Die();
		return;
	}
	//寿命を減算
	m_LifespanTimer -= delta_time;

	//フィールドとの衝突判定
	Line line;
	line.start = m_Transform.position();
	line.end = m_Transform.position() + m_Velocity * delta_time;
	GSvector3 intersect;
	//フィールドに当たったら死亡
	if (m_World->GetField()->Collide(line, &intersect)) {
		m_Transform.position(intersect);
		gsStopEffect(m_EffectHandle);
		Die();
		return;
	}

	m_Transform.translate(m_Velocity * delta_time, GStransform::Space::World);
	// エフェクトに自身のワールド変換行列を設定
	GSmatrix4 world = m_Transform.localToWorldMatrix();
	gsSetEffectMatrix(m_EffectHandle, &world); // ワールド変換行列を設定
}

void WaveAttackCollider::Draw() const{}


void WaveAttackCollider::React(Actor& other) {
	gsStopEffect(m_EffectHandle);
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
	Die();
}
