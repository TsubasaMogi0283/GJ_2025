#include "StartTitleScene.h"

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "WindowsSetup.h"
#include "Audio.h"

#include "TitleScene/TitleScene.h"
#include <TitleScene/BaseTitleScene/Select/SelectTitleScene.h>
#include <SingleCalculation.h>
#include <VectorCalculation.h>

StartTitleScene::StartTitleScene(){
	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//ウィンドウクラス
	windowsSetup_ = Elysia::WindowsSetup::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void StartTitleScene::Initialize(){

	//名前の設定
	textInformations_[TextCharacter::Syo].name_ = textSyo_;
	textInformations_[TextCharacter::Kai].name_ = textKai_;
	textInformations_[TextCharacter::Mei].name_ = textMei_;
	textInformations_[TextCharacter::Ro].name_ = textRo_;

	//初期座標の設定
	textInformations_[TextCharacter::Syo].initialPosition=levelDataManager_->GetInitialTranslate(levelDataHandle_, textSyo_);
	textInformations_[TextCharacter::Kai].initialPosition=levelDataManager_->GetInitialTranslate(levelDataHandle_, textKai_);
	textInformations_[TextCharacter::Mei].initialPosition=levelDataManager_->GetInitialTranslate(levelDataHandle_, textMei_);
	textInformations_[TextCharacter::Ro].initialPosition=levelDataManager_->GetInitialTranslate(levelDataHandle_, textRo_);

	//待機座標の設定
	textInformations_[TextCharacter::Syo].waitingPosition = levelDataManager_->GetInitialTranslate(levelDataHandle_, textSyo_);
	textInformations_[TextCharacter::Syo].waitingPosition.z= waitingPositionZ_;
	textInformations_[TextCharacter::Kai].waitingPosition = levelDataManager_->GetInitialTranslate(levelDataHandle_, textKai_);
	textInformations_[TextCharacter::Kai].waitingPosition.z=waitingPositionZ_;
	textInformations_[TextCharacter::Mei].waitingPosition = levelDataManager_->GetInitialTranslate(levelDataHandle_, textMei_);
	textInformations_[TextCharacter::Mei].waitingPosition.z=waitingPositionZ_;
	textInformations_[TextCharacter::Ro].waitingPosition = levelDataManager_->GetInitialTranslate(levelDataHandle_, textRo_);
	textInformations_[TextCharacter::Ro].waitingPosition.z= waitingPositionZ_;

	Vector3 e = textInformations_[TextCharacter::Syo].initialPosition;
	start = textInformations_[TextCharacter::Syo].waitingPosition;

	//新しく座標の設定
	//待機の方を入れる
	levelDataManager_->SetTranslate(levelDataHandle_, textInformations_[TextCharacter::Syo].name_, textInformations_[TextCharacter::Syo].waitingPosition);
	levelDataManager_->SetTranslate(levelDataHandle_, textInformations_[TextCharacter::Kai].name_, textInformations_[TextCharacter::Kai].waitingPosition);
	levelDataManager_->SetTranslate(levelDataHandle_, textInformations_[TextCharacter::Mei ].name_, textInformations_[TextCharacter::Mei].waitingPosition);
	levelDataManager_->SetTranslate(levelDataHandle_, textInformations_[TextCharacter::Ro].name_, textInformations_[TextCharacter::Ro].waitingPosition);


}

void StartTitleScene::Update(TitleScene* titleScene){
	
	//ライトアップ中
	if (isEndLightUp_ == false) {
		//線形補間で増やす

		radiusT_ += INCREASE_T_VALUE_;
		radiusT_ = std::clamp(radiusT_, 0.0f, 1.0f);
		pointLight_.radius = SingleCalculation::Lerp(MIN_, MAX_RADIUS_, radiusT_);

		//ライトアップ完了
		if (radiusT_>=1.0f) {
			isEndLightUp_=true;
		}
	}
	//ライトアップ完了後
	else {
		//移動開始タイマー
		moveStartTimer_ += DELTA_TIME;
		//1秒ごとに移動開始
		if (moveStartTimer_ > 1.0f&& releaseTextNumber_<4) {
			moveStartTimer_ = 0.0f;
			//動き始める
			textInformations_[releaseTextNumber_].isStartMove_ = true;
			releaseTextNumber_++;
			
		}


		for (uint8_t i = 0u; i < TEXT_QUANTITY_; i++) {
			//動き始めたものだけ通す
			if (textInformations_[i].isStartMove_ == true) {
				//線形補間
				textInformations_[i].positionT_ += 0.01f;
				textInformations_[i].positionT_ = std::clamp(textInformations_[i].positionT_, 0.0f, 1.0f);

				//待機から初期へ進んで行く
				Vector3 position = VectorCalculation::Lerp(textInformations_[i].waitingPosition, textInformations_[i].initialPosition, textInformations_[i].positionT_);
				//座標の設定
				levelDataManager_->SetTranslate(levelDataHandle_, textInformations_[i].name_, position);

				//移動終了
				if (textInformations_[i].positionT_ >= 1.0f) {
					//移動終了
					textInformations_[i].isEndMove_ = true;
					textInformations_[i].isStartMove_ = false;
				}
			}
		}

	}

	

	titleScene;

#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG


}


void StartTitleScene::DrawSprite(){

}

void StartTitleScene::DisplayImGui(){
	ImGui::Begin("開始(タイトル)");
	ImGui::InputFloat("半径", &pointLight_.radius);
	ImGui::Checkbox("ライトアップ", &isEndLightUp_);
	ImGui::InputFloat("移動開始時間", &moveStartTimer_);
	ImGui::InputFloat("TP", &textInformations_[0].positionT_);
	int32_t num=static_cast<int32_t>(releaseTextNumber_);
	ImGui::InputInt("移動開始下番号", &num);
	ImGui::End();


	
}
