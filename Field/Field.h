#ifndef FIELD_H_
#define FIELD_H_

#include "FieldActorManager.h"

class Ray;
class Line;
class BoundingSphere;

//フィールドクラス
class Field {
public:

	//コンストラクタ
	Field(GSuint octree, GSuint collider, GSuint skybox);
	//デストラクタ
	~Field();
	//アクター検索
	Actor* FindActor(const std::string& name) const;

public:

	//更新
	void Update(float delta_time);
	//描画
	void Draw() const;
	//アクター描画
	void DrawActors()const;
	//フィールド用アクターの追加
	void Add(Actor* actor);
	//フィールド用アクターの消去
	void Clear();
	//メッセージ送る
	void HandleMessage(const std::string& message, void* param);

public:

	//線分との衝突判定
	bool Collide(const Line& line,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr,
		Actor** actor = nullptr)const;

	//レイとの衝突判定
	bool Collide(const Ray& ray, float max_distance,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr,
		Actor** actor = nullptr)const;

	//球体との衝突判定
	bool Collide(const BoundingSphere& sphere, GSvector3* center = nullptr,
		Actor** actor = nullptr)const;

	//コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

private:
	//描画用オクトリー
	GSuint m_Octree;
	//衝突判定用オクトリー
	GSuint m_Collider;
	//スカイボックス
	GSuint m_Skybox;
	//アクター
	FieldActorManager m_Actors;
};

#endif
