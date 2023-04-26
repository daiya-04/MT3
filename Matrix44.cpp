#include"Matrix44.h"
#include<cmath>
#include<assert.h>
#include<Novice.h>

Matrix44 Add(const Matrix44& m1, const Matrix44& m2) {
	Matrix44 result;
	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			result.m[row][column] = m1.m[row][column] + m2.m[row][column];
		}
	}
	return result;
}

Matrix44 Sub(const Matrix44& m1, const Matrix44& m2) {
	Matrix44 result;
	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			result.m[row][column] = m1.m[row][column] - m2.m[row][column];
		}
	}
	return result;
}

Matrix44 Multiply(const Matrix44& m1, const Matrix44& m2) {
	Matrix44 result;
	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			result.m[row][column] = (m1.m[row][0] * m2.m[0][column]) + (m1.m[row][1] * m2.m[1][column]) + (m1.m[row][2] * m2.m[2][column]) + (m1.m[row][3] * m2.m[3][column]);
		}
	}
	return result;
}

Matrix44 Inverse(const Matrix44& matrix) {
	Matrix44 result;
	float sweep[kMatrixNum][kMatrixNum * 2];
	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			sweep[row][column] = matrix.m[row][column];

			sweep[row][kMatrixNum + column] = (row == column) ? 1.0f : 0.0f;
		}
	}

	for (int k = 0; k < kMatrixNum; k++) {
		float a = 1 / sweep[k][k];

		for (int column = 0; column < kMatrixNum * 2; column++) {
			sweep[k][column] *= a;
		}

		for (int row = 0; row < kMatrixNum; row++) {
			if (row == k) {
				continue;
			}

			a = -sweep[row][k];

			for (int column = 0; column < kMatrixNum * 2; column++) {
				sweep[row][column] += sweep[k][column] * a;
			}
		}
	}

	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			result.m[row][column] = sweep[row][column + kMatrixNum];
		}
	}

	return result;
}

Matrix44 Transpose(const Matrix44& matrix) {
	Matrix44 result;
	for (int row = 0; row < kMatrixNum; row++) {
		for (int column = 0; column < kMatrixNum; column++) {
			result.m[row][column] = matrix.m[column][row];
		}
	}
	return result;
}

Matrix44 MakeIdentity44() {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Matrix44 MakeTranslateMatrix(const Vec3& translate) {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};
}

Matrix44 makeScaleMatrix(const Vec3& scale) {
	return {
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Vec3 Transform(const Vec3& vector, const Matrix44& matrix) {
	Vec3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Matrix44 MakerotateXMatrix(float radian) {
	return {
		1.0f,0.0f,0.0f,0.0f,
		0.0f, std::cos(radian), std::sin(radian), 0.0f,
		0.0f,-std::sin(radian), std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Matrix44 MakerotateYMatrix(float radian) {
	return {
		std::cos(radian), 0.0f, -std::sin(radian), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		std::sin(radian),0.0f, std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

Matrix44 MakerotateZMatrix(float radian) {
	return {
		std::cos(radian), std::sin(radian), 0.0f, 0.0f,
		-std::sin(radian), std::cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
}

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < kMatrixNum; ++row) {
		for (int column = 0; column < kMatrixNum; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidht, y + kRowHeight + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}