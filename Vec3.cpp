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

Vec3 Inverse(const Vec3& v) {
	return{ -v.x,-v.y,-v.z };
}

float Clamp(float value, float min, float max) {
	if (value <= 0.0f) {
		return 0.0f;
	}
	if (value >= 1.0f) {
		return 1.0f;
	}
	return value;
}

float Lerp(float t, float start, float end) {
	Clamp(t);
	return(1.0f - t) * start + t * end;
}

Vec3 Lerp(float t, const Vec3& start, const Vec3& end) {
	return{ Lerp(t,start.x,end.x),Lerp(t,start.y,end.y),Lerp(t,start.z,end.z) };
}

