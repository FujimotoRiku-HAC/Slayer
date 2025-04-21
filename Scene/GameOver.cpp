#include "GameOver.h"
#include "SceneManager.h"

void GameOver::Start(){
	gsLoadTexture(Over_Text, "Assets/Texture/UI/GameOver/over_text.png");

	ResetFrag();
}

void GameOver::Update(float delta_time){
	switch (m_Field)
	{
	case GameOver::GameStart:
		RetryUpdate(delta_time);
		break;
	case GameOver::Title:
		TitleUpdate(delta_time);
		break;
	case GameOver::Return:
		EndUpdate(delta_time);
		break;
	default:
		break;
	}
}

void GameOver::Draw() const{
	GSvector2 pos{ ScreenWidth / 2,ScreenHeight / 2 };
	GSrect rect = { 0.f,0.f,GameOverRect.x,GameOverRect.y };
	GScolor color{ 1.f,1.f,1.f,1.0f };

	//ゲームオーバー描画
	GSvector2 over_pos = pos - OverPos;
	gsDrawSprite2D(Over_Text, &over_pos, &rect, NULL, NULL, NULL, NULL);

	rect = { 0.f,GameOverRect.y,GameOverRect.x,GameOverRect.y + GameOverRect.y };
	pos = { ScreenWidth / 2 - OverTextPos.x ,ScreenHeight / 2 + OverTextPos.y };
	//テキスト描画
	for (int i = 0; i < OverTextNum; ++i) {
		if (i == m_Field)color = { 0.f,0.f,1.f,1.f };
		else color = { 1.f,1.f,1.f,1.0f };
		gsDrawSprite2D(Over_Text, &pos, &rect, NULL, &color, NULL, NULL);
		rect.top += GameOverRect.y;
		rect.bottom += GameOverRect.y;
		pos.y += OverTextShiftPos;
	}
	gsDrawRectangle2D(&m_Rect, &SelectColor);
}

bool GameOver::IsEnd() const{
	return m_IsEnd;
}

bool GameOver::StackClear() const{
	return m_IsClear;
}

void GameOver::ResetFrag(){
	m_IsClear = false;
	m_IsEnd = false;
	m_IsGameEnd = false;
}

int GameOver::Next() const{
	return m_NextScene;
}

void GameOver::End(){}

bool GameOver::IsGameEnd() const{
	return m_IsGameEnd;
}

void GameOver::RetryUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Field = Field::Title;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_NextScene = (int)SceneManager::EachScene::Load;
		m_IsEnd = true;
	}
}

void GameOver::TitleUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Field = Field::Return;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Field = Field::GameStart;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_NextScene = (int)SceneManager::EachScene::Title;
		m_IsEnd = true;
	}
}

void GameOver::EndUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Field = Field::Title;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsGameEnd = true;
	}
}
