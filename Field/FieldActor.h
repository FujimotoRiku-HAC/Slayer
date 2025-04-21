#ifndef FIELD_ACTOR_H_
#define FIELD_ACTOR_H_

#include "Actor/Actor.h"

class Ray;
class Line;
class BoundingSphere;

class FieldActor : public Actor {
public:
	//フィールドアクタークラス
	virtual void Draw()const override;

	//レイとの衝突判定
	virtual bool Collide(
		const Ray& ray, float max_distance,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//線分との衝突判定
	virtual bool Collide(
		const Line& line,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//球体との衝突判定
	virtual bool Collide(
		const BoundingSphere& sphere,
		GSvector3* intersect = nullptr)const;

	//指定された場所までTweenで移動する
	TweenUnit& MoveTo(const GSvector3& to, float duration);

protected:

	//メッシュ
	GSuint m_Mesh{ 0 };
	//メッシュコライダ
	GSuint m_MeshCollider{ 0 };
};

#endif