#include "Number.h"

void Number::Die(){
	m_IsDead = true;
}

bool Number::IsDead() const{
	return m_IsDead;
}
