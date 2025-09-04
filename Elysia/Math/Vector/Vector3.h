#pragma once

/**
 * @file Vector3.h
 * @brief ベクトル(3D)
 * @author 茂木翼
 */

#include <cmath>

/// <summary>
/// ベクトル(3D)
/// </summary>
struct Vector3 {
	float_t x;
	float_t y;
	float_t z;

	Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
};

// ベクトルの各種計算
Vector3 operator+(const Vector3& a, const Vector3& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
Vector3 operator-(const Vector3& a, const Vector3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
Vector3 operator*(const Vector3& v, float s) { return { v.x * s, v.y * s, v.z * s }; }