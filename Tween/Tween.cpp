#include "Tween.h"
#include "ValueUnit.h"
#include "Vector2Unit.h"
#include "Vector3Unit.h"

std::list<TweenUnit*>Tween::m_Units;

void Tween::Add(TweenUnit* unit) {
	//�v�f�̈�ԉ��ɒǉ�
	m_Units.push_back(unit);
}

void Tween::Update(float delta_time) {
	//�S�Ă�TweenUnit�̍X�V����������
	for (TweenUnit* unit : m_Units) {
		unit->Update(delta_time);
	}
	//�I������TweenUnit�͍폜
	for (auto itr = m_Units.begin(); itr != m_Units.end();) {
		if ((*itr)->IsFinished()){
			//���g��TweenUnit��delete���Ă���
			delete* itr;
			//���X�g�̗v�f���폜
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
	Add(unit);             //���X�g�ɉ����ĊǗ��Ώۂɂ���
	return *unit;          //TwennUnit�̎Q�Ƃ�ԋp
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
	//�S�Ă̍��ڂ𑖍����āA���O����v�������̂��폜
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