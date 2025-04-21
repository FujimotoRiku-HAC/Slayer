#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include "IScene.h"
#include "World/World.h"
#include "Fade.h"
#include "Assets.h"
#include "Animation/AnimatedMesh.h"
#include "CharacterEdit/SkillEdit.h"
#include "Data/ClearTimer.h"
#include "GameClear.h"

class GamePlayScene : public IScene {
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

	// スポーン
	void SpawnGolem();

private:

	//プレイシーン
	void PlayUpdate(float delta_time);
	//タイトルに戻る
	void TitleUpdate(float delta_time);
	//ゲーム終了
	void EndUpdate(float delta_time);
	//クリア描画
	void GameClearDraw()const;

private:

	enum Text {
		Play,
		TitleReturn,
		EndReturn
	};

private:

	//ワールド
	World m_World;
	//フェード
	Fade m_Fade;
	//タイマー
	ClearTimer m_Timer;
	//クリア
	GameClear m_GameClear;
	//テキスト
	Text m_Text;
	//出現したか
	bool m_IsGenerate{ false };
	//クリアタイマー
	float m_ClearTimer{ 0.0f };

	//終了処理
	bool m_IsEnd{ false };
	bool m_IsClear{ false };
	bool m_IsSceneClear{ false };
	bool m_IsGameEnd{ false };
	int m_NextScene{ 0 };
};

#endif