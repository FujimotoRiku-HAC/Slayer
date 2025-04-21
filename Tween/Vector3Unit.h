#ifndef VECTOR3_UNIT_H_
#define VECTOR3_UNIT_H_

#include "TweenUnit.h"

//Vector3�œ��������߂�Class
class Vector3Unit : public TweenUnit {
public:
	//�R���X�g���N�^
	Vector3Unit(const GSvector3& from, const GSvector3& to, float duration,
		std::function<void(const GSvector3&)> update_func);
	//�X�V���̏���
	virtual void OnUpdate(float progress)override;

private:
	GSvector3 m_From;                               //�J�n�l
	GSvector3 m_To;                                 //�I���l
	std::function<void(GSvector3)>m_UpdateFunc;    //�X�V���̏���
};

#endif