#ifndef TARGET_H_
#define TARGET_H_

#include "Actor/Actor.h"

class Target : public Actor {
public:

	//コンストラクタ
	Target();
	//更新
	void Update(float delta_time)override;
	//GUI描画
	void DrawGui()const override;
	//メッセージ処理
	void HandleMessage(const std::string& message, void* param)override;

public:

	//ターゲット画像描画
	void TargetDraw(const GSvector3& pos);
	void TargetDraw(Actor* owner);

private:
	Actor* m_Owner{ nullptr };					//オーナー
	GSvector2 m_DrawPos = GSvector2::zero();	//位置
	GSvector2 m_Center = GSvector2::zero();		//中心
	float m_LifeTimer = 0.0f;					//寿命
	bool m_IsDraw = false;						//描画するか
};

#endif