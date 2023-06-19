#include "Hit.h"
#include <cmath>
#include "imgui.h"

Vec3 ClosestPoint(const Vec3& point, const Segment& segment) {
	return Add(segment.origin, Project(Sub(point, segment.origin), segment.diff));
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {

	float distance = Length(Sub(s1.center, s2.center));

	if (distance <= s1.radius + s2.radius) {
		return true;
	}

	return false;
}

bool IsCollision(const Plane& plane, const Sphere& sphere) {

	float distance = std::fabs(Dot(plane.normal, sphere.center) - plane.distance);

	if (distance <= sphere.radius) {
		return true;
	}

	return false;
}

bool IsCollision(const Segment& segment, const Plane& plane) {

	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Segment& segment) {

	Vec3 v01 = Sub(triangle.vertices[1], triangle.vertices[0]);
	Vec3 v12 = Sub(triangle.vertices[2], triangle.vertices[1]);
	Vec3 v20 = Sub(triangle.vertices[0], triangle.vertices[2]);

	Vec3 normal = Normalize(Cross(v01, v12));
	float distance = Dot(triangle.vertices[0], normal);

	float dot = Dot(normal, segment.diff);

	float t = (distance - Dot(segment.origin, normal)) / dot;

	Vec3 p = Add(segment.origin, Mul(t, segment.diff));

	Vec3 v0p = Sub(p, triangle.vertices[0]);
	Vec3 v1p = Sub(p, triangle.vertices[1]);
	Vec3 v2p = Sub(p, triangle.vertices[2]);

	Vec3 cross01 = Cross(v01, v1p);
	Vec3 cross12 = Cross(v12, v2p);
	Vec3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f) {
		if (IsCollision(segment, { normal,distance })) {
			return true;
		}
	}
	return false;
}