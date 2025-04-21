#ifndef TWEEN_H_
#define TWEEN_H_

#include "TweenUnit.h"

//Tween���[�V�������Ǘ�����Static�N���X
//������Tween���[�V�����Ǘ����s��
class Tween {
public:
	//TweenUnit��ǉ����ĊǗ����ɒu��
	static void Add(TweenUnit* unit);
	//�Ǘ�����TweenUnit�̍X�V���Ăяo��
	static void Update(float delta_time);
	//�Ǘ�����TweenUnit�����ׂč폜����
	static void Clear();

	//float�^�̒l��Tween����
	static TweenUnit& Value(float from, float to, float duration,
		std::function<void(float)> update_func);

	//Vector2�^�̒l��Tween����
	static TweenUnit& Vector2(const GSvector2& from, const GSvector2& to, float duration,
		std::function<void(const GSvector2&)>update_func);

	//Vector3�^�̒l��Tween����
	static TweenUnit& Vector3(const GSvector3& from, const GSvector3& to,float duration,
		std::function<void(const GSvector3&)>update_func);

	//�w�肳�ꂽ���Ԍ�ɏ��������s
	static TweenUnit& DelayCall(float delay_time, std::function<void()>callback);
	//�w�肳�ꂽ���O��Tween���L�����Z��
	static void Cancel(const std::string& name);

private:
	//�C���X�^���X����
	Tween() = delete;
	//������TweenUnit���Ǘ����邽�߂̃��X�g
	static std::list<TweenUnit*>m_Units;
};

#endif 