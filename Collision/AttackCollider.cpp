#include "AttackCollider.h"

void AttackCollider::Update(float delta_time) {}

void AttackCollider::Draw()const {}

void AttackCollider::React(Actor& other) {}

int AttackCollider::DamageValue() const {
	return m_Damage;
}

int AttackCollider::StanPointValue() const{
	return m_StanValue;
}

