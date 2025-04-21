#ifndef VECTOR3_UNIT_H_
#define VECTOR3_UNIT_H_

#include "TweenUnit.h"

//Vector3で動かすためのClass
class Vector3Unit : public TweenUnit {
public:
	//コンストラクタ
	Vector3Unit(const GSvector3& from, const GSvector3& to, float duration,
		std::function<void(const GSvector3&)> update_func);
	//更新時の処理
	virtual void OnUpdate(float progress)override;

private:
	GSvector3 m_From;                               //開始値
	GSvector3 m_To;                                 //終了値
	std::function<void(GSvector3)>m_UpdateFunc;    //更新時の処理
};

#endif