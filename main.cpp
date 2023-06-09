#include <Novice.h>
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"
#include "Hit.h"
#include "imgui.h"

const char kWindowTitle[] = "LE2A_09_セト_ダイヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Sphere sphere1{ {},1.0f };
	Sphere sphere2{ {2.0f,0.0f,0.0f},0.5f };

	Vec3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vec3 cameraRotate = { 0.26f,0.0f,0.0f };

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

		

		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = Inverse(cameraMatrix);
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		ImGui::Begin("Window");
		ImGui::DragFloat3("Camera", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat4("Sphere1", &sphere1.center.x, 0.01f);
		ImGui::DragFloat4("Sphere2", &sphere2.center.x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);

		if (IsCollision(sphere1, sphere2)) {
			DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, 0xFF0000FF);
		}else {
			DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
		}
		

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
