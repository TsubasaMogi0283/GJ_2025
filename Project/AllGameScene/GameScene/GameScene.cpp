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

	//ポストエフェクトの初期化
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	//初期化
	backTexture_->SetClearColour({ 1.0f,0.0f,0.0f,1.0f });
	backTexture_->Initialize();
	
}


void GameScene::DisplayImGui() {

	ImGui::Begin("ゲームシーン");

	if (ImGui::TreeNode("ビネット")==true) {
		ImGui::TreePop();
	}

	ImGui::End();

}

void GameScene::Update(Elysia::GameManager* gameManager) {
	gameManager;

	//プレイヤーの更新
	player_->Update();
	//カメラの更新
	//転送
	camera_.Update();
	
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


}

void GameScene::DrawPostEffect() {
	//ビネット描画
	backTexture_->Draw();
}

void GameScene::DrawSprite() {
}
