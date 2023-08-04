#include <Novice.h>
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"
#include "Hit.h"
#include "imgui.h"
#include <numbers>

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

	Vec3 rotate = { 0.0f,0.0f,0.0f };

	OBB obb = {
		{-1.0f,0.0f,0.0f},
		{{1.0f,0.0f,0.0f},
		 {0.0f,1.0f,0.0f},
		 {0.0f,0.0f,1.0f}},
		{0.5f,0.5f,0.5f}
	};

	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		0.5f
	};

	uint32_t color = 0xFFFFFFFF;

	Vec3 cameraTranslate = { 0.0f,0.0f,-6.49f };
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

		Matrix44 rotateMatrix = MakeRotateXMatrix(rotate.x) * MakeRotateYMatrix(rotate.y) * MakeRotateZMatrix(rotate.z);

		obb.orientation[0] = { rotateMatrix.m[0][0],rotateMatrix.m[0][1] ,rotateMatrix.m[0][2] };
		obb.orientation[1] = { rotateMatrix.m[1][0],rotateMatrix.m[1][1] ,rotateMatrix.m[1][2] };
		obb.orientation[2] = { rotateMatrix.m[2][0],rotateMatrix.m[2][1] ,rotateMatrix.m[2][2] };


		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = cameraMatrix.Inverse();
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		if (IsCollision(obb, sphere)) {
			color = 0xFF0000FF;
		}else {
			color = 0xFFFFFFFF;
		}
		

		ImGui::Begin("Camera");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::DragFloat3("obb center", &obb.center.x, 0.01f);
		ImGui::DragFloat("rotateX", &rotate.x, 0.01f);
		ImGui::DragFloat("rotateY", &rotate.y, 0.01f);
		ImGui::DragFloat("rotateZ", &rotate.z, 0.01f);
		ImGui::DragFloat3("obb orientationX", &obb.orientation[0].x, 0.01f);
		ImGui::DragFloat3("obb orientationY", &obb.orientation[1].x, 0.01f);
		ImGui::DragFloat3("obb orientationZ", &obb.orientation[2].x, 0.01f);
		ImGui::DragFloat3("obb size", &obb.size.x, 0.01f);

		ImGui::DragFloat3("Sphere center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("Sphere radius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
		DrawOBB(obb, viewProjectionMatrix, viewportMatrix, color);

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
