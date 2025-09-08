#include "Collider.h"

Vector3 Collider::CalculateAABBPushbackVector(const AABB& aabbB){
	// 各AABBの中心点を計算
	Vector3 centerA = { (aabb_.min.x + aabb_.max.x) / 2.0f, (aabb_.min.y + aabb_.max.y) / 2.0f, (aabb_.min.z + aabb_.max.z) / 2.0f };
	Vector3 centerB = { (aabbB.min.x + aabbB.max.x) / 2.0f, (aabbB.min.y + aabbB.max.y) / 2.0f, (aabbB.min.z + aabbB.max.z) / 2.0f };

	// 各軸の重なり量を計算
	float overlapX = (aabb_.max.x - aabb_.min.x) / 2.0f + (aabbB.max.x - aabbB.min.x) / 2.0f - std::abs(centerA.x - centerB.x);
	float overlapY = (aabb_.max.y - aabb_.min.y) / 2.0f + (aabbB.max.y - aabbB.min.y) / 2.0f - std::abs(centerA.y - centerB.y);
	float overlapZ = (aabb_.max.z - aabb_.min.z) / 2.0f + (aabbB.max.z - aabbB.min.z) / 2.0f - std::abs(centerA.z - centerB.z);

	// 押し戻しベクトルを初期化
	Vector3 pushbackVector = { 0.0f, 0.0f, 0.0f };

	// 最も重なりが小さい軸で押し出す
	if (overlapX < overlapY && overlapX < overlapZ) {
		pushbackVector.x = (centerA.x > centerB.x) ? overlapX : -overlapX;
	}
	else if (overlapY < overlapZ) {
		pushbackVector.y = (centerA.y > centerB.y) ? overlapY : -overlapY;
	}
	else {
		pushbackVector.z = (centerA.z > centerB.z) ? overlapZ : -overlapZ;
	}

	return pushbackVector;
}