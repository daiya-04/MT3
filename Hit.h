#pragma once
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"



Vec3 ClosestPoint(const Vec3& point, const Segment& segment);

bool IsCollision(const Sphere& s1, const Sphere& s2);
bool IsCollision(const Plane& plane, const Sphere& sphere);
bool IsCollision(const Segment& segment, const Plane& plane);
bool IsCollision(const Triangle& triangle, const Segment& segment);