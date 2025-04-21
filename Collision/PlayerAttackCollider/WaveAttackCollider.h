#ifndef WAVE_ATTACK_COLLIDER_
#define WAVE_ATTACK_COLLIDER_

#include "Collision/AttackCollider.h"

class WaveAttackCollider : public AttackCollider {
public:

	//コンストラクタ
	WaveAttackCollider(IWorld* world, const BoundingSphere&collider, const GSvector3& velocity, int damage,int stan_damage, std::string name);
	//更新
	void Update(float delta_time)override;
	//描画
	void Draw()const override;
	//リアクション
	void React(Actor& other)override;

private:

	GSuint m_EffectHandle = NAN;	//エフェクトハンドル
};

#endif