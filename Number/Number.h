#ifndef NUMBER_H_
#define NUMBER_H_

#include "NumberTexture.h"

class Number {
public:

	Number() = default;
	//仮想デストラクタ
	virtual ~Number() = default;
	//更新
	virtual void Update(float delta_time) {};
	//描画
	virtual void Draw()const {};

public:

	//死亡する
	void Die();
	//死亡したか
	bool IsDead()const;

protected:
	//ナンバーRect
	NumberTexture m_Number{ 0,16,16 };
	//死亡したか
	bool m_IsDead = false;
};

#endif
