#include "Vector2Unit.h"

Vector2Unit::Vector2Unit(const GSvector2& from, const GSvector2& to, float duration,
	std::function<void(const GSvector2&)>update_func) :
	TweenUnit{ duration },
	m_From{ from },
	m_To{ to },
	m_UpdateFunc{ update_func } {
}

void Vector2Unit::OnUpdate(float progress) {
	m_UpdateFunc(LERP(progress, m_From, m_To));
}