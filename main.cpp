#include <Novice.h>
#include "Vec3.h"
#include "Matrix44.h"
#include "Draw.h"
#include "imgui.h"
#include <cmath>

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

	ConicalPendulum conicalPendulum = {
		.anchor{0.0f,1.0f,0.0f},
		.length = 0.8f,
		.halfApexAngle = 0.7f,
		.angle = 0.0f,
		.anglarVelocity = 0.0f
	};

	Sphere sphere = {
		{},
		0.05f
	};

	//振り子の先端の位置
	Vec3 point{};


	float deltaTime = 1.0f / 60.0f;
	float gravityAcceleration = 9.8f;

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

		if (startFlag == true) {
			conicalPendulum.anglarVelocity = std::sqrtf(gravityAcceleration / (conicalPendulum.length * std::cosf(conicalPendulum.halfApexAngle)));
			conicalPendulum.angle += conicalPendulum.anglarVelocity * deltaTime;
		}

		float radius = std::sinf(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		float height = std::cosf(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		point.x = conicalPendulum.anchor.x + std::cosf(conicalPendulum.angle) * radius;
		point.y = conicalPendulum.anchor.y - height;
		point.z = conicalPendulum.anchor.z - std::sinf(conicalPendulum.angle) * radius;

		Matrix44 pointWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, {}, point);
		Matrix44 sphereWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, {0.0f,conicalPendulum.halfApexAngle,conicalPendulum.halfApexAngle},{}) * pointWorldMatrix;

		point = { pointWorldMatrix.m[3][0],pointWorldMatrix.m[3][1] ,pointWorldMatrix.m[3][2] };
		sphere.center = { sphereWorldMatrix.m[3][0],sphereWorldMatrix.m[3][1] ,sphereWorldMatrix.m[3][2] };

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
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
		Vec3 start = Transform(conicalPendulum.anchor, viewProjectionMatrix * viewportMatrix);
		Vec3 end = Transform(point, viewProjectionMatrix * viewportMatrix);
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
