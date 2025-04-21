#ifndef LOAD_SCENE_H_
#define LOAD_SCENE_H_

#include "IScene.h"

class LoadScene : public IScene {
public:

	//開始
	virtual void Start() override;
	//更新
	virtual void Update(float delta_time) override;
	//描画
	virtual void Draw() const override;
	//終了しているか
	virtual bool IsEnd() const override;
	//シーン削除
	bool StackClear()const override;
	//フラグ初期化
	void ResetFrag() override;
	//次のシーンを返す
	virtual int Next()const override;
	//終了
	virtual void End() override;
	//ゲーム終了か
	virtual bool IsGameEnd()const override;

private:

	//アセットロード
	void AssetsLoad();

private:

	//終了処理
	bool m_IsLoad{ true };
	bool m_IsEnd{ false };
	int m_NextScene{ -1 };
	//タイマー
	int m_Timer{ 0 };
	//回転する
	float m_Angle{ 0 };
};

#endif