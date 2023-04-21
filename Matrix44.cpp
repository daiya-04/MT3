#include"Matrix44.h"
#include<math.h>
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

void MatrixScreenPrintf(int x, int y, const Matrix44& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < kMatrixNum; ++row) {
		for (int column = 0; column < kMatrixNum; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + kRowHeight + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}