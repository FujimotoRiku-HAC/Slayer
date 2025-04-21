#include "BasicAvoidCollider.h"

BasicAvoidCollider::BasicAvoidCollider(IWorld* world, const BoundingSphere& collider,float lifetime){
	//ワールド設定
	m_World = world;
	//タグ名設定
	m_Tag = st_AvoidTag;
	//親のタグ名設定
	m_OwnerTag = st_Enemy;
	//名前設定
	m_Name = st_Avoid;
	//寿命
	m_LifespanTimer = lifetime;
	//弾の初期化
	m_Collider = { BoundingSphere(collider.m_Radius) };
	//座標初期化
	m_Transform.position(collider.m_Center);
	//衝突判定無効
	m_EnableCollider = false;
}

void BasicAvoidCollider::Update(float delta_time){
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

void BasicAvoidCollider::Draw() const{}

void BasicAvoidCollider::React(Actor& other){
	//自分と同じタグまたは、オーナーと同じタグは衝突判定しない
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
}
