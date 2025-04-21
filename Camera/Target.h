#ifndef TARGET_H_
#define TARGET_H_

#include "Actor/Actor.h"

class Target : public Actor {
public:

	//�R���X�g���N�^
	Target();
	//�X�V
	void Update(float delta_time)override;
	//GUI�`��
	void DrawGui()const override;
	//���b�Z�[�W����
	void HandleMessage(const std::string& message, void* param)override;

public:

	//�^�[�Q�b�g�摜�`��
	void TargetDraw(const GSvector3& pos);
	void TargetDraw(Actor* owner);

private:
	Actor* m_Owner{ nullptr };					//�I�[�i�[
	GSvector2 m_DrawPos = GSvector2::zero();	//�ʒu
	GSvector2 m_Center = GSvector2::zero();		//���S
	float m_LifeTimer = 0.0f;					//����
	bool m_IsDraw = false;						//�`�悷�邩
};

#endif