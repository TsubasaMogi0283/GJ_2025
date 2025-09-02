#include "LoseScene.h"

#include <imgui.h>

#include "Input.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "LevelDataManager.h"
#include "Audio.h"
#include "GameManager.h"
#include "VectorCalculation.h"
#include "GlobalVariables.h"
#include "Easing.h"


LoseScene::LoseScene(){

	//インスタンスの取得
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルデータ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//グローバル変数クラス
	globalVariables_ = Elysia::GlobalVariables::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void LoseScene::Initialize(){

	//負けシーン用のレベルデータを入れる
	levelDataHandle_ = levelDataManager_->Load("LoseStage/LoseStage.json");
	

	//背景(ポストエフェクト)
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	const Vector4 CLEAR_COLOR = { .x = 0.0f,.y = 0.0f,.z = 1.0f,.w = 1.0f };
	backTexture_->SetClearColour(CLEAR_COLOR);
	backTexture_->Initialize();

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 2.8f,.z = -23.0f };

	//初期化
	pointLight_.Initialize();

}

void LoseScene::Update(Elysia::GameManager* gameManager){

	gameManager;
	//レベルデータの更新
	levelDataManager_->Update(levelDataHandle_);

	//カメラの更新
	camera_.Update();
	//点光源の更新
	pointLight_.Update();
#ifdef _DEBUG
	//ImGui
	DisplayImGui();
	
	//再読み込み
	if (input_->IsTriggerKey(DIK_L) == true) {
		levelDataManager_->Reload(levelDataHandle_);
	}

#endif // _DEBUG
}


void LoseScene::DrawObject3D(){
}

void LoseScene::PreDrawPostEffect(){
	backTexture_->PreDraw();
}

void LoseScene::DrawPostEffect(){
	backTexture_->Draw();
}

void LoseScene::DrawSprite(){

}



void LoseScene::DisplayImGui(){

	ImGui::Begin("脱出失敗シーン");
	if (ImGui::TreeNode("点光源")) {
		ImGui::SliderFloat3("座標", &pointLight_.position.x, -40.0f, 40.0f);
		ImGui::SliderFloat("Decay", &pointLight_.decay, 0.0f, 20.0f);
		ImGui::SliderFloat("半径", &pointLight_.radius, 0.0f, 20.0f);
		ImGui::TreePop();
		
	}
	if (ImGui::TreeNode("カメラ")) {
		ImGui::SliderFloat3("座標", &camera_.translate.x, -40.0f, 40.0f);
		ImGui::TreePop();
	}

	ImGui::End();
	

}

