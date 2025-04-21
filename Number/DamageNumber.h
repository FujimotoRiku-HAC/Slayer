#ifndef DAMAGE_NUMBER_H_
#define DAMAGE_NUMBER_H_

#include "Number.h"

class DamageNumber : public Number {
public:

	//�R���X�g���N�^
	DamageNumber(const GSvector3& position, const int damage, const float time);
	//�X�V
	void Update(float delta_time)override;
	//�`��
	void Draw()const override;

private:

	//�|�W�V����
	GSvector2 m_DrawPos = GSvector2::zero();
	//�^�C�}�[
	float m_Timer = 0.0f;
	//�l
	int m_Value = 0;
};

#endif