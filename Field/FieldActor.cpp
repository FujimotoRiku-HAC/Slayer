#include "FieldActor.h"
#include "Math/Line.h"
#include "Math/Ray.h"
#include "Collision/BoundingSphere.h"

//描画
void FieldActor::Draw()const {}

//レイとの衝突判定
bool FieldActor::Collide(const Ray& ray, float max_distance, GSvector3* intersect,
	GSplane* plane)const {
	//レイのパラメータを線分に変換
	Line line;
	line.start = ray.position;
	line.end = ray.position + (ray.direction.normalized() * max_distance);
	//線分との衝突判定を行う
	return Collide(line, intersect, plane);
}

//線分との衝突判定
bool FieldActor::Collide(const Line& line, GSvector3* intersect, GSplane* plane)const {
	//ローカル座標系の線分を求める
	Line local_line;
	local_line.start = m_Transform.inverseTransformPoint(line.start);
	local_line.end = m_Transform.inverseTransformPoint(line.end);
	//メッシュと線分が交差したか
	if(gsCollisionMeshAndLine(gsGetMesh(m_MeshCollider),&local_line.start,&local_line.end,
		intersect, plane) == GS_TRUE){
			if (intersect != nullptr) {
				//交点をワールド座標系に変換
				*intersect = m_Transform.transformPoint(*intersect);
			}
			if (plane != nullptr) {
				//平面の方程式をワールド座標系に変換
				const GSmatrix4& local_to_world_matrix = m_Transform.localToWorldMatrix();
				gsPlaneTransform(plane, plane, &local_to_world_matrix);
			}
			return true;
		}	
	return false;
}

//球体との衝突判定
bool FieldActor::Collide(const BoundingSphere& sphere, GSvector3* collided_center)const {
	//ローカル座標系の球体を求める
	BoundingSphere local_sphere;
	local_sphere.m_Center = m_Transform.inverseTransformPoint(sphere.m_Center);
	local_sphere.m_Radius = sphere.m_Radius;
	//メッシュとの球体が衝突したか
	GSvector3 local_collided_center;
	if (gsCollisionMeshAndSphere(gsGetMesh(m_MeshCollider), &local_sphere.m_Center,
		local_sphere.m_Radius, &local_collided_center) == GS_TRUE) {
		if (collided_center != nullptr) {
			//衝突判定後の中心座標をワールド座標系に変換
			*collided_center = m_Transform.transformPoint(local_collided_center);
		}
		return true;
	}
	return false;
}

TweenUnit& FieldActor::MoveTo(const GSvector3& to, float duration) {
	//現在の場所から指定された場所までTweenで移動する
	return Tween::Vector3(m_Transform.position(), to, duration,
		[=](GSvector3 pos) {m_Transform.position(pos); });
}