#include "Tween.h"
#include "ValueUnit.h"
#include "Vector2Unit.h"
#include "Vector3Unit.h"

std::list<TweenUnit*>Tween::m_Units;

void Tween::Add(TweenUnit* unit) {
	//要素の一番下に追加
	m_Units.push_back(unit);
}

void Tween::Update(float delta_time) {
	//全てのTweenUnitの更新処理をする
	for (TweenUnit* unit : m_Units) {
		unit->Update(delta_time);
	}
	//終了したTweenUnitは削除
	for (auto itr = m_Units.begin(); itr != m_Units.end();) {
		if ((*itr)->IsFinished()){
			//中身のTweenUnitをdeleteしてから
			delete* itr;
			//リストの要素を削除
			itr = m_Units.erase(itr);
		}
		else {
			++itr;
		}
	}
}

void Tween::Clear() {
	for (TweenUnit* tween : m_Units) {
		delete tween;
	}
	m_Units.clear();
}

TweenUnit& Tween::Value(float from, float to, float duration,
	std::function<void(float)>update_func) {
	TweenUnit* unit = new ValueUnit(from, to, duration, update_func);
	Add(unit);             //リストに加えて管理対象にする
	return *unit;          //TwennUnitの参照を返却
}
TweenUnit& Tween::Vector2(const GSvector2& from, const GSvector2& to, float duration,
	std::function<void(const GSvector2&)>update_func) {
	TweenUnit* unit = new Vector2Unit(from, to, duration, update_func);
	Add(unit);
	return *unit;
}

TweenUnit& Tween::Vector3(const GSvector3& from, const GSvector3& to,float duration,
	std::function<void(const GSvector3&)>update_func) {
	TweenUnit* unit = new Vector3Unit(from, to, duration, update_func);
	Add(unit);
	return *unit;
}

TweenUnit& Tween::DelayCall(float delay_time, std::function<void()>callback) {
	TweenUnit* unit = new TweenUnit(delay_time);
	unit->OnComplete(callback);
	Add(unit);
	return *unit;
}

void Tween::Cancel(const std::string& name) {
	//全ての項目を走査して、名前が一致したものを削除
	for (auto itr = m_Units.begin(); itr != m_Units.end();) {
		if ((*itr)->Name() == name) {
			delete* itr;
			itr = m_Units.erase(itr);
		}
		else {
			++itr;
		}
	}
}