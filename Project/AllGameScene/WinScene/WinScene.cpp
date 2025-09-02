#include "WinScene.h"

#include <imgui.h>

#include "TextureManager.h"
#include "LevelDataManager.h"
#include "GameManager.h"
#include "Input.h"
#include "Audio.h"
#include "VectorCalculation.h"


WinScene::WinScene(){
	//インスタンスの取得
	//レベルデータ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void WinScene::Initialize() {

	//レベルデータの読み込み
	levelDataHandle_ = levelDataManager_->Load("WinStage/WinStage.json");


	//平行光源の初期化
	directionalLight_.Initialize();
	directionalLight_.color = { .x = 1.0f,.y = 0.22f,.z = 0.0f,.w = 1.0f };
	directionalLight_.direction = { .x = 0.91f,.y = -1.0f,.z = 0.0f };

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 2.0f,.z = -6.0f };
	//ポストエフェクト
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	backTexture_->SetClearColour(directionalLight_.color);
	backTexture_->Initialize();

}

void WinScene::Update(Elysia::GameManager* gameManager){
	gameManager;

	//平行光源の更新
	directionalLight_.Update();
	//カメラの更新
	camera_.Update();

	//レベルデータの更新
	levelDataManager_->Update(levelDataHandle_);

	
}

void WinScene::PreDrawPostEffect(){
	backTexture_->PreDraw();
}

void WinScene::DrawObject3D(){

}

void WinScene::DrawPostEffect(){
	backTexture_->Draw();
}

void WinScene::DrawSprite(){
}
