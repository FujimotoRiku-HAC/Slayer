#ifndef VALUE_UNIT_H_
#define VALUE_UNIT_H_

#include "TweenUnit.h"

//�l(float�^)�𓮂������߂�TweenUnit
class ValueUnit : public TweenUnit {
public:
	//�R���X�g���N�^
	ValueUnit(float from, float to, float duration, std::function<void(float)> update_func);
	//�X�V���̏���
	virtual void OnUpdate(float progress) override;

private:
	float m_From;                               //�J�n�l
	float m_To;                                 //�I���l
	std::function<void(float)> m_UpdateFunc;   //�X�V���̏���
};

#endif // !VALUE_UNIT_H_
