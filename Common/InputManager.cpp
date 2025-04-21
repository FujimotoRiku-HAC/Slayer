#include "InputManager.h"

float InputManager::m_Timer = 0.0f;

const float ReceptionTime{ 30.0f };

InputManager InputManager::Instance(){
    return InputManager();
}

GSvector2 InputManager::LeftAxis(){
	GSvector2 result = GSvector2::zero();

	gsXBoxPadGetLeftAxis(0, &result);

	if (gsGetKeyState(GKEY_W)) result.y =  1.f;
	if (gsGetKeyState(GKEY_A)) result.x = -1.f;
	if (gsGetKeyState(GKEY_S)) result.y =  -1.f;
	if (gsGetKeyState(GKEY_D)) result.x =  1.f;

	return result;
}

GSvector2 InputManager::RightAxis(){
	GSvector2 result = GSvector2::zero();

	gsXBoxPadGetRightAxis(0, &result);

	if (gsGetKeyState(GKEY_UPARROW))    result.x =  1.f;
	if (gsGetKeyState(GKEY_LEFTARROW))  result.y = -1.f;
	if (gsGetKeyState(GKEY_DOWNARROW))  result.x = -1.f;
	if (gsGetKeyState(GKEY_RIGHTARROW)) result.y =  1.f;

	return result;
}

bool InputManager::IsBottonDown(InputType type){
	return gsXBoxPadButtonTrigger(0,m_InputLibrary[type]);
}

bool InputManager::IsBottonState(InputType type){
	return gsXBoxPadButtonState(0, m_InputLibrary[type]);
}

bool InputManager::IsBottonDetach(InputType type){
	return gsXBoxPadButtonDetach(0, m_InputLibrary[type]);
}

bool InputManager::IsBottonShortPress(InputType type){
	return IsBottonPressType(type) == Short;

}

bool InputManager::IsBottonLongPress(InputType type){
	return IsBottonPressType(type) == State;
}

int InputManager::IsBottonPressType(InputType type){
	m_Num = 0;

	//‰Ÿ‚µ‚½uŠÔ
	if (gsXBoxPadButtonTrigger(0, m_InputLibrary[type])) {
		m_Num = 1;
	}
	//‰Ÿ‚µ‚Ä‚µ‚Î‚ç‚­‚½‚Á‚½‚ç
	else if (gsXBoxPadButtonTrigger(0, m_InputLibrary[type])){
		if(m_Timer >= ReceptionTime){
			m_Num = 2;
		}
	}
	//—£‚µ‚½‚ç
	else if (gsXBoxPadButtonDetach(0, m_InputLibrary[type])) {
		//ˆê’èŽžŠÔˆÈ“à‚È‚ç
		m_Num = 3;

		//ˆê’èŽžŠÔ‚ð’´‚¦‚½‚ç
		if (m_Timer < ReceptionTime) {
			m_Num = 4;
		}
		m_Timer = 0.f;
	}
	else {
		return 0;
	}
	m_Timer++;
	return m_Num;
}

InputManager::InputManager() {
	m_InputLibrary[InputType::Decision] =			GS_XBOX_PAD_B;
	m_InputLibrary[InputType::Return] =				GS_XBOX_PAD_A;
	m_InputLibrary[InputType::Delete] =				GS_XBOX_PAD_LEFT_SHOULDER;
	m_InputLibrary[InputType::Pose] =				GS_XBOX_PAD_START;
	m_InputLibrary[InputType::Back] =				GS_XBOX_PAD_BACK;
	m_InputLibrary[InputType::SelectMoveUp] =		GS_XBOX_PAD_UP;
	m_InputLibrary[InputType::SelectMoveDown] =		GS_XBOX_PAD_DOWN;
	m_InputLibrary[InputType::SelectMoveRight] =	GS_XBOX_PAD_RIGHT;
	m_InputLibrary[InputType::SelectMoveLeft] =		GS_XBOX_PAD_LEFT;
	m_InputLibrary[InputType::ResetCamera] =		GS_XBOX_PAD_LEFT_SHOULDER;
	m_InputLibrary[InputType::SkillSelect] =		GS_XBOX_PAD_RIGHT_SHOULDER;
	m_InputLibrary[InputType::Attack] =				GS_XBOX_PAD_X;
	m_InputLibrary[InputType::Avoid] =				GS_XBOX_PAD_A;
	m_InputLibrary[InputType::Ability1] =			GS_XBOX_PAD_B;
	m_InputLibrary[InputType::Ability2] =			GS_XBOX_PAD_Y;
}