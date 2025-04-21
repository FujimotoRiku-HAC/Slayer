#ifndef FIELD_ACTOR_H_
#define FIELD_ACTOR_H_

#include "Actor/Actor.h"

class Ray;
class Line;
class BoundingSphere;

class FieldActor : public Actor {
public:
	//�t�B�[���h�A�N�^�[�N���X
	virtual void Draw()const override;

	//���C�Ƃ̏Փ˔���
	virtual bool Collide(
		const Ray& ray, float max_distance,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//�����Ƃ̏Փ˔���
	virtual bool Collide(
		const Line& line,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr)const;

	//���̂Ƃ̏Փ˔���
	virtual bool Collide(
		const BoundingSphere& sphere,
		GSvector3* intersect = nullptr)const;

	//�w�肳�ꂽ�ꏊ�܂�Tween�ňړ�����
	TweenUnit& MoveTo(const GSvector3& to, float duration);

protected:

	//���b�V��
	GSuint m_Mesh{ 0 };
	//���b�V���R���C�_
	GSuint m_MeshCollider{ 0 };
};

#endif