#ifndef AVOID_COLLIDER_H_
#define AVOID_COLLIDER_H_

#include "Actor/Actor.h"

//回避判定
class AvoidCollider : public Actor {
public:

	//デフォルトコンストラクタ
	AvoidCollider() = default;
	//更新
	virtual void Update(float delta_time)override;
	//描画
	virtual void Draw() const override;
	//衝突リアクション
	virtual void React(Actor& other)override;

public:

	//回避したか
	bool CanAvoid()const;

protected:
	//攻撃判定を出現させたアクタータグ
	std::string m_OwnerTag = "";
	//寿命
	float m_LifespanTimer = 60.0f;
	//衝突判定が有効になるまでの遅延時間
	float m_DelayTimer = 0.0f;
	//回避できるか
	bool m_CanAvoid = true;
};

#endif