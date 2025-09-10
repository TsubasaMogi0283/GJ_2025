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
#include <TitleScene/BaseTitleScene/Start/StartTitleScene.h>

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

	//ステージオブジェクト
	levelHandle_ = levelDataManager_->Load("TitleStage/TitleStage.json");

	//平行光源
	pointLight_.Initialize();
	pointLight_.color = { .x = 1.0f,.y = 1.0f,.z = 1.0f,.w = 1.0f };
	pointLight_.decay = 1.2f;

	//カメラの初期化
	camera_.Initialize();
	camera_.translate.y = 1.4f;

	//マスクテクスチャ
	uint32_t maskTexture = textureManager_->Load("Resources/External/Texture/Dissolve/noise0.png");

	//ディゾルブ
	dissolve_.Initialize();
	dissolve_.maskTextureHandle = maskTexture;
	dissolve_.threshold = 0.0f;
	dissolve_.edgeThinkness = 0.0f;
	//ポストエフェクト
	dissolvePostEffect_ = std::make_unique<Elysia::DissolvePostEffect>();
	dissolvePostEffect_->Initialize({ .x = 0.0f,.y = 0.0f,.z = 0.0f,.w = 1.0f });

	detailScene_ = std::make_unique<StartTitleScene>();
	detailScene_->SetLevelDataHandle(levelHandle_);
	detailScene_->Initialize();




}

void TitleScene::Update(Elysia::GameManager* gameManager) {
	//詳細シーンの更新
	detailScene_->Update(this);
	
	//レベルエディターの更新
	levelDataManager_->Update(levelHandle_);

	//平行光源の更新
	pointLight_.radius = detailScene_->GetPointLight().radius;
	pointLight_.Update();
	//ディゾルブの更新
	dissolve_.threshold = detailScene_->GetDissolve().threshold;
	dissolve_.Update();

	//カメラの更新
	camera_.translate = detailScene_->GetCamera().translate;
	camera_.Update();
	
	//ゲーム終了
	if (isEnd_ == true) {
		if (isGameEnd_ == true) {
			gameManager->SetIsGameEnd(true);
			return;
		}
		else {
			gameManager->ChangeScene("Select");
			return;
		}
	}

#ifdef _DEBUG
	//再読み込み
	if (input_->IsTriggerKey(DIK_R) == true) {
		levelDataManager_->Reload(levelHandle_);
	}
	//ImGui用
	DisplayImGui();
#endif
}

void TitleScene::DrawObject3D() {
	//ステージオブジェクト
	levelDataManager_->Draw(levelHandle_, camera_, pointLight_);
}

void TitleScene::PreDrawPostEffect() {
	dissolvePostEffect_->PreDraw();
}

void TitleScene::DrawPostEffect() {
	dissolvePostEffect_->Draw(dissolve_);
}

void TitleScene::DrawSprite() {
	detailScene_->DrawSprite();
}

void TitleScene::ChangeDetailScene(std::unique_ptr<BaseTitleScene> detailScene){
	//違った時だけ遷移する
	if (detailScene_ != detailScene) {
		detailScene_ = std::move(detailScene);
		//次に遷移する
		detailScene_->SetLevelDataHandle(levelHandle_);
		detailScene_->Initialize();
	}
}

void TitleScene::DisplayImGui() {
	ImGui::Begin("タイトル");
	if (ImGui::TreeNode("点光源")) {
		ImGui::SliderFloat3("座標", &pointLight_.position.x, -40.0f, 40.0f);
		ImGui::SliderFloat("Decay", &pointLight_.decay, 0.0f, 20.0f);
		ImGui::SliderFloat("半径", &pointLight_.radius, 0.0f, 20.0f);
		ImGui::TreePop();

	}

	if (ImGui::TreeNode("ディゾルブ")) {
		ImGui::SliderFloat("しきい値", &dissolve_.threshold, 0.0f, 2.0f);
		ImGui::SliderFloat("厚さ", &dissolve_.edgeThinkness, 0.0f, 2.0f);
		ImGui::TreePop();

	}
	if (ImGui::TreeNode("カメラ")) {
		ImGui::SliderFloat3("座標", &camera_.translate.x, -40.0f, 40.0f);
		ImGui::SliderFloat3("回転", &camera_.rotate.x, -3.0f, 3.0f);
		ImGui::TreePop();
	}

	ImGui::End();

}

