#pragma once
#include"Vec3.h"

const int kMatrixNum = 4;

typedef struct {
	float m[kMatrixNum][kMatrixNum];
}Matrix44;


Matrix44 Add(const Matrix44& m1, const Matrix44& m2);

Matrix44 Sub(const Matrix44& m1, const Matrix44& m2);

Matrix44 Multiply(const Matrix44& m1, const Matrix44& m2);

Matrix44 Inverse(const Matrix44& m);

Matrix44 Transpose(const Matrix44& m);

Matrix44 MakeIdentity44();

Matrix44 MakeTranslateMatrix(const Vec3& translate);

Matrix44 MakeScaleMatrix(const Vec3& scale);

Vec3 Transform(const Vec3& vector, const Matrix44& matrix);

Matrix44 MakerotateXMatrix(float radian);

Matrix44 MakerotateYMatrix(float radian);

Matrix44 MakerotateZMatrix(float radian);

Matrix44 MakeAffineMatrix(const Vec3& scale, const Vec3& rotate, const Vec3& translate);

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix,const char* label);