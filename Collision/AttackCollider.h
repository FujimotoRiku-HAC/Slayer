#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_

#include "Actor/Actor.h"

//攻撃判定
class AttackCollider : public Actor {
public:

	//デフォルトコンストラクタ
	AttackCollider() = default;
	//更新
	virtual void Update(float delta_time)override;
	//描画
	virtual void Draw() const override;
	//衝突リアクション
	virtual void React(Actor& other)override;

public:

	//ダメージ量
	int DamageValue()const;
	//スタンダメージ
	int StanPointValue()const;

protected:
	//攻撃判定を出現させたアクタータグ
	std::string m_OwnerTag = "";
	//寿命
	float m_LifespanTimer = 60.0f;
	//衝突判定が有効になるまでの遅延時間
	float m_DelayTimer = 0.0f;
	//ダメージ量
	int m_Damage = 1;
	//スタン量
	int m_StanValue = 1;
};

#endif