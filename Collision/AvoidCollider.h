#ifndef AVOID_COLLIDER_H_
#define AVOID_COLLIDER_H_

#include "Actor/Actor.h"

//��𔻒�
class AvoidCollider : public Actor {
public:

	//�f�t�H���g�R���X�g���N�^
	AvoidCollider() = default;
	//�X�V
	virtual void Update(float delta_time)override;
	//�`��
	virtual void Draw() const override;
	//�Փ˃��A�N�V����
	virtual void React(Actor& other)override;

public:

	//���������
	bool CanAvoid()const;

protected:
	//�U��������o���������A�N�^�[�^�O
	std::string m_OwnerTag = "";
	//����
	float m_LifespanTimer = 60.0f;
	//�Փ˔��肪�L���ɂȂ�܂ł̒x������
	float m_DelayTimer = 0.0f;
	//����ł��邩
	bool m_CanAvoid = true;
};

#endif