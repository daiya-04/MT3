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

bool IsCollition(const Plane& plane, const Sphere& sphere) {

	float distance = std::fabs(Dot(plane.normal, sphere.center) - plane.distance);

	if (distance <= sphere.radius) {
		return true;
	}

	return false;
}

bool IsCollision(const Segment& segment, const Plane& plane) {

	Vec3 end = Add(segment.origin, segment.diff);

	float dot = Dot(plane.normal, end);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}
	return false;
}