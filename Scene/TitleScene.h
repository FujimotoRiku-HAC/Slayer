#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"
#include "Fade.h"
#include "World/World.h"
#include "Animation/AnimatedMesh.h"
#include "Data/OptionData.h"

//タイトルシーン
class TitleScene : public IScene {
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

	//スタート更新
	void StartUpdate(float delta_time);
	//オプション更新
	void OptionUpdate(float delta_time);
	//エンド更新
	void EndUpdate(float delta_time);

private:

	enum TextField {
		GameStart,
		Option,
		GameEnd
	};

private:
	
	//フェード
	Fade m_Fade;
	//ワールド
	World m_World;
	//データ
	OptionData m_Data;
	//メッシュ
	AnimatedMesh m_Mesh{ NULL,NULL,NULL };
	//トランスフォーム
	GStransform m_Transform;
	//テキスト
	TextField m_TextField;
	//Rect
	GSrect m_Rect;

	//終了フラグ
	bool m_IsEnd{ false };
	bool m_IsGameEnd{ false };
	bool m_IsClear{ false };
	int m_NextScene{ -1 };
};

#endif
