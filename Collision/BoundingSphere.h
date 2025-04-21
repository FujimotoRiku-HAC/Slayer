#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

//境界球クラス
class BoundingSphere {
public:

	//コンストラクタ
	BoundingSphere(float redius = 0.0f, const GSvector3& center = GSvector3{ 0.0f,0.0f,0.0f });
	//平行移動
	BoundingSphere Translate(const GSvector3& position)const;
	//座標変換
	BoundingSphere Transform(const GSmatrix4& matrix)const;
	//重なっているか
	bool Intersects(const BoundingSphere& other) const;
	//デバッグ表示
	void Draw() const;

public:
	//半径
	float m_Radius{ 0.0f };
	//中心座標
	GSvector3 m_Center{ 0.0f,0.0f,0.0f };
};

#endif