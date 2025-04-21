#ifndef BASIC_ENEMY_ATTACK_COLLIDER_H_
#define BASIC_ENEMY_ATTACK_COLLIDER_H_

#include "AttackCollider.h"

//通常の攻撃クラス
class BasicEnemyAttackCollider : public AttackCollider {
public:

	//コンストラクタ
	BasicEnemyAttackCollider(
		IWorld* world,						//ワールド
		const BoundingSphere& collider,		//弾
		const std::string& name,			//名前
		const std::string& tag,				//タグ
		const std::string& owner_tag = "",	//親の名前
		const int damage = 1,				//ダメージ
		const float lifespan = 1.0f,		//寿命
		const float delay = 0.0f			//遅延時間
	);
	//更新
	void Update(float delta_time)override;
	//描画
	void Draw()const override;
	//リアクション
	void React(Actor& other)override;

private:
	bool m_IsGenerate{ false };	//出現したか
};

#endif