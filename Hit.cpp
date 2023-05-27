#include "Hit.h"

Vec3 ClosestPoint(const Vec3& point, const Segment& segment) {
	return Add(segment.origin, Project(Sub(point, segment.origin),segment.diff));
}