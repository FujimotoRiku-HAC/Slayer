#include "Vector3Unit.h"

Vector3Unit::Vector3Unit(const GSvector3& from,const GSvector3& to,float duration,
	std::function<void(const GSvector3&)>update_func) :
	TweenUnit{duration},
	m_From{from},
	m_To{to},
	m_UpdateFunc{update_func}{ 
}

void Vector3Unit::OnUpdate(float progress) {
	m_UpdateFunc(LERP(progress, m_From, m_To));
}