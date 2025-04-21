#include "Fade.h"

//Å‘å’l
const float Max{ 1.5f };
//Å¬’l
const float Min{ 0.0f };

Fade::Fade(float speed) :
	m_Speed{ speed } {
}

void Fade::Draw()const {
	//ƒ|ƒŠƒSƒ“ì¬
	GSrect rect = { 0,0,ScreenWidth,ScreenHeight };
	GScolor color = { 0,0,0,m_Alpha };
	gsDrawRectangle2D(&rect, &color);
}

void Fade::SetSpeed(float speed) {
	m_Speed = speed;
}

bool Fade::FadeIn(float delta_time){
	m_Alpha += m_Speed * delta_time;
	m_Alpha = std::max(m_Alpha, 0.f);
	return m_Alpha < Max;
}

bool Fade::FadeOut(float delta_time){
	m_Alpha -= m_Speed * delta_time;
	m_Alpha = std::min(m_Alpha, 1.f);
	return m_Alpha > Min;
}

float Fade::GetAlpha()const {
	return m_Alpha;
}