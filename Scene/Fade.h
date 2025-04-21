#ifndef FADE_H_
#define FADE_H_

class Fade{
public:

	//コンストラクタ
	Fade(float speed = 0.1f);
	//描画
	void Draw()const;
	//スピード調整
	void SetSpeed(float speed);

public:

	//フェードイン
	bool FadeIn(float delta_time);
	//フェードアウト
	bool FadeOut(float delta_time);

public:

	//アルファ値取得
	float GetAlpha()const;

private:
	//スピード
	float m_Speed{ 0.0f };
	//アルファ値
	float m_Alpha{ 0.0f };
};

#endif