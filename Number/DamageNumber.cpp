#include "DamageNumber.h"

const float ShakeValue{ 0.5f };

DamageNumber::DamageNumber(const GSvector3& position, const int damage, const float time):
	m_Value(damage),m_Timer(time){
	
	GSvector3 pos = position;
	pos.x += gsRandf(-ShakeValue, ShakeValue);
	pos.y += gsRandf(-ShakeValue, ShakeValue);
	pos.z += gsRandf(-ShakeValue, ShakeValue);

	gsCalculateScreen(&m_DrawPos, &pos);
	m_Number = { Num_Texture,32,32 };

}

void DamageNumber::Update(float delta_time){
	if (m_Timer <= 0.f) {
		Die();
		return;
	}

	m_Timer -= delta_time;
}

void DamageNumber::Draw() const{
	m_Number.Draw(m_DrawPos, m_Value, 1);
}
