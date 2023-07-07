#include "Draw.h"
#include<Novice.h>
#define _USE_MATH_DEFINES
#include<cmath>

void DrawGrid(const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix) {
	const float kGridhalfWidth = 2.0f;                                      //Gridの半分の幅
	const uint32_t kSubdivision = 10;                                       //分割数
	const float kGridEvery = (kGridhalfWidth * 2.0f) / float(kSubdivision); //1つ分の長さ

	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		Vec3 worldStartPos = { -kGridhalfWidth,0.0f,float(xIndex) * kGridEvery - kGridhalfWidth };
		Vec3 worldEndPos = { kGridhalfWidth,0.0f, float(xIndex) * kGridEvery - kGridhalfWidth };

		Vec3 screenStartPos = Transform(worldStartPos, Multiply(viewProjectionMatrix, viewportMatrix));
		Vec3 screenEndPos = Transform(worldEndPos, Multiply(viewProjectionMatrix, viewportMatrix));

		if (xIndex == 5) {
			Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), 0xAAAAAAFF);
		}

	}

	//左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		Vec3 worldStartPos = { float(zIndex) * kGridEvery - kGridhalfWidth,0.0f,-kGridhalfWidth };
		Vec3 worldEndPos = { float(zIndex) * kGridEvery - kGridhalfWidth,0.0f, kGridhalfWidth };

		Vec3 screenStartPos = Transform(worldStartPos, Multiply(viewProjectionMatrix, viewportMatrix));
		Vec3 screenEndPos = Transform(worldEndPos, Multiply(viewProjectionMatrix, viewportMatrix));

		if (zIndex == 5) {
			Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), 0x000000FF);
		}
		else {
			Novice::DrawLine(int(screenStartPos.x), int(screenStartPos.y), int(screenEndPos.x), int(screenEndPos.y), 0xAAAAAAFF);
		}

	}

}

void DrawSphere(const Sphere& sphere, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 16;                    //分割数
	const float kLonEvery = float(M_PI) / kSubdivision;         //経度分割1つ分の角度
	const float kLatEvery = 2.0f * float(M_PI) / kSubdivision;  //緯度分割1つ分の角度
	//緯度の方向に分割　-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; //θ
		//経度の方向に分割　0~2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; //φ



			Vec3 worldA = Add(sphere.center, Mul(sphere.radius, { std::cosf(lat) * std::cosf(lon),std::sinf(lat),std::cosf(lat) * std::sinf(lon) }));
			Vec3 worldB = Add(sphere.center, Mul(sphere.radius, { std::cosf(lat + kLatEvery) * std::cosf(lon),std::sinf(lat + kLatEvery),std::cosf(lat + kLatEvery) * std::sinf(lon) }));
			Vec3 worldC = Add(sphere.center, Mul(sphere.radius, { std::cosf(lat) * std::cosf(lon + kLonEvery),std::sinf(lat),std::cosf(lat) * std::sinf(lon + kLonEvery) }));

			Vec3 screenA = Transform(worldA, Multiply(viewProjectionMatrix, viewportMatrix));
			Vec3 screenB = Transform(worldB, Multiply(viewProjectionMatrix, viewportMatrix));
			Vec3 screenC = Transform(worldC, Multiply(viewProjectionMatrix, viewportMatrix));


			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);

		}
	}


}

