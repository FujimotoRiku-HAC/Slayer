#ifndef SLIDER_H_
#define SLIDER_H_

class Slider {
public:

	//コンストラクタ
	Slider(const GSvector2& pos, const GSvector2& scale, float min, float max,
		const GScolor& color = GScolor{ 0.0f,0.0f,0.0f,1.0f });
	Slider(const GSvector3& pos, const GSvector2& scale, float min, float max,
		const GScolor& color = GScolor{ 0.0f,0.0f,0.0f,1.0f });
	//デストラクタ
	~Slider();
	//描画
	void Draw()const;
	//設定
	void SetValue(float value);
	//位置決定
	void SetPos(GSvector3& pos);
	
public:

	//値の取得
	float GetValue()const;

private:
	//位置
	GSvector2 m_Position;
	//カラー
	GScolor m_Color{ 1.0f,1.0f,1.0f,1.0 };
	//スケール
	GSvector2 m_Scale{ 5.0f,1.0f };
	//最大スケール
	GSvector2 m_MaxScale{ m_Scale };
	//最小値
	float m_Min{ 0.0f };
	//最大値
	float m_Max{ 1.0f };
	//値
	float m_Value;

};

#endif