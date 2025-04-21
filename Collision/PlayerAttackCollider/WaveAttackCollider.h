#ifndef WAVE_ATTACK_COLLIDER_
#define WAVE_ATTACK_COLLIDER_

#include "Collision/AttackCollider.h"

class WaveAttackCollider : public AttackCollider {
public:

	//�R���X�g���N�^
	WaveAttackCollider(IWorld* world, const BoundingSphere&collider, const GSvector3& velocity, int damage,int stan_damage, std::string name);
	//�X�V
	void Update(float delta_time)override;
	//�`��
	void Draw()const override;
	//���A�N�V����
	void React(Actor& other)override;

private:

	GSuint m_EffectHandle = NAN;	//�G�t�F�N�g�n���h��
};

#endif