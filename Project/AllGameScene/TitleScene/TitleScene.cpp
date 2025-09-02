#include "TitleScene.h"
#include <imgui.h>
#include <numbers>
#include <array>

#include "Input.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "Audio.h"
#include "VectorCalculation.h"
#include "SingleCalculation.h"
#include "Calculation/QuaternionCalculation.h"


TitleScene::TitleScene() {
	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void TitleScene::Initialize() {

	//平行光源
	directionalLight_.Initialize();
	directionalLight_.color = { .x = 1.0f,.y = 0.22f,.z = 0.0f,.w = 1.0f };
	directionalLight_.direction = { .x = 0.91f,.y = -1.0f,.z = 0.0f };


	//カメラの初期化
	camera_.Initialize();

	backTexture_ = std::make_unique<Elysia::BackTexture>();
	backTexture_->SetClearColour({ .x = 0.0f,.y = 0.5f,.z = 0.7f,.w = 1.0f });
	backTexture_->Initialize();

}

void TitleScene::Update(Elysia::GameManager* gameManager) {
	//平行光源の更新
	directionalLight_.Update();

	//カメラの更新
	camera_.Update();
	//処理を終えたらゲームシーンへ
	if(false) {
		gameManager->ChangeScene("Game");
		return;
	}
	
#ifdef _DEBUG
	//ImGui用
	DisplayImGui();
#endif
}

void TitleScene::DrawObject3D() {
	//ステージオブジェクト
	levelDataManager_->Draw(levelHandle_, camera_, directionalLight_);

}

void TitleScene::PreDrawPostEffect() {

	backTexture_->PreDraw();
}

void TitleScene::DrawPostEffect() {
	backTexture_->Draw();
}

void TitleScene::DrawSprite() {


}

void TitleScene::DisplayImGui() {
	ImGui::Begin("タイトル");

	ImGui::End();

}

