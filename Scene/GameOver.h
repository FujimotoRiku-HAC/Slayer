#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include "IScene.h"

class GameOver : public IScene {
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

	//リトライ更新
	void RetryUpdate(float delta_time);
	//タイトル更新
	void TitleUpdate(float delta_time);
	//エンド更新
	void EndUpdate(float delta_time);

private:

	enum Field {
		GameStart,
		Title,
		Return
	};

private:
	//フィールド
	Field m_Field;
	//Rect
	GSrect m_Rect;
	//終了処理
	bool m_IsEnd{ false };
	bool m_IsClear{ false };
	bool m_IsGameEnd{ false };
	int m_NextScene = -1;

};


#endif