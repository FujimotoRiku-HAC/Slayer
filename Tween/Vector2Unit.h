#ifndef VECTOR2_UNIT_H_
#define VECTOR2_UNIT_H_

#include "TweenUnit.h"

//Vector3で動かすためのClass
class Vector2Unit : public TweenUnit {
public:
	//コンストラクタ
	Vector2Unit(const GSvector2& from, const GSvector2& to, float duration,
		std::function<void(const GSvector2&)> update_func);
	//更新時の処理
	virtual void OnUpdate(float progress)override;

private:
	GSvector2 m_From;                               //開始値
	GSvector2 m_To;                                 //終了値
	std::function<void(GSvector2)>m_UpdateFunc;    //更新時の処理
};

#endif