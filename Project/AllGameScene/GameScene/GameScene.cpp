#include "GameScene.h"

#include <imgui.h>
#include <numbers>
#include <algorithm>

#include "Input.h"
#include "SingleCalculation.h"
#include "VectorCalculation.h"
#include "PushBackCalculation.h"
#include "AnimationManager.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "ModelManager.h"
#include "LevelDataManager.h"
#include "GlobalVariables.h"
#include "Audio.h"


GameScene::GameScene() {
	//インスタンスの取得
	//入力	
	input_ = Elysia::Input::GetInstance();
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//モデル管理クラス
	modelManager_ = Elysia::ModelManager::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//グローバル変数クラス
	globalVariables_ = Elysia::GlobalVariables::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void GameScene::Initialize() {

	//ハンドルの取得
	levelHandle_ = levelDataManager_->Load("GameStage/GameStage.json");

	//生成
	player_ = std::make_unique<Player>();
	//初期化
	player_->Initialize();
	//ハンドルの設定
	player_->SetLevelHandle(levelHandle_);
	//最初はコントロールは出来ない用にする
	player_->SetIsAbleToControll(false);

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 2.0f,.z = -5.0f };

	//スポットライト
	spotLight_.Initialize();
	spotLight_.direction = { 0.0f,0.0f,1.0f };

	//ポストエフェクトの初期化
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	//初期化
	backTexture_->SetClearColour({ 1.0f,0.0f,0.0f,1.0f });
	backTexture_->Initialize();
	
	uint32_t modelHandle = modelManager_->Load("Resources/LevelData/GameStage/Cube", "cube.obj");
	model_.reset(Elysia::Model::Create(modelHandle));

	worldTransform_.Initialize();
	worldTransform_.translate.z = 3.0f;


	material_.Initialize();
	material_.lightingKinds = LightingType::NoneLighting;
}


void GameScene::DisplayImGui() {

	ImGui::Begin("ゲームシーン");

	if (ImGui::TreeNode("カメラ") == true) {
		ImGui::SliderFloat3("座標", &camera_.translate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("回転", &camera_.rotate.x, -3.0f, 3.0f);
		ImGui::TreePop();

	}
	
	ImGui::End();

}

void GameScene::Update(Elysia::GameManager* gameManager) {
	gameManager;

	//プレイヤーの更新
	if (input_->IsPushButton(DIK_UP) == true) {
		playerDirection_.z = 1.0f;
	}
	if (input_->IsPushButton(DIK_DOWN) == true) {
		playerDirection_.z = -1.0f;
	}
	if (input_->IsPushButton(DIK_RIGHT) == true) {
		playerDirection_.x = 1.0f;
	}
	if (input_->IsPushButton(DIK_LEFT) == true) {
		playerDirection_.x = -1.0f;
	}

	//方向取得
	player_->SetMoveDirection(playerDirection_);
	//更新
	player_->Update();
	//カメラの更新
	camera_.Update();
	
	//ライトの更新
	spotLight_.Update();
	worldTransform_.Update();
	material_.Update();

	levelDataManager_->Update(levelHandle_);
#ifdef _DEBUG 

	//再読み込み
	if (input_->IsTriggerKey(DIK_R) == true) {
		levelDataManager_->Reload(levelHandle_);
	}
	//ImGuiの表示
	DisplayImGui();

#endif // _DEBUG
}

void GameScene::PreDrawPostEffect() {
	//ビネット描画処理前
	backTexture_->PreDraw();
}

void GameScene::DrawObject3D() {
	levelDataManager_->Draw(levelHandle_, camera_, spotLight_);

	model_->Draw(worldTransform_, camera_, material_);

}

void GameScene::DrawPostEffect() {
	//ビネット描画
	backTexture_->Draw();
}

void GameScene::DrawSprite() {
}
