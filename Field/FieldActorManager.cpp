#include "FieldActorManager.h"
#include "FieldActor.h"
#include "Math/Line.h"
#include "Math/Ray.h"
#include "Collision/BoundingSphere.h"

//���C�ƃt�B�[���h�p�̃A�N�^�[�Ƃ̏Փ˔���
FieldActor* FieldActorManager::Collide(const Ray& ray, float max_distance, GSvector3*
	intersect, GSplane* plane)const {
	//���C������ɕϊ�
	Line line;
	line.start = ray.position;
	line.end = ray.position * (ray.direction.normalized() * max_distance);
	//�����Ƃ̔�����s��
	return Collide(line, intersect, plane);
}

//�����ƃt�B�[���h�p�̃A�N�^�[�Ƃ̏Փ˔���
FieldActor* FieldActorManager::Collide(const Line& line, GSvector3* intersect, GSplane* plane)const {
	//�ł��n�_����߂��A�N�^�[
	FieldActor* closest_actor{ nullptr };
	//�ł��n�_����߂���_�Ƃ̋���
	float closest_distance = std::numeric_limits<float>::max();
	//�ł��n�_����߂���_
	GSvector3 closest_intersection;
	//�ł��n�_����߂���_�̕���
	GSplane closest_intersection_plane;

	for (auto actor : m_Actors) {
		//�t�B�[���h�A�N�^�[�ł��邩�m�F
		FieldActor* field_actor = dynamic_cast<FieldActor*>(actor);
		//�t�B�[���h�A�N�^�[�łȂ���΃X�L�b�v
		if (field_actor == nullptr)continue;
		//�t�B�[���h�A�N�^�[�Ɛ����Ƃ̌���������s��
		GSvector3 intersection_point;
		GSplane intersection_plane;
		if (field_actor->Collide(line, &intersection_point, &intersection_plane)) {
			//���_����̋������v�Z
			float distance = line.start.distance(intersection_point);
			if (distance < closest_distance) {
				//�������߂��ꍇ�́A�A�N�^�[���X�V
				closest_distance = distance;
				closest_actor = field_actor;
				closest_intersection = intersection_point;
				closest_intersection_plane = intersection_plane;
			}
		}
	}
	//�Փ˂����A�N�^�[�����݂��邩
	if (closest_actor != nullptr) {
		if (intersect != nullptr) {
			*intersect = closest_intersection;
		}
		if (plane != nullptr) {
			*plane = closest_intersection_plane;
		}
	}
	return closest_actor;
}

FieldActor* FieldActorManager::Collide(const BoundingSphere& sphere, GSvector3*
	collided_center)const {
	for (auto actor : m_Actors) {
		//�t�B�[���h�A�N�^�[�ł��邩�m�F
		FieldActor* field_actor = dynamic_cast<FieldActor*>(actor);
		//�t�B�[���h�A�N�^�[�łȂ���΃X�L�b�v
		if (field_actor == nullptr)continue;
		//�t�B�[���h�Ƌ��̂̏Փ˔�����s��
		if (field_actor->Collide(sphere, collided_center)) {
			return field_actor;
		}
	}
	return nullptr;
}