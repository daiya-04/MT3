#pragma once

const int kColumnWidht = 60;
const int kRowHeight = 20;

typedef struct {
	float x, y, z;
}Vec3;

Vec3 Add(const Vec3& v1, const Vec3& v2);
Vec3 Sub(const Vec3& v1, const Vec3& v2);
Vec3 Mul(float scalar, const Vec3& v);
float Dot(const Vec3& v1, const Vec3& v2);
Vec3 Cross(const Vec3& v1, const Vec3& v2);
float Length(const Vec3& v);
Vec3 Normalize(const Vec3& v);
Vec3 Inverse(const Vec3& v);
float Lerp(float t, float start, float end);
Vec3 Lerp(float t, const Vec3& start, const Vec3& end);
float Clamp(float value, float min = 0.0f, float max = 1.0f);
Vec3 Project(const Vec3& v1, const Vec3& v2);
Vec3 Perpendicular(const Vec3& vector);