#ifndef OPTION_SCENE_H_
#define OPTION_SCENE_H_

#include "IScene.h"
#include "UI/Slider.h"
#include "Data/OptionData.h"
#include "Fade.h"

class OptionScene : public IScene {
public:

	//デストラクタ
	~OptionScene();
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
	void ResetFrag()override;
	//次のシーンを返す
	virtual int Next()const override;
	//終了
	virtual void End() override;
	//ゲーム終了か
	virtual bool IsGameEnd()const override;

private:

	//BGMバーの更新
	void BGMUpdate(float delta_time);
	//SEバーの更新
	void SEUpdate(float delta_time);
	//戻るボタン処理
	void BackUpdate(float delta_time);

private:

	enum Field{
		BGM,
		SE,
		Back
	};

private:

	//フェード
	Fade m_Fade;
	//データ
	OptionData m_Data;
	//BGMスライダー
	Slider* m_BGMSlider;
	//SEスライダー
	Slider* m_SESlider;
	//Rect
	GSrect m_Rect;
	//Pos
	GSvector2 m_Pos;
	//フィールド
	Field m_Field = Field::BGM;
	//BGMの値
	float m_BGMValue{ 1.0f };
	//SEの値
	float m_SEValue{ 1.0f };

	//終了処理
	bool m_IsEnd{ false };
	bool m_IsSelect{ false };
};

#endif