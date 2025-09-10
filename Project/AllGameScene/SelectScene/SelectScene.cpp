#include "SelectScene.h"

#include <imgui.h>

#include "Input.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "LevelDataManager.h"
#include "Audio.h"
#include "GameManager.h"
#include "VectorCalculation.h"
#include <SingleCalculation.h>
#include "GlobalVariables.h"
#include "Easing.h"
#include <SelectedStageInformation/SelectedStageInformation.h>

SelectScene::SelectScene(){

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

void SelectScene::Initialize(){

	//負けシーン用のレベルデータを入れる
	levelDataHandle_ = levelDataManager_->Load("SelectStage/SelectStage.json");
	

	//背景(ポストエフェクト)
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	const Vector4 CLEAR_COLOR = { .x = 0.0f,.y = 0.0f,.z = 0.0f,.w = 1.0f };
	backTexture_->SetClearColour(CLEAR_COLOR);
	backTexture_->Initialize();

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 2.8f,.z = -23.0f };

	//初期化
	pointLight_.Initialize();


	stageNumber_ = 1u;

	//初期座標を取得
	initialPosition_ = levelDataManager_->GetInitialTranslate(levelDataHandle_, one_);
	numberPositions_[0]= levelDataManager_->GetInitialTranslate(levelDataHandle_, returnString_);
	numberPositions_[1] = levelDataManager_->GetInitialTranslate(levelDataHandle_, one_);
	numberPositions_[2] = levelDataManager_->GetInitialTranslate(levelDataHandle_, two_);
	numberPositions_[3] = levelDataManager_->GetInitialTranslate(levelDataHandle_, three_);
	numberPositions_[4] = levelDataManager_->GetInitialTranslate(levelDataHandle_, four_);
	numberPositions_[5] = levelDataManager_->GetInitialTranslate(levelDataHandle_, five_);
	numberPositions_[6] = levelDataManager_->GetInitialTranslate(levelDataHandle_, six_);
	numberPositions_[7] = levelDataManager_->GetInitialTranslate(levelDataHandle_, seven_);
	numberPositions_[8] = levelDataManager_->GetInitialTranslate(levelDataHandle_, eight_);
	numberPositions_[9] = levelDataManager_->GetInitialTranslate(levelDataHandle_, nine_);


}

void SelectScene::Update(Elysia::GameManager* gameManager){

	gameManager;

	if (isDecide_ == false) {
		//左
		if (input_->IsTriggerKey(DIK_LEFT) == true ||
			input_->IsTriggerKey(DIK_A) == true ||
			input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_LEFT) == true) {

			if (stageNumber_ > 0u) {
				moveInterval_.x += INTERVAL_;
				stageNumber_--;
			}

		}

		//右
		if (input_->IsTriggerKey(DIK_RIGHT) == true ||
			input_->IsTriggerKey(DIK_D) == true ||
			input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true) {
			if (stageNumber_ < 5u) {
				moveInterval_.x -= INTERVAL_;
				stageNumber_++;
			}
		}

		std::array<Vector3, NUMBER_QUANTITY_>numberScales = {
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
		};

		for (uint8_t i = 1; i < NUMBER_QUANTITY_; ++i) {
			if (i == stageNumber_) {
				numberScales[i] = SELECTED_SCALE_;
				break;
			}
		}

		//スケールの設定
		levelDataManager_->SetScale(levelDataHandle_, one_, numberScales[1]);
		levelDataManager_->SetScale(levelDataHandle_, two_, numberScales[2]);
		levelDataManager_->SetScale(levelDataHandle_, three_, numberScales[3]);
		levelDataManager_->SetScale(levelDataHandle_, four_, numberScales[4]);
		levelDataManager_->SetScale(levelDataHandle_, five_, numberScales[5]);
		levelDataManager_->SetScale(levelDataHandle_, six_, numberScales[6]);
		levelDataManager_->SetScale(levelDataHandle_, seven_, numberScales[7]);
		levelDataManager_->SetScale(levelDataHandle_, eight_, numberScales[8]);
		levelDataManager_->SetScale(levelDataHandle_, nine_, numberScales[9]);

		//座標
		levelDataManager_->SetTranslate(levelDataHandle_, returnString_, VectorCalculation::Add(numberPositions_[0], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, one_, VectorCalculation::Add(numberPositions_[1], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, two_, VectorCalculation::Add(numberPositions_[2], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, three_, VectorCalculation::Add(numberPositions_[3], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, four_, VectorCalculation::Add(numberPositions_[4], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, five_, VectorCalculation::Add(numberPositions_[5], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, six_, VectorCalculation::Add(numberPositions_[6], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, seven_, VectorCalculation::Add(numberPositions_[7], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, eight_, VectorCalculation::Add(numberPositions_[8], moveInterval_));
		levelDataManager_->SetTranslate(levelDataHandle_, nine_, VectorCalculation::Add(numberPositions_[9], moveInterval_));

		//決定
		if (input_->IsTriggerKey(DIK_SPACE) == true || input_->IsTriggerButton(XINPUT_GAMEPAD_B) == true) {
			isDecide_ = true;
			SelectedStageInformation::GetInstance()->RecordSelectedStageNumber(stageNumber_);
		}

	}
	else {
		std::array<Vector3, NUMBER_QUANTITY_>numberScales = {
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
			INITIAL_SCALE_,
		};
		std::array<Vector3, NUMBER_QUANTITY_>numberRotates = {};

		changeT_ += INCREASE_T_VALUE_;
		for (uint8_t i = 0; i < NUMBER_QUANTITY_; ++i) {
			if (i != stageNumber_) {
				changeT_ = std::clamp(changeT_, 0.0f, 1.0f);
				numberScales[i] = VectorCalculation::Lerp(INITIAL_SCALE_, { 0.0f,0.0f,0.0f }, changeT_);
			}
			else {
				numberRotates[i] = VectorCalculation::Lerp({}, DECIDED_ROTATE_, changeT_);
				numberScales[i] = VectorCalculation::Lerp(SELECTED_SCALE_, DECIDED_SCALE_, changeT_);
			}
		}



		//スケールの設定
		levelDataManager_->SetScale(levelDataHandle_, returnString_, numberScales[0]);
		levelDataManager_->SetScale(levelDataHandle_, one_, numberScales[1]);
		levelDataManager_->SetScale(levelDataHandle_, two_, numberScales[2]);
		levelDataManager_->SetScale(levelDataHandle_, three_, numberScales[3]);
		levelDataManager_->SetScale(levelDataHandle_, four_, numberScales[4]);
		levelDataManager_->SetScale(levelDataHandle_, five_, numberScales[5]);
		levelDataManager_->SetScale(levelDataHandle_, six_, numberScales[6]);
		levelDataManager_->SetScale(levelDataHandle_, seven_, numberScales[7]);
		levelDataManager_->SetScale(levelDataHandle_, eight_, numberScales[8]);
		levelDataManager_->SetScale(levelDataHandle_, nine_, numberScales[9]);


		//回転の設定
		levelDataManager_->SetRotate(levelDataHandle_, one_, numberRotates[1]);
		levelDataManager_->SetRotate(levelDataHandle_, two_, numberRotates[2]);
		levelDataManager_->SetRotate(levelDataHandle_, three_, numberRotates[3]);
		levelDataManager_->SetRotate(levelDataHandle_, four_, numberRotates[4]);
		levelDataManager_->SetRotate(levelDataHandle_, five_, numberRotates[5]);
		levelDataManager_->SetRotate(levelDataHandle_, six_, numberRotates[6]);
		levelDataManager_->SetRotate(levelDataHandle_, seven_, numberRotates[7]);
		levelDataManager_->SetRotate(levelDataHandle_, eight_, numberRotates[8]);
		levelDataManager_->SetRotate(levelDataHandle_, nine_, numberRotates[9]);
	}
	

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
	if (input_->IsTriggerKey(DIK_R) == true) {
		levelDataManager_->Reload(levelDataHandle_);
	}

#endif // _DEBUG
}


void SelectScene::DrawObject3D(){
	//レベルデータ
	levelDataManager_->Draw(levelDataHandle_, camera_);
}

void SelectScene::PreDrawPostEffect(){
	backTexture_->PreDraw();
}

void SelectScene::DrawPostEffect(){
	backTexture_->Draw();
}

void SelectScene::DrawSprite(){

}



void SelectScene::DisplayImGui(){

	ImGui::Begin("選択");
	ImGui::InputFloat("決定時の線形補間", &changeT_);
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

