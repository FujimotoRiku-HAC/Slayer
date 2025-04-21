#ifndef BASIC_ENEMY_ATTACK_COLLIDER_H_
#define BASIC_ENEMY_ATTACK_COLLIDER_H_

#include "AttackCollider.h"

//�ʏ�̍U���N���X
class BasicEnemyAttackCollider : public AttackCollider {
public:

	//�R���X�g���N�^
	BasicEnemyAttackCollider(
		IWorld* world,						//���[���h
		const BoundingSphere& collider,		//�e
		const std::string& name,			//���O
		const std::string& tag,				//�^�O
		const std::string& owner_tag = "",	//�e�̖��O
		const int damage = 1,				//�_���[�W
		const float lifespan = 1.0f,		//����
		const float delay = 0.0f			//�x������
	);
	//�X�V
	void Update(float delta_time)override;
	//�`��
	void Draw()const override;
	//���A�N�V����
	void React(Actor& other)override;

private:
	bool m_IsGenerate{ false };	//�o��������
};

#endif