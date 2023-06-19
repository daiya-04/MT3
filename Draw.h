#pragma once
#include "Vec3.h"
#include "Matrix44.h"

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

void DrawGrid(const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawPlane(const Plane& plane, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);
void DrawTriangle(const Triangle& triangle, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label);
void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label);