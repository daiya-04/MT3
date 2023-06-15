﻿#include "Hit.h"
#include <cmath>

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