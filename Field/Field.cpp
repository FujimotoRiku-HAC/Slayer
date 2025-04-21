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
	//スカイボックス
	gsDrawSkyboxCubemap(m_Skybox);
	//オクトリー
	gsDrawOctree(m_Octree);
	//フィールドアクターの描画
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

//線分との衝突判定
bool Field::Collide(const Line& line, GSvector3* intersect, GSplane* plane,
	Actor** actor) const {
	//オクトリーとの交差判定
	GSvector3 octree_intersection_point;
	GSplane octree_intersection_plane;
	bool intersection_octree = gsOctreeCollisionLine(
		gsGetOctree(m_Collider),
		&line.start, &line.end, &octree_intersection_point, &octree_intersection_plane)
		== GS_TRUE;
	//アクターとの交差判定
	GSvector3 actor_intersection_point;
	GSplane actor_intersection_plane;
	Actor* intersection_actor = m_Actors.Collide(line, &actor_intersection_point,
		&actor_intersection_plane);
	//オクトリーとアクター両方に衝突しているか
	if (intersection_octree && intersection_actor != nullptr) {
		//始点と交点の距離を計算
		float distance_to_actor = line.start.distance(actor_intersection_point);
		float distance_to_octree = line.start.distance(octree_intersection_point);
		if (distance_to_octree < distance_to_actor) {
			//オクトリーの方が近い場合はアクターに衝突していないことにする
			intersection_actor = nullptr;
		}
		else {
			//アクターの方が近い場合オクトリーに衝突していないことにする
			intersection_octree = false;
		}
	}
	//オクトリーに衝突しているか
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
	//アクターに衝突しているか
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
	//何も衝突しなかった
	return false;
}

//レイとの衝突判定
bool Field::Collide(const Ray& ray, float max_distance,
	GSvector3* intersect, GSplane* plane,Actor** actor) const {
	Line line;
	line.start = ray.position;
	line.end = ray.position + (ray.direction.normalized() * max_distance);
	return Collide(line, intersect, plane, actor);
}

//球体との衝突判定
bool Field::Collide(const BoundingSphere& sphere, GSvector3* center,Actor** actor) const {
	//衝突判定後の半径
	GSvector3 collided_center = sphere.m_Center;
	//フィールド用アクターとの衝突判定を行う
	Actor* collided_actor = m_Actors.Collide(sphere, &collided_center);
	//オクトリーとの衝突判定を行う
	bool collided_octree = gsOctreeCollisionSphere(
		gsGetOctree(m_Collider),
		&collided_center, sphere.m_Radius, &collided_center) == GS_TRUE;
	if (center != nullptr) {
		*center = collided_center;
	}
	if (actor != nullptr) {
		*actor = collided_actor;
	}
	//オクトリーがアクターどちらかに衝突していたか
	return collided_octree || collided_actor != nullptr;
}