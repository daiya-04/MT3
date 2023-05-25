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

void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label);