#ifndef BASIC_AVOID_COLLIDER_H_
#define BASIC_AVOID_COLLIDER_H_

#include "AvoidCollider.h"

//�ʏ�̍U���N���X
class BasicAvoidCollider : public AvoidCollider {
public:

	//�R���X�g���N�^
	BasicAvoidCollider(
		IWorld* world,
		const BoundingSphere& collider,
		const float lifetime);
	//�X�V
	void Update(float delta_time)override;
	//�`��
	void Draw()const override;
	//���A�N�V����
	void React(Actor& other)override;
};

#endif