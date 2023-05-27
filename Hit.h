#pragma once
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"

typedef struct {
	Vec3 origin; //始点
	Vec3 diff;   //終点との差分ベクトル
}Segment;

Vec3 ClosestPoint(const Vec3& point, const Segment& segment);