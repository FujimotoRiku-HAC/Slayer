#include "FieldActorManager.h"
#include "FieldActor.h"
#include "Math/Line.h"
#include "Math/Ray.h"
#include "Collision/BoundingSphere.h"

//レイとフィールド用のアクターとの衝突判定
FieldActor* FieldActorManager::Collide(const Ray& ray, float max_distance, GSvector3*
	intersect, GSplane* plane)const {
	//レイを線分に変換
	Line line;
	line.start = ray.position;
	line.end = ray.position * (ray.direction.normalized() * max_distance);
	//線分との判定を行う
	return Collide(line, intersect, plane);
}

//線分とフィールド用のアクターとの衝突判定
FieldActor* FieldActorManager::Collide(const Line& line, GSvector3* intersect, GSplane* plane)const {
	//最も始点から近いアクター
	FieldActor* closest_actor{ nullptr };
	//最も始点から近い交点との距離
	float closest_distance = std::numeric_limits<float>::max();
	//最も始点から近い交点
	GSvector3 closest_intersection;
	//最も始点から近い交点の平面
	GSplane closest_intersection_plane;

	for (auto actor : m_Actors) {
		//フィールドアクターであるか確認
		FieldActor* field_actor = dynamic_cast<FieldActor*>(actor);
		//フィールドアクターでなければスキップ
		if (field_actor == nullptr)continue;
		//フィールドアクターと線分との交差判定を行う
		GSvector3 intersection_point;
		GSplane intersection_plane;
		if (field_actor->Collide(line, &intersection_point, &intersection_plane)) {
			//視点からの距離を計算
			float distance = line.start.distance(intersection_point);
			if (distance < closest_distance) {
				//距離が近い場合は、アクターを更新
				closest_distance = distance;
				closest_actor = field_actor;
				closest_intersection = intersection_point;
				closest_intersection_plane = intersection_plane;
			}
		}
	}
	//衝突したアクターが存在するか
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
		//フィールドアクターであるか確認
		FieldActor* field_actor = dynamic_cast<FieldActor*>(actor);
		//フィールドアクターでなければスキップ
		if (field_actor == nullptr)continue;
		//フィールドと球体の衝突判定を行う
		if (field_actor->Collide(sphere, collided_center)) {
			return field_actor;
		}
	}
	return nullptr;
}