#pragma once
#include "Vec3.h"
#include "Matrix44.h"

typedef struct {
	Vec3 center;
	float radius;
}Sphere;

void DrawGrid(const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color);

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label);
void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label);