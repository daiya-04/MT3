#include <Novice.h>
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"
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

	float radius = 0.8f;

	Ball ball = {
		{radius,0.0f,0.0f},
		{},
		{},
		1.0f,
		0.05f,
		0xFFFFFFFF
	};

	float deltaTime = 1.0f / 60.0f;

	float anglarVelocity = (float)std::numbers::pi;
	float angle = 0.0f;

	Vec3 cameraTranslate = { 0.0f,0.0f,-6.49f };
	Vec3 cameraRotate = { 0.26f,0.0f,0.0f };

	bool startFlag = false;

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

		
		angle = std::fmod(angle, 2.0f * (float)std::numbers::pi);

		if (startFlag == true) {
			angle += anglarVelocity * deltaTime;
			ball.position.x = std::cosf(angle) * radius;
			ball.position.y = std::sinf(angle) * radius;
			ball.position.z = 0.0f;
		}
		

		

		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = cameraMatrix.Inverse();
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		ImGui::Begin("Camera");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {
			startFlag = true;
		}
		ImGui::DragFloat("angle", &angle, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere({ ball.position,ball.radius }, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);


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
