#ifndef CLEAR_TIMER_H_
#define CLEAR_TIMER_H_

class ClearTimer {
public:

	//コンストラクタ
	ClearTimer() = default;
	//更新
	void Update(float delta_time);
	//秒数のセーブ
	void TimeDataSave();

private:

	float m_Timer;		//タイマー
	float m_Minutes;	//分数
	float m_Seconds;	//秒数
};

#endif