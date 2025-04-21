#ifndef NUMBER_H_
#define NUMBER_H_

#include "NumberTexture.h"

class Number {
public:

	Number() = default;
	//���z�f�X�g���N�^
	virtual ~Number() = default;
	//�X�V
	virtual void Update(float delta_time) {};
	//�`��
	virtual void Draw()const {};

public:

	//���S����
	void Die();
	//���S������
	bool IsDead()const;

protected:
	//�i���o�[Rect
	NumberTexture m_Number{ 0,16,16 };
	//���S������
	bool m_IsDead = false;
};

#endif
