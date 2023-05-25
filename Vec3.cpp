#include"Vec3.h"
#include<math.h>
#include<Novice.h>


Vec3 Add(const Vec3& v1, const Vec3& v2) {
    return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

Vec3 Sub(const Vec3& v1, const Vec3& v2) {
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

Vec3 Mul(float scalar, const Vec3& v) {
	return { scalar * v.x,scalar * v.y,scalar * v.z };
}

float Dot(const Vec3& v1, const Vec3& v2) {
	return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
}

Vec3 Cross(const Vec3& v1, const Vec3& v2) {
	return{ v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z,v1.x * v2.y - v1.y * v2.x };
}

float Length(const Vec3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 Normalize(const Vec3& v) {
	float len = Length(v);
	return { v.x / len,v.y / len,v.z / len };
}

void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", v.x);
	Novice::ScreenPrintf(x + kColumnWidht, y, "%.02f", v.y);
	Novice::ScreenPrintf(x + kColumnWidht * 2, y, "%.02f", v.z);
	Novice::ScreenPrintf(x + kColumnWidht * 3, y, "%s", label);
}