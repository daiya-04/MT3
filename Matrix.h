#pragma once

const int kRowHeight = 20;
const int kColumnWidht = 60;

typedef struct {
	float x, y, z;
}Vec3;

typedef struct {
	float m[4][4];
}Matrix44;

Matrix44 MakeTranslateMatrix(const Vec3& translate);
Matrix44 makeScaleMatrix(const Vec3& scale);
Vec3 Transform(const Vec3& vector, const Matrix44& matrix);
void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label);
void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label);