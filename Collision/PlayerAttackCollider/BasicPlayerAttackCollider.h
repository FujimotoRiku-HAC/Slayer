#ifndef BASIC_PLAYER_ATTACK_COLLIDER_H_
#define BASIC_PLAYER_ATTACK_COLLIDER_H_

#include "Collision/AttackCollider.h"

//�ʏ�̍U���N���X
class BasicPlayerAttackCollider : public AttackCollider {
public:

	//�R���X�g���N�^
	BasicPlayerAttackCollider(
		IWorld* world,						//���[���h
		const BoundingSphere& collider,		//�e
		const std::string& name,			//���O
		const std::string& tag,				//�^�O
		const std::string& owner_tag = "",	//�e�̖��O
		const int damage = 1,				//�_���[�W
		const int stan_damage = 1,			//�_���[�W
		const float lifespan = 1.0f,		//����
		const float delay = 0.0f			//�x������
	);
	//�X�V
	void Update(float delta_time)override;
	//�`��
	void Draw()const override;
	//���A�N�V����
	void React(Actor& other)override;

};

#endif