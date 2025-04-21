#include "ValueUnit.h"

ValueUnit::ValueUnit(float from,float to,float duration,std::function<void(float)> update_func) :
	TweenUnit{duration},
	m_From{from},
	m_To{to},
	m_UpdateFunc{update_func}{ }

void ValueUnit::OnUpdate(float progress) {
	m_UpdateFunc(LERP(progress, m_From, m_To));
}