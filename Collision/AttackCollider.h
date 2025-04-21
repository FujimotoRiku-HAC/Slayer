#ifndef ATTACK_COLLIDER_H_
#define ATTACK_COLLIDER_H_

#include "Actor/Actor.h"

//�U������
class AttackCollider : public Actor {
public:

	//�f�t�H���g�R���X�g���N�^
	AttackCollider() = default;
	//�X�V
	virtual void Update(float delta_time)override;
	//�`��
	virtual void Draw() const override;
	//�Փ˃��A�N�V����
	virtual void React(Actor& other)override;

public:

	//�_���[�W��
	int DamageValue()const;
	//�X�^���_���[�W
	int StanPointValue()const;

protected:
	//�U��������o���������A�N�^�[�^�O
	std::string m_OwnerTag = "";
	//����
	float m_LifespanTimer = 60.0f;
	//�Փ˔��肪�L���ɂȂ�܂ł̒x������
	float m_DelayTimer = 0.0f;
	//�_���[�W��
	int m_Damage = 1;
	//�X�^����
	int m_StanValue = 1;
};

#endif