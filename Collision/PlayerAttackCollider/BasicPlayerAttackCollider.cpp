#include "BasicPlayerAttackCollider.h"

BasicPlayerAttackCollider::BasicPlayerAttackCollider(IWorld* world, const BoundingSphere& collider, const std::string& name, const std::string& tag, const std::string& owner_tag, const int damage,const int stan_damage, const float lifespan, const float delay){
	//ワールド設定
	m_World = world;
	//タグ名設定
	m_Tag = tag;
	//親のタグ名設定
	m_OwnerTag = owner_tag;
	//名前設定
	m_Name = name;
	//ダメージ量
	m_Damage = damage;
	//スタンダメージ量
	m_StanValue = stan_damage;
	//寿命設定
	m_LifespanTimer = lifespan;
	//遅延時間
	m_DelayTimer = delay;
	//弾の初期化
	m_Collider = { BoundingSphere(collider.m_Radius) };
	//座標初期化
	m_Transform.position(collider.m_Center);
	//衝突判定無効
	m_EnableCollider = false;
}

void BasicPlayerAttackCollider::Update(float delta_time){
	//遅延時間が過ぎたら衝突判定を有効にする
	if (m_DelayTimer <= 0.f) {
		m_EnableCollider = true;
		//寿命が尽きたら死亡
		if (m_LifespanTimer <= 0.f) {
			Die();
		}
		//寿命の更新
		m_LifespanTimer -= delta_time;
	}
	//遅延時間の更新
	m_DelayTimer -= delta_time;
}

void BasicPlayerAttackCollider::Draw() const{}

void BasicPlayerAttackCollider::React(Actor& other){
	//自分と同じタグまたは、オーナーと同じタグは衝突しない
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
	Die();
}
