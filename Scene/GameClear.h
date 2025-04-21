#ifndef GAME_CLEAR_H_
#define GAME_CLEAR_H_

class GameClear {
public:

	//デフォルトコンストラクタ
	GameClear() = default;
	//デストラクタ
	~GameClear();
	//開始
	void Start();
	//描画
	void Draw()const;

private:

	//時間データの取得
	void LoadTimeData();
	//ランクの計算
	void Calclate();
	//何ランクを描画するか
	void RankBackCalulateDraw(char rank)const;

private:
	//分
	int m_Minutes{ 0 };
	//秒
	int m_Second{ 0 };
	//ランク
	char m_Rank;
	//カラー
	const GScolor m_Color{ 0.f,0.f,0.f,0.7f };
};

#endif
