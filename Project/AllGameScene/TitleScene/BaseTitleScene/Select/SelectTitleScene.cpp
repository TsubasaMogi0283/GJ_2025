#include "SelectTitleScene.h"

#include <imgui.h>

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "TitleScene/TitleScene.h"
#include <TitleScene/BaseTitleScene/ToGame/ToGameTitleScene.h>
#include <TitleScene/BaseTitleScene/Finish/FinishTitleScene.h>
#include <Easing.h>
#include <SingleCalculation.h>

SelectTitleScene::SelectTitleScene(){

	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
}

void SelectTitleScene::Initialize(){
	//初期座標の取得
	startInitialPosition_ = levelDataManager_->GetInitialTranslate(levelDataHandle_,START_);
	endInitialPosition_ = levelDataManager_->GetInitialTranslate(levelDataHandle_, END_);
	arrowInitialPosition_=levelDataManager_->GetInitialTranslate(levelDataHandle_, ARROW_);

	isArrowUp_ = true;

	pointLight_.radius = MAX_RADIUS_;
	camera_.translate.y = 1.4f;
	camera_.translate.z = -9.8f;
}

void SelectTitleScene::Update(TitleScene* titleScene){

	
	
	//上
	if ((input_->IsPushKey(DIK_UP) == true) || 
		(input_->IsPushKey(DIK_W) == true) || 
		(input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_UP) == true)) {
		isArrowUp_ = true;
		isArrowDown_ = false;
	}
	//下
	if ((input_->IsPushKey(DIK_DOWN) == true) ||
		(input_->IsPushKey(DIK_S) == true) ||
		(input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_DOWN) == true)) {
		isArrowUp_ = false;
		isArrowDown_ = true;
	}

	if (isArrowUp_ == true) {
		const float_t OFFSET = 0.1f;
		arrowPosition_.y = startInitialPosition_.y+OFFSET;
	}
	if (isArrowDown_ == true) {
		const float_t OFFSET = 0.1f;
		arrowPosition_.y = endInitialPosition_.y+OFFSET;
	}

	//XZはそのままの座標にする
	arrowPosition_.x = arrowInitialPosition_.x;
	arrowPosition_.z = arrowInitialPosition_.z;
	
	//矢印の設定
	levelDataManager_->SetRotate(levelDataHandle_, ARROW_, arrowRotate_);
	levelDataManager_->SetTranslate(levelDataHandle_, ARROW_, arrowPosition_);
	




	if (input_->IsPushKey(DIK_SPACE) == true || input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_DOWN) == true) {
		isDecice_ = true;
	}


	if (isDecice_ == true) {
		//高速回転
		rapidRotateTime_ += DELTA_TIME;

		//高速回転
		if (isRapidRotate_ == true) {
			arrowRotate_.x += RAPID_ROTATE_VALUE_;
			if (rapidRotateTime_ > 1.5f) {
				isRapidRotate_ = false;
			}
		}
		//高速回転終了
		else {
			rotateT_ += INCREASE_T_VALUE_;
			rotateT_ = std::clamp(rotateT_, 0.0f, 1.0f);
			float_t newRotateT = Easing::EaseOutBack(rotateT_);
			
			t = SingleCalculation::Lerp(RAPID_ROTATE_VALUE_, 0.0f, newRotateT);
			arrowRotate_.x += t;
		}
	}
	else {
		arrowRotate_.x += 0.1f;
	}

	if (rotateT_ >= 1.0f) {
		changeWaitingTime_ += DELTA_TIME;

		if (changeWaitingTime_ >= 1.0f) {
			if (isArrowUp_ == true) {
				titleScene->ChangeDetailScene(std::make_unique<ToGameTitleScene>());
				return;
			}
			if (isArrowDown_ == true) {
				titleScene->ChangeDetailScene(std::make_unique<FinishTitleScene>());
				return;
			}
		}
		
	}


	
	
#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG

}

void SelectTitleScene::DrawSprite(){
}

void SelectTitleScene::DisplayImGui(){
	ImGui::Begin("ゲームシーンへ(タイトル)");
	ImGui::InputFloat("A", &t);
	ImGui::InputFloat("回転T", &rotateT_);
	ImGui::Checkbox("上", &isArrowUp_);
	ImGui::Checkbox("下", &isArrowDown_);
	ImGui::InputFloat("高速回転時間", &rapidRotateTime_);
	ImGui::Checkbox("高速回転", &isRapidRotate_);
	ImGui::End();

}
