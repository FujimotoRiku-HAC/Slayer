#include "OptionScene.h"
#include "SceneManager.h"

OptionScene::~OptionScene(){
	delete m_BGMSlider;
	delete m_SESlider;
}

void OptionScene::Start(){
	//終了フラグ初期化
	ResetFrag();

	m_Data.DataLoad(			"Data/config_data.txt");
	gsLoadTexture(Option_Text,	"Assets/Texture/UI/Option/option_text.png");

	//音量取得
	m_BGMValue = m_Data.GetBGMValue();
	m_SEValue = m_Data.GetSEValue();

	m_BGMSlider = new Slider(BGMSliderPos, BGMSliderValue, 0.f, 1.f, BGMSliderColor);
	m_SESlider = new Slider(SESliderPos, SESliderValue, 0.f, 1.f, SESliderColor);

	m_Field = Field::BGM;

	gsPauseBGM();
}

void OptionScene::Update(float delta_time){
	switch (m_Field) {
	case OptionScene::BGM:
		m_Rect = OptionBGMRect;
		BGMUpdate(delta_time);
		break;
	case OptionScene::SE:
		m_Rect = OptionSERect;
		SEUpdate(delta_time);
		break;
	case OptionScene::Back:
		m_Rect = OptionReturnRect;
		BackUpdate(delta_time);
		break;
	default:
		break;
	}
	m_BGMValue = CLAMP(m_BGMValue, 0.f, 1.f);
	m_SEValue  = CLAMP( m_SEValue, 0.f, 1.f);
	//音量セット
	m_BGMSlider->SetValue(m_BGMValue);
	m_SESlider->SetValue(m_SEValue);

}

void OptionScene::Draw() const{
	GSrect rect{ 0.0f,0.0f,OptionTextScale.x,OptionTextScale.y };
	//シーン名描画
	gsDrawSprite2D(Option_Text, &SceneName, &rect, NULL, NULL, NULL, NULL);
	//オプションテキスト描画
	rect = { 0.0f,OptionTextScale.y,OptionTextScale.x,OptionTextScale.y * 2 };
	GSvector2 pos{ SceneName.x,OptionTextPos.y };
	for (int i = 0; i < OptionTextFieldNum; ++i) {
		gsDrawSprite2D(Option_Text, &pos, &rect, NULL, NULL, NULL, NULL);
		rect.top += OptionTextScale.y;
		rect.bottom += OptionTextScale.y;
		pos.y += OptionBlankScale;
	}
	gsDrawSprite2D(Option_Text, &OptionReturnScale, &rect, NULL, NULL, NULL, NULL);
	//スライダーの描画
	m_SESlider->Draw();
	m_BGMSlider->Draw();

	gsDrawRectangle2D(&m_Rect, &SelectColor);
}

bool OptionScene::IsEnd() const{
	return m_IsEnd;
}

bool OptionScene::StackClear() const{
	return false;
}

void OptionScene::ResetFrag(){
	m_IsEnd = false;
}

int OptionScene::Next() const{
	return (int)SceneManager::EachScene::Revert;
}

void OptionScene::End(){
	gsSetVolumeBGM(m_BGMValue);
	gsSetMasterVolumeSE(m_SEValue);
	m_Data.DataSave("Data/config_data.txt", m_BGMValue, m_SEValue);
	gsRestartBGM();
}

bool OptionScene::IsGameEnd() const{
	return false;
}

void OptionScene::BGMUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveLeft)) {
		gsPlaySE(Change_SE);
		m_BGMValue -= OptionSliderValue * delta_time;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveRight)) {
		gsPlaySE(Change_SE);
		m_BGMValue += OptionSliderValue * delta_time;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Field = Field::Back;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Field = Field::SE;
		return;
	}
}

void OptionScene::SEUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveLeft)) {
		gsPlaySE(Change_SE);
		m_SEValue -= OptionSliderValue * delta_time;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveRight)) {
		gsPlaySE(Change_SE);
		m_SEValue += OptionSliderValue * delta_time;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Field = Field::BGM;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Field = Field::Back;
		return;
	}
}

void OptionScene::BackUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsEnd = true;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Field = Field::BGM;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Field = Field::SE;
		return;
	}
}
