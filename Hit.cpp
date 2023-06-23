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

bool IsCollision(const Line& line, const Plane& plane) {

	float dot = Dot(plane.normal, line.diff);

	if (dot == 0.0f) {
		return false;
	}

	//float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	return true;
}

bool IsCollision(const Ray& ray, const Plane& plane) {

	float dot = Dot(plane.normal, ray.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(ray.origin, plane.normal)) / dot;

	if (t >= 0.0f) {
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

	if (dot == 0.0f) {
		return false;
	}

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
		if (0.0f <= t && t <= 1.0f) {
			return true;
		}
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Line& line) {
	Vec3 v01 = Sub(triangle.vertices[1], triangle.vertices[0]);
	Vec3 v12 = Sub(triangle.vertices[2], triangle.vertices[1]);
	Vec3 v20 = Sub(triangle.vertices[0], triangle.vertices[2]);

	Vec3 normal = Normalize(Cross(v01, v12));
	float distance = Dot(triangle.vertices[0], normal);

	float dot = Dot(normal, line.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (distance - Dot(line.origin, normal)) / dot;

	Vec3 p = Add(line.origin, Mul(t, line.diff));

	Vec3 v0p = Sub(p, triangle.vertices[0]);
	Vec3 v1p = Sub(p, triangle.vertices[1]);
	Vec3 v2p = Sub(p, triangle.vertices[2]);

	Vec3 cross01 = Cross(v01, v1p);
	Vec3 cross12 = Cross(v12, v2p);
	Vec3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f) {
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Ray& ray) {
	Vec3 v01 = Sub(triangle.vertices[1], triangle.vertices[0]);
	Vec3 v12 = Sub(triangle.vertices[2], triangle.vertices[1]);
	Vec3 v20 = Sub(triangle.vertices[0], triangle.vertices[2]);

	Vec3 normal = Normalize(Cross(v01, v12));
	float distance = Dot(triangle.vertices[0], normal);

	float dot = Dot(normal, ray.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (distance - Dot(ray.origin, normal)) / dot;

	Vec3 p = Add(ray.origin, Mul(t, ray.diff));

	Vec3 v0p = Sub(p, triangle.vertices[0]);
	Vec3 v1p = Sub(p, triangle.vertices[1]);
	Vec3 v2p = Sub(p, triangle.vertices[2]);

	Vec3 cross01 = Cross(v01, v1p);
	Vec3 cross12 = Cross(v12, v2p);
	Vec3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f) {
		if (0.0f <= t) {
			return true;
		}
	}
	return false;
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}

	return false;
}
