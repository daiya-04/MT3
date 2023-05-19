#include <Novice.h>
#include <stdint.h>
#include <Matrix44.h>
#include<cmath>

const char kWindowTitle[] = "LE2A_09_セト_ダイヤ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const float kSpeed = 1.0f;
	const float kTriangleHalfHeight = (100.0f * std::powf(3, (1 / 2))) / 2;
	const Vec3 kLocalViertices[3] = {
		{0.0f,kTriangleHalfHeight,0.0f},
		{50.0f,-kTriangleHalfHeight,0.0f},
		{-50.0,-kTriangleHalfHeight,0.0f}
	};

	Vec3 v1 = { 1.2f,-3.9f,2.5f };
	Vec3 v2 = { 2.8f,0.4f,-1.3f };

	Vec3 rotate = {};
	Vec3 translate = {};
	Vec3 cameraPos = { 0.0f,0.0f,-500.0f };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_W]) {
			translate.z += kSpeed;
		}
		if (keys[DIK_S]) {
			translate.z -= kSpeed;
		}
		if (keys[DIK_D]) {
			translate.x += kSpeed;
		}
		if (keys[DIK_A]) {
			translate.x -= kSpeed;
		}

		if (translate.z <= cameraPos.z) {
			translate.z = cameraPos.z + 1.0f;
		}

		rotate.y += 0.05f;

		Vec3 cross = Cross(v1, v2);

		Matrix44 worldMarix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPos);
		Matrix44 viewMatrix = Inverse(cameraMatrix);
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 worldViewProjectionMatrix = Multiply(worldMarix, Multiply(viewMatrix, projectionMatrix));
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));
		Vec3 screenVertices[3];
		for (uint32_t i = 0; i < 3; i++) {
			Vec3 ndcVertex = Transform(kLocalViertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (Dot(cameraPos, Cross(Sub(screenVertices[1], screenVertices[0]), Sub(screenVertices[2], screenVertices[1]))) <= 0) {
			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y),
				RED, kFillModeSolid);
		}
		

		VectorScreenPrintf(0, 0, cross, "Cross");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
