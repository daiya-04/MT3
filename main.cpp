#include <Novice.h>
#include "imgui.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"

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

	Vec3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};

	Vec3 rotates[3]{
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f}
	};

	Vec3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f}
	};

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

		Matrix44 sWorldMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix44 eWorldMatrix = MakeAffineMatrix(scales[1], rotates[1], translates[1]) * sWorldMatrix;
		Matrix44 hWorldMatrix = MakeAffineMatrix(scales[2], rotates[2], translates[2]) * eWorldMatrix;

		Sphere shoulder = {
			{sWorldMatrix.m[3][0],sWorldMatrix.m[3][1],sWorldMatrix.m[3][2]},
			0.1f
		};

		Sphere elbow = {
			{eWorldMatrix.m[3][0],eWorldMatrix.m[3][1],eWorldMatrix.m[3][2]},
			0.1f
		};

		Sphere hand = {
			{hWorldMatrix.m[3][0],hWorldMatrix.m[3][1],hWorldMatrix.m[3][2]},
			0.1f
		};

		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = cameraMatrix.Inverse();
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		Vec3 cameraWorldPos = { cameraMatrix.m[3][0],cameraMatrix.m[3][1] ,cameraMatrix.m[3][2] };

		ImGui::Begin("Camera");
		ImGui::DragFloat3("CameraTranslate", &cameraWorldPos.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::DragFloat3("shoulder translate", &translates[0].x, 0.01f);
		ImGui::DragFloat3("shoulder rotate", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("shoulder rotate", &scales[0].x, 0.01f);

		ImGui::DragFloat3("elbow translate", &translates[1].x, 0.01f);
		ImGui::DragFloat3("elbow rotate", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("elbow scale", &scales[1].x, 0.01f);

		ImGui::DragFloat3("hand translate", &translates[2].x, 0.01f);
		ImGui::DragFloat3("hand rotate", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("hand scale", &scales[2].x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(shoulder, viewProjectionMatrix, viewportMatrix, 0xFF0000FF);
		DrawSphere(elbow, viewProjectionMatrix, viewportMatrix, 0x00FF00FF);
		DrawSphere(hand, viewProjectionMatrix, viewportMatrix, 0x0000FFFF);

		Vec3 start = Transform(shoulder.center, viewProjectionMatrix * viewportMatrix);
		Vec3 end = Transform(elbow.center, viewProjectionMatrix * viewportMatrix);
		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, 0xFFFFFFFF);

		start = end;
		end = Transform(hand.center, viewProjectionMatrix * viewportMatrix);
		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, 0xFFFFFFFF);
		

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
