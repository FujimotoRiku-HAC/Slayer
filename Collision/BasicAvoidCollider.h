#ifndef BASIC_AVOID_COLLIDER_H_
#define BASIC_AVOID_COLLIDER_H_

#include "AvoidCollider.h"

//通常の攻撃クラス
class BasicAvoidCollider : public AvoidCollider {
public:

	//コンストラクタ
	BasicAvoidCollider(
		IWorld* world,
		const BoundingSphere& collider,
		const float lifetime);
	//更新
	void Update(float delta_time)override;
	//描画
	void Draw()const override;
	//リアクション
	void React(Actor& other)override;
};

#endif