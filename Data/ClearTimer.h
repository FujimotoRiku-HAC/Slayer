#ifndef CLEAR_TIMER_H_
#define CLEAR_TIMER_H_

class ClearTimer {
public:

	//�R���X�g���N�^
	ClearTimer() = default;
	//�X�V
	void Update(float delta_time);
	//�b���̃Z�[�u
	void TimeDataSave();

private:

	float m_Timer;		//�^�C�}�[
	float m_Minutes;	//����
	float m_Seconds;	//�b��
};

#endif