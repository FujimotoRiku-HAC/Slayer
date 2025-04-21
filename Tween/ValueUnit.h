#ifndef VALUE_UNIT_H_
#define VALUE_UNIT_H_

#include "TweenUnit.h"

//値(float型)を動かすためのTweenUnit
class ValueUnit : public TweenUnit {
public:
	//コンストラクタ
	ValueUnit(float from, float to, float duration, std::function<void(float)> update_func);
	//更新時の処理
	virtual void OnUpdate(float progress) override;

private:
	float m_From;                               //開始値
	float m_To;                                 //終了値
	std::function<void(float)> m_UpdateFunc;   //更新時の処理
};

#endif // !VALUE_UNIT_H_
