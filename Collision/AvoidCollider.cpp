#include "AvoidCollider.h"

void AvoidCollider::Update(float delta_time){}

void AvoidCollider::Draw() const{}

void AvoidCollider::React(Actor& other){}

bool AvoidCollider::CanAvoid() const{
	return m_CanAvoid;
}
