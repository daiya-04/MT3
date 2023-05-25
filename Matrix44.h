#pragma once
#include"Vec3.h"
#include <stdint.h>

const int kMatrixNum = 4;

typedef struct {
	float m[kMatrixNum][kMatrixNum];
}Matrix44;

typedef struct {
	Vec3 center;
	float radius;
}Sphere;

//加算
Matrix44 Add(const Matrix44& m1, const Matrix44& m2);
//減算
Matrix44 Sub(const Matrix44& m1, const Matrix44& m2);
//乗算
Matrix44 Multiply(const Matrix44& m1, const Matrix44& m2);
//逆行列
Matrix44 Inverse(const Matrix44& m);
//転置行列
Matrix44 Transpose(const Matrix44& m);
//単位行列
Matrix44 MakeIdentity44();
//平行移動行列
Matrix44 MakeTranslateMatrix(const Vec3& translate);
//拡大縮小行列
Matrix44 MakeScaleMatrix(const Vec3& scale);
//座標変換
Vec3 Transform(const Vec3& vector, const Matrix44& matrix);
//X軸回転行列
Matrix44 MakerotateXMatrix(float radian);
//Y軸回転行列
Matrix44 MakerotateYMatrix(float radian);
//Z軸回転行列
Matrix44 MakerotateZMatrix(float radian);
//3次元アフィン変換行列
Matrix44 MakeAffineMatrix(const Vec3& scale, const Vec3& rotate, const Vec3& translate);
//透視投影行列
Matrix44 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//正射影行列
Matrix44 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//ビューポート変換行列
Matrix44 MakeViewportMatrix(float left, float top, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f);

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix,const char* label);

void DrawGrid(const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix,uint32_t color);