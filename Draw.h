﻿#pragma once
#include "Vec3.h"
#include "Matrix44.h"

const int kColumnWidht = 60;
const int kRowHeight = 20;
const int kDivitionNum = 16;

//線分
typedef struct {
	Vec3 origin; //始点
	Vec3 diff;   //終点との差分ベクトル
}Segment;

//直線
typedef struct {
	Vec3 origin; //始点
	Vec3 diff;   //終点との差分ベクトル
}Line;

//半直線
typedef struct {
	Vec3 origin; //始点
	Vec3 diff;   //終点との差分ベクトル
}Ray;

//球
typedef struct {
	Vec3 center; //中心点
	float radius; //半径
}Sphere;

//平面
typedef struct {
	Vec3 normal; //法線
	float distance; //原点からの距離
}Plane;

//三角形
typedef struct {
	Vec3 vertices[3]; //頂点
}Triangle;

typedef struct {
	Vec3 min;
	Vec3 max;
}AABB;

typedef struct {
	Vec3 center;
	Vec3 orientation[3];
	Vec3 size;
}OBB;

void DrawGrid(const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawPlane(const Plane& plane, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawTriangle(const Triangle& triangle, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawAABB(const AABB& aabb, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawBezier(const Vec3& controlPoint0, const Vec3& controlPoint1, const Vec3& controlPoint2,
	const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawOBB(const OBB& obb, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label);
void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label);