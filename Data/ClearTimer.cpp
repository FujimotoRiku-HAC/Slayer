#include "ClearTimer.h"

void ClearTimer::Update(float delta_time){
	m_Timer += delta_time;

	//60�t���[����������
	if (m_Timer >= 60.f) {
		//�J�E���g�A�b�v
		m_Seconds++;
		m_Timer = 0.0f;
	}
	if (m_Seconds >= 60.f) {
		//�J�E���g�A�b�v
		m_Minutes++;
		m_Seconds = 0.0f;
	}
}

void ClearTimer::TimeDataSave(){
	std::ofstream filepath;
	filepath.open("Assets/Data/time_data.txt");

	filepath << m_Minutes << std::endl;
	filepath << m_Seconds << std::endl;

	filepath.close();
}
