#pragma once

const int kRowHeight = 20;
const int kColumnWidth = 60;
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

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix,const char* label);