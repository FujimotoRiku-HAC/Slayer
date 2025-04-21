#ifndef DAMAGE_NUMBER_H_
#define DAMAGE_NUMBER_H_

#include "Number.h"

class DamageNumber : public Number {
public:

	//コンストラクタ
	DamageNumber(const GSvector3& position, const int damage, const float time);
	//更新
	void Update(float delta_time)override;
	//描画
	void Draw()const override;

private:

	//ポジション
	GSvector2 m_DrawPos = GSvector2::zero();
	//タイマー
	float m_Timer = 0.0f;
	//値
	int m_Value = 0;
};

#endif