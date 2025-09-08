#pragma once
/**
 * @file AABB.h
 * @brief AABBの構造体
 * @author 茂木翼
 */

#include "Vector3.h"

//AABB...Axis Aligned Bounding Box

/// <summary>
/// AABB
/// </summary>
struct AABB {
	//最小点(手前の左下)
	Vector3 min;
	//最大点(奥の右上)
	Vector3 max;

	/// <summary>
	/// AABBの中心点を計算するヘルパー関数
	/// </summary>
	/// <param name="aabb"></param>
	/// <returns></returns>
	Vector3 GetAABBCenter() {
		return {
			(min.x + max.x) / 2.0f,
			(min.y + max.y) / 2.0f,
			(min.z + max.z) / 2.0f
		};
	}
};