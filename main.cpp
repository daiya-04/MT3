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

	Vec3 rotate1{};
	Vec3 rotate2{};

	OBB obb1{
		.center{},
		.orientation{
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f}
		},
		.size{0.83f,0.26f,0.24f}
	};

	OBB obb2{
		.center{0.0f,1.0f,0.0f},
		.orientation{
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f}
		},
		.size{0.5f,0.37f,0.5f}
	};

	uint32_t color = 0xFFFFFFFF;

	Vec3 cameraTranslate = { 0.0f,0.0f,-6.49f };
	Vec3 cameraRotate = { 0.0f,0.0f,0.0f };

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

		Matrix44 rotate1Matrix = MakeRotateXMatrix(rotate1.x) * MakeRotateYMatrix(rotate1.y) * MakeRotateZMatrix(rotate1.z);
		Matrix44 rotate2Matrix = MakeRotateXMatrix(rotate2.x) * MakeRotateYMatrix(rotate2.y) * MakeRotateZMatrix(rotate2.z);

		obb1.orientation[0] = { rotate1Matrix.m[0][0],rotate1Matrix.m[0][1] ,rotate1Matrix.m[0][2] };
		obb1.orientation[1] = { rotate1Matrix.m[1][0],rotate1Matrix.m[1][1] ,rotate1Matrix.m[1][2] };
		obb1.orientation[2] = { rotate1Matrix.m[2][0],rotate1Matrix.m[2][1] ,rotate1Matrix.m[2][2] };

		obb2.orientation[0] = { rotate2Matrix.m[0][0],rotate2Matrix.m[0][1] ,rotate2Matrix.m[0][2] };
		obb2.orientation[1] = { rotate2Matrix.m[1][0],rotate2Matrix.m[1][1] ,rotate2Matrix.m[1][2] };
		obb2.orientation[2] = { rotate2Matrix.m[2][0],rotate2Matrix.m[2][1] ,rotate2Matrix.m[2][2] };


		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = cameraMatrix.Inverse();
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		if (IsCollision(obb1, obb2)) {
			color = 0xFF0000FF;
		}
		else {
			color = 0xFFFFFFFF;
		}

		ImGui::Begin("Camera");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::DragFloat3("obb1 center", &obb1.center.x, 0.01f);
		ImGui::DragFloat("rotate1X", &rotate1.x, 0.01f);
		ImGui::DragFloat("rotate1Y", &rotate1.y, 0.01f);
		ImGui::DragFloat("rotate1Z", &rotate1.z, 0.01f);
		ImGui::DragFloat3("obb1 orientationX", &obb1.orientation[0].x, 0.01f);
		ImGui::DragFloat3("obb1 orientationY", &obb1.orientation[1].x, 0.01f);
		ImGui::DragFloat3("obb1 orientationZ", &obb1.orientation[2].x, 0.01f);
		ImGui::DragFloat3("obb1 size", &obb1.size.x, 0.01f);

		ImGui::DragFloat3("obb2 center", &obb2.center.x, 0.01f);
		ImGui::DragFloat("rotate2X", &rotate2.x, 0.01f);
		ImGui::DragFloat("rotate2Y", &rotate2.y, 0.01f);
		ImGui::DragFloat("rotate2Z", &rotate2.z, 0.01f);
		ImGui::DragFloat3("obb2 orientationX", &obb2.orientation[0].x, 0.01f);
		ImGui::DragFloat3("obb2 orientationY", &obb2.orientation[1].x, 0.01f);
		ImGui::DragFloat3("obb2 orientationZ", &obb2.orientation[2].x, 0.01f);
		ImGui::DragFloat3("obb2 size", &obb2.size.x, 0.01f);
		
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawOBB(obb1, viewProjectionMatrix, viewportMatrix, color);
		DrawOBB(obb2, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);

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