void DrawPlane(const Plane& plane, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color) {
	Vec3 center = Mul(plane.distance, plane.normal);
	Vec3 perpendicular[4];
	perpendicular[0] = Normalize(Perpendicular(plane.normal));
	perpendicular[1] = Inverse(perpendicular[0]);
	perpendicular[2] = Cross(plane.normal, perpendicular[0]);
	perpendicular[3] = Inverse(perpendicular[2]);

	Vec3 points[4];
	for (uint32_t index = 0; index < 4; ++index) {
		Vec3 extend = Mul(2.0f, perpendicular[index]);
		Vec3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}

void DrawTriangle(const Triangle& triangle, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color) {

	Vec3 vertices[3];
	for (uint32_t i = 0; i < 3; i++) {
		vertices[i] = Transform(triangle.vertices[i], Multiply(viewProjectionMatrix, viewportMatrix));
	}

	Novice::DrawTriangle(
		(int)vertices[0].x, (int)vertices[0].y,
		(int)vertices[1].x, (int)vertices[1].y,
		(int)vertices[2].x, (int)vertices[2].y,
		color, kFillModeWireFrame);

}

void DrawAABB(const AABB& aabb, const Matrix44& viewProjectionMatrix, const Matrix44& viewportMatrix, uint32_t color) {
	Vec3 point[8]{};
	for (uint32_t index = 0; index < 8; index++) {
		if (index < 4) {
			point[index] = aabb.min;
		}else if (index >= 4) {
			point[index] = aabb.max;
		}
	}

	Vec3 diff = {
		aabb.max.x - aabb.min.x,
		aabb.max.y - aabb.min.y,
		aabb.max.z - aabb.min.z
	};

	//左下奥
	point[1].z += diff.z;
	//左上奥
	point[2].y += diff.y;
	point[2].z += diff.z;
	//左上手前
	point[3].y += diff.y;

	//右上手前
	point[5].z -= diff.z;
	//右下手前
	point[6].y -= diff.y;
	point[6].z -= diff.z;
	//右下奥
	point[7].y -= diff.y;

	Vec3 vertex[8]{};
	for (uint32_t index = 0; index < 8; index++) {
		vertex[index] = Transform(point[index], Multiply(viewProjectionMatrix, viewportMatrix));
	}

	Novice::DrawLine((int)vertex[0].x, (int)vertex[0].y, (int)vertex[1].x, (int)vertex[1].y, color);
	Novice::DrawLine((int)vertex[1].x, (int)vertex[1].y, (int)vertex[2].x, (int)vertex[2].y, color);
	Novice::DrawLine((int)vertex[2].x, (int)vertex[2].y, (int)vertex[3].x, (int)vertex[3].y, color);
	Novice::DrawLine((int)vertex[3].x, (int)vertex[3].y, (int)vertex[0].x, (int)vertex[0].y, color);
	Novice::DrawLine((int)vertex[4].x, (int)vertex[4].y, (int)vertex[5].x, (int)vertex[5].y, color);
	Novice::DrawLine((int)vertex[5].x, (int)vertex[5].y, (int)vertex[6].x, (int)vertex[6].y, color);
	Novice::DrawLine((int)vertex[6].x, (int)vertex[6].y, (int)vertex[7].x, (int)vertex[7].y, color);
	Novice::DrawLine((int)vertex[7].x, (int)vertex[7].y, (int)vertex[4].x, (int)vertex[4].y, color);
	Novice::DrawLine((int)vertex[0].x, (int)vertex[0].y, (int)vertex[6].x, (int)vertex[6].y, color);
	Novice::DrawLine((int)vertex[1].x, (int)vertex[1].y, (int)vertex[7].x, (int)vertex[7].y, color);
	Novice::DrawLine((int)vertex[2].x, (int)vertex[2].y, (int)vertex[4].x, (int)vertex[4].y, color);
	Novice::DrawLine((int)vertex[3].x, (int)vertex[3].y, (int)vertex[5].x, (int)vertex[5].y, color);

}

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < kMatrixNum; ++row) {
		for (int column = 0; column < kMatrixNum; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidht, y + kRowHeight + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vec3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", v.x);
	Novice::ScreenPrintf(x + kColumnWidht, y, "%.02f", v.y);
	Novice::ScreenPrintf(x + kColumnWidht * 2, y, "%.02f", v.z);
	Novice::ScreenPrintf(x + kColumnWidht * 3, y, "%s", label);
}