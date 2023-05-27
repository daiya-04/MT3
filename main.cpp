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

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vec3 point{ -1.5f,0.6f,0.6f };

	

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

		Vec3 project = Project(Sub(point, segment.origin), segment.diff);
		Vec3 closestPoint = ClosestPoint(point, segment);

		Sphere pointSphere{ point,0.01f };
		Sphere closestPointSphere{ closestPoint,0.01f };

		Matrix44 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix44 viewMatrix = Inverse(cameraMatrix);
		Matrix44 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix44 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix44 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight));

		Vec3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vec3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);


		ImGui::Begin("Window");
		ImGui::DragFloat3("Point", &point.x, 0.01f);
		ImGui::DragFloat3("Segment origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment diff", &segment.diff.x, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), 0xFFFFFFFF);
		DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, 0xFF0000FF);
		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, 0x000000FF);
		


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
