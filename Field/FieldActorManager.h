#ifndef FIELD_ACTOR_MANAGER_H_
#define FIELD_ACTOR_MANAGER_H_

#include "Actor/ActorManager.h"

class FieldActor;
class Ray;
class Line;
class BoundingSphere;
struct GSvector3;
struct GSplane;

class FieldActorManager : public ActorManager {
public:
	//���C�̏Փ˔���
	FieldActor* Collide(
		const Ray& ray, float max_distance,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//�����Ƃ̏Փ˔���
	FieldActor* Collide(
		const Line& line,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//���̂Ƃ̏Փ˔���
	FieldActor* Collide(
		const BoundingSphere& sphere,
		GSvector3* collided_center = nullptr)const;
};

#endif 