#include "Slider.h"

Slider::Slider(const GSvector2& pos, const GSvector2& scale, float min, float max, const GScolor& color)
	:m_Scale(scale), m_MaxScale(scale), m_Min(min), m_Max(max) {
	m_Position = pos;
	m_Value = 1.f;
	m_Color = color;
	m_Scale.x = m_Value * m_MaxScale.x;
}

Slider::Slider(const GSvector3& pos, const GSvector2& scale, float min, float max, const GScolor& color)
	: m_Scale(scale),m_MaxScale(scale),m_Min(min),m_Max(max){
	gsCalculateScreen(&m_Position, &pos);
	m_Value = 1.f;
	m_Color = color;
	m_Scale.x = m_Value * m_MaxScale.x;
}

Slider::~Slider(){}

void Slider::Draw() const{
	GSrect rect = {
		m_Position.x - 2.f,
		m_Position.y - 2.f,
		m_Position.x + m_MaxScale.x + 2.f,
		m_Position.y + m_MaxScale.y + 2.f };
	GScolor frame_color = { 0.f,0.f,0.f,1.f };
	//内側
	gsDrawRectangle2D(&rect, &frame_color);
	//外側
	rect = { m_Position.x,m_Position.y,m_Position.x + m_Scale.x,m_Position.y + m_Scale.y };
	gsDrawRectangle2D(&rect, &m_Color);
}

void Slider::SetValue(float value){
	m_Value = CLAMP(value, m_Min, m_Max);
	//スケールの計算
	m_Scale.x = m_Value / m_Max * m_MaxScale.x;
}

void Slider::SetPos(GSvector3& pos){
	gsCalculateScreen(&m_Position, &pos);
}

float Slider::GetValue() const{
	return m_Value;
}
