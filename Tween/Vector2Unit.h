#ifndef VECTOR2_UNIT_H_
#define VECTOR2_UNIT_H_

#include "TweenUnit.h"

//Vector3�œ��������߂�Class
class Vector2Unit : public TweenUnit {
public:
	//�R���X�g���N�^
	Vector2Unit(const GSvector2& from, const GSvector2& to, float duration,
		std::function<void(const GSvector2&)> update_func);
	//�X�V���̏���
	virtual void OnUpdate(float progress)override;

private:
	GSvector2 m_From;                               //�J�n�l
	GSvector2 m_To;                                 //�I���l
	std::function<void(GSvector2)>m_UpdateFunc;    //�X�V���̏���
};

#endif