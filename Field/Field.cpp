#include "Field.h"
#include "Math/Ray.h"
#include "Math/Line.h"
#include "Collision/BoundingSphere.h"
#include "FieldActor.h"

Field::Field(GSuint octree, GSuint collider, GSuint skybox) :
	m_Octree{ octree }, m_Collider{ collider }, m_Skybox{ skybox }{
}

Field::~Field() {
	Clear();
}

Actor* Field::FindActor(const std::string& name) const {
	return m_Actors.Find(name);
}

void Field::Update(float delta_time){
	m_Actors.Update(delta_time);
	m_Actors.Remove();
}

void Field::Draw()const {
	//�X�J�C�{�b�N�X
	gsDrawSkyboxCubemap(m_Skybox);
	//�I�N�g���[
	gsDrawOctree(m_Octree);
	//�t�B�[���h�A�N�^�[�̕`��
	DrawActors();
}

void Field::DrawActors()const {
	m_Actors.Draw();
}

void Field::Add(Actor* actor) {
	m_Actors.Add(actor);
}

void Field::Clear() {
	m_Actors.Clear();
}

void Field::HandleMessage(const std::string& message, void* param) {
	m_Actors.OnMessage(message, param);
}

//�����Ƃ̏Փ˔���
bool Field::Collide(const Line& line, GSvector3* intersect, GSplane* plane,
	Actor** actor) const {
	//�I�N�g���[�Ƃ̌�������
	GSvector3 octree_intersection_point;
	GSplane octree_intersection_plane;
	bool intersection_octree = gsOctreeCollisionLine(
		gsGetOctree(m_Collider),
		&line.start, &line.end, &octree_intersection_point, &octree_intersection_plane)
		== GS_TRUE;
	//�A�N�^�[�Ƃ̌�������
	GSvector3 actor_intersection_point;
	GSplane actor_intersection_plane;
	Actor* intersection_actor = m_Actors.Collide(line, &actor_intersection_point,
		&actor_intersection_plane);
	//�I�N�g���[�ƃA�N�^�[�����ɏՓ˂��Ă��邩
	if (intersection_octree && intersection_actor != nullptr) {
		//�n�_�ƌ�_�̋������v�Z
		float distance_to_actor = line.start.distance(actor_intersection_point);
		float distance_to_octree = line.start.distance(octree_intersection_point);
		if (distance_to_octree < distance_to_actor) {
			//�I�N�g���[�̕����߂��ꍇ�̓A�N�^�[�ɏՓ˂��Ă��Ȃ����Ƃɂ���
			intersection_actor = nullptr;
		}
		else {
			//�A�N�^�[�̕����߂��ꍇ�I�N�g���[�ɏՓ˂��Ă��Ȃ����Ƃɂ���
			intersection_octree = false;
		}
	}
	//�I�N�g���[�ɏՓ˂��Ă��邩
	if (intersection_octree) {
		if (intersect != nullptr) {
			*intersect = octree_intersection_point;
		}
		if (plane != nullptr) {
			*plane = octree_intersection_plane;
		}
		if (actor != nullptr) {
			*actor = nullptr;
		}
		return true;
	}
	//�A�N�^�[�ɏՓ˂��Ă��邩
	if (intersection_actor) {
		if (intersect != nullptr) {
			*intersect = actor_intersection_point;
		}
		if (plane != nullptr) {
			*plane = actor_intersection_plane;
		}
		if (actor != nullptr) {
			*actor = intersection_actor;
		}
		return true;
	}
	//�����Փ˂��Ȃ�����
	return false;
}

//���C�Ƃ̏Փ˔���
bool Field::Collide(const Ray& ray, float max_distance,
	GSvector3* intersect, GSplane* plane,Actor** actor) const {
	Line line;
	line.start = ray.position;
	line.end = ray.position + (ray.direction.normalized() * max_distance);
	return Collide(line, intersect, plane, actor);
}

//���̂Ƃ̏Փ˔���
bool Field::Collide(const BoundingSphere& sphere, GSvector3* center,Actor** actor) const {
	//�Փ˔����̔��a
	GSvector3 collided_center = sphere.m_Center;
	//�t�B�[���h�p�A�N�^�[�Ƃ̏Փ˔�����s��
	Actor* collided_actor = m_Actors.Collide(sphere, &collided_center);
	//�I�N�g���[�Ƃ̏Փ˔�����s��
	bool collided_octree = gsOctreeCollisionSphere(
		gsGetOctree(m_Collider),
		&collided_center, sphere.m_Radius, &collided_center) == GS_TRUE;
	if (center != nullptr) {
		*center = collided_center;
	}
	if (actor != nullptr) {
		*actor = collided_actor;
	}
	//�I�N�g���[���A�N�^�[�ǂ��炩�ɏՓ˂��Ă�����
	return collided_octree || collided_actor != nullptr;
}