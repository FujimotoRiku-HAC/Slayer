#include "FieldActor.h"
#include "Math/Line.h"
#include "Math/Ray.h"
#include "Collision/BoundingSphere.h"

//�`��
void FieldActor::Draw()const {}

//���C�Ƃ̏Փ˔���
bool FieldActor::Collide(const Ray& ray, float max_distance, GSvector3* intersect,
	GSplane* plane)const {
	//���C�̃p�����[�^������ɕϊ�
	Line line;
	line.start = ray.position;
	line.end = ray.position + (ray.direction.normalized() * max_distance);
	//�����Ƃ̏Փ˔�����s��
	return Collide(line, intersect, plane);
}

//�����Ƃ̏Փ˔���
bool FieldActor::Collide(const Line& line, GSvector3* intersect, GSplane* plane)const {
	//���[�J�����W�n�̐��������߂�
	Line local_line;
	local_line.start = m_Transform.inverseTransformPoint(line.start);
	local_line.end = m_Transform.inverseTransformPoint(line.end);
	//���b�V���Ɛ���������������
	if(gsCollisionMeshAndLine(gsGetMesh(m_MeshCollider),&local_line.start,&local_line.end,
		intersect, plane) == GS_TRUE){
			if (intersect != nullptr) {
				//��_�����[���h���W�n�ɕϊ�
				*intersect = m_Transform.transformPoint(*intersect);
			}
			if (plane != nullptr) {
				//���ʂ̕����������[���h���W�n�ɕϊ�
				const GSmatrix4& local_to_world_matrix = m_Transform.localToWorldMatrix();
				gsPlaneTransform(plane, plane, &local_to_world_matrix);
			}
			return true;
		}	
	return false;
}

//���̂Ƃ̏Փ˔���
bool FieldActor::Collide(const BoundingSphere& sphere, GSvector3* collided_center)const {
	//���[�J�����W�n�̋��̂����߂�
	BoundingSphere local_sphere;
	local_sphere.m_Center = m_Transform.inverseTransformPoint(sphere.m_Center);
	local_sphere.m_Radius = sphere.m_Radius;
	//���b�V���Ƃ̋��̂��Փ˂�����
	GSvector3 local_collided_center;
	if (gsCollisionMeshAndSphere(gsGetMesh(m_MeshCollider), &local_sphere.m_Center,
		local_sphere.m_Radius, &local_collided_center) == GS_TRUE) {
		if (collided_center != nullptr) {
			//�Փ˔����̒��S���W�����[���h���W�n�ɕϊ�
			*collided_center = m_Transform.transformPoint(local_collided_center);
		}
		return true;
	}
	return false;
}

TweenUnit& FieldActor::MoveTo(const GSvector3& to, float duration) {
	//���݂̏ꏊ����w�肳�ꂽ�ꏊ�܂�Tween�ňړ�����
	return Tween::Vector3(m_Transform.position(), to, duration,
		[=](GSvector3 pos) {m_Transform.position(pos); });
}