#ifndef TWEEN_H_
#define TWEEN_H_

#include "TweenUnit.h"

//Tweenモーションを管理するStaticクラス
//複数のTweenモーション管理を行う
class Tween {
public:
	//TweenUnitを追加して管理下に置く
	static void Add(TweenUnit* unit);
	//管理下のTweenUnitの更新を呼び出す
	static void Update(float delta_time);
	//管理下のTweenUnitをすべて削除する
	static void Clear();

	//float型の値をTweenする
	static TweenUnit& Value(float from, float to, float duration,
		std::function<void(float)> update_func);

	//Vector2型の値をTweenする
	static TweenUnit& Vector2(const GSvector2& from, const GSvector2& to, float duration,
		std::function<void(const GSvector2&)>update_func);

	//Vector3型の値をTweenする
	static TweenUnit& Vector3(const GSvector3& from, const GSvector3& to,float duration,
		std::function<void(const GSvector3&)>update_func);

	//指定された時間後に処理を実行
	static TweenUnit& DelayCall(float delay_time, std::function<void()>callback);
	//指定された名前のTweenをキャンセル
	static void Cancel(const std::string& name);

private:
	//インスタンス生成
	Tween() = delete;
	//複数のTweenUnitを管理するためのリスト
	static std::list<TweenUnit*>m_Units;
};

#endif 