#ifndef NUMBER_MANAGER_H_
#define NUMBER_MANAGER_H_

class Number;

class NumberManager {
public:
	//デフォルトコンストラクタ
	NumberManager() = default;
	//デストラクタ
	~NumberManager();
	//追加
	void Add(Number* number);
	//更新
	void Update(float delta_time);
	//アクターの描画
	void Draw()const;
	//死亡しているアクターの削除
	void Remove();
	//消去
	void Clear();
	// コピー禁止
	NumberManager(const NumberManager& other) = delete;
	NumberManager& operator = (const NumberManager& other) = delete;

private:
	// アクターリスト
	std::list<Number*> m_Numbers;
};

#endif