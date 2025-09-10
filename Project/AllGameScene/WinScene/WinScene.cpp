#include "WinScene.h"

#include <imgui.h>

#include "TextureManager.h"
#include "LevelDataManager.h"
#include "GameManager.h"
#include "Input.h"
#include "Audio.h"
#include "VectorCalculation.h"
#include <TextureManager.h>
#include <SelectedStageInformation/SelectedStageInformation.h>

WinScene::WinScene(){
	//インスタンスの取得
	//レベルデータ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
}

void WinScene::Initialize() {

	//レベルデータの読み込み
	levelDataHandle_ = levelDataManager_->Load("ResultStage/ResultStage.json");


	//平行光源の初期化
	directionalLight_.Initialize();
	directionalLight_.color = { .x = 1.0f,.y = 0.22f,.z = 0.0f,.w = 1.0f };
	directionalLight_.direction = { .x = 0.91f,.y = -1.0f,.z = 0.0f };

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 1.2f,.z = -10.0f };
	//ポストエフェクト
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	backTexture_->SetClearColour(directionalLight_.color);
	backTexture_->Initialize();

	uint32_t whiteTextureHandle = Elysia::TextureManager::GetInstance()->Load("Resources/Sprite/Back/White.png");
	whiteFade_.reset(Elysia::Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));
	whiteFade_->SetTransparency(0.0f);
	//初期化は左
	isLeft_ = true;

	decideSEhandle_ = audio_->Load("Resources/Audio/SE/Deside.wav");
	selectSEHandle_ = audio_->Load("Resources/Audio/SE/Select.wav");

	winBgmHandle_ = audio_->Load("Resources/Audio/Win/WinBGM.wav");
	audio_->Play(winBgmHandle_, true);
	bgmVolume_ = 1.0f;
	audio_->ChangeVolume(winBgmHandle_, bgmVolume_);
}

void WinScene::Update(Elysia::GameManager* gameManager){
	
	if (isDecide_ == false) {

		//左
		if (isLeft_ == true) {
			//大きく回転
			leftScale_ = SELECTED_SCALE_;			
			leftRotate_ += NORMAL_ROTATE_AMOUNT_;
			
			//右は縮小と無回転
			rightScale_ = INITIAL_SCALE_;
			rightRotate_ = 0.0f;

		}
		//右
		if (isRight_ == true) {
			//大きく回転
			rightScale_ = SELECTED_SCALE_;
			rightRotate_ += NORMAL_ROTATE_AMOUNT_;

			//左は縮小と無回転
			leftScale_ = INITIAL_SCALE_;
			leftRotate_ = 0.0f;

			
		}

		//スケールの設定
		levelDataManager_->SetScale(levelDataHandle_, NEXT_, leftScale_);
		levelDataManager_->SetScale(levelDataHandle_, TITLE_, rightScale_);

		//回転の設定
		levelDataManager_->SetRotate(levelDataHandle_, NEXT_, { 0.0f,leftRotate_,0.0f });
		levelDataManager_->SetRotate(levelDataHandle_, TITLE_, { 0.0f,rightRotate_,0.0f });

		//左
		if (input_->IsTriggerKey(DIK_LEFT) == true ||
			input_->IsTriggerKey(DIK_A) == true ||
			input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_LEFT) == true) {
			isLeft_ = true;
			isRight_ = false;
			audio_->Play(selectSEHandle_, false);
		}
		//右
		if (input_->IsTriggerKey(DIK_RIGHT) == true ||
			input_->IsTriggerKey(DIK_D) == true ||
			input_->IsTriggerButton(XINPUT_GAMEPAD_DPAD_RIGHT) == true) {
			isRight_ = true;
			isLeft_ = false;
			audio_->Play(selectSEHandle_, false);
		}


		//決定
		if (input_->IsTriggerKey(DIK_SPACE) == true || input_->IsTriggerButton(XINPUT_GAMEPAD_B) == true) {
			isDecide_ = true;
			audio_->Play(decideSEhandle_, false);
		}

	}
	else {

		scaleDownT_ += 0.01f;
		if (isLeft_ == true) {
			//縮小
			rightScale_ = VectorCalculation::Lerp( rightScale_, { 0.0f,0.0f,0.0f },scaleDownT_);
		}
		if (isRight_ == true) {
			//縮小
			leftScale_ = VectorCalculation::Lerp(leftScale_, { 0.0f,0.0f,0.0f }, scaleDownT_);
			
		}
		bgmVolume_ = 1.0f - scaleDownT_;
		if (bgmVolume_ <= 0.0f) {
			bgmVolume_ = 0.0f;
		}
		

		if (scaleDownT_ < 1.0f) {
			leftRotate_ += RAPID_ROTATE_AMOUNT_;
			rightRotate_ += RAPID_ROTATE_AMOUNT_;
		}
		else {
			audio_->Stop(winBgmHandle_);

			leftRotate_ += NORMAL_ROTATE_AMOUNT_;
			rightRotate_ += NORMAL_ROTATE_AMOUNT_;
			isCameraMove_ = true;
		}

		if (isCameraMove_ == true) {
			//カメラ加速
			cameraVelocity_ += cameraAccel_;
			camera_.translate.z += cameraVelocity_;

			//フェード
			whiteTramsparency_ += FADE_AMOUNT_;
			whiteFade_->SetTransparency(whiteTramsparency_);
			if (whiteTramsparency_ >= 2.0f) {
				if (isLeft_ == true) {

					uint8_t nextNumber=SelectedStageInformation::GetInstance()->GetRecordedNumber()+1u;
					SelectedStageInformation::GetInstance()->RecordSelectedStageNumber(nextNumber);
					gameManager->ChangeScene("Game");
					return;
				}
				if (isRight_ == true) {
					gameManager->ChangeScene("Title");
					return;
				}
				
			}


		}
		

		//スケールの設定
		levelDataManager_->SetScale(levelDataHandle_, NEXT_, leftScale_);
		levelDataManager_->SetScale(levelDataHandle_, TITLE_, rightScale_);
		//回転の設定
		levelDataManager_->SetRotate(levelDataHandle_, NEXT_, { 0.0f,leftRotate_ ,0.0f });
		levelDataManager_->SetRotate(levelDataHandle_, TITLE_, {0.0f,rightRotate_ ,0.0f});
	}
	//BGM
	audio_->ChangeVolume(winBgmHandle_, bgmVolume_);

	//平行光源の更新
	directionalLight_.Update();
	//カメラの更新
	camera_.Update();

	//レベルデータの更新
	levelDataManager_->Update(levelDataHandle_);

#ifdef _DEBUG
	//再読み込み
	if (input_->IsTriggerKey(DIK_R) == true) {
		levelDataManager_->Reload(levelDataHandle_);
	}

#endif // _DEBUG
}

void WinScene::PreDrawPostEffect(){
	backTexture_->PreDraw();
}

void WinScene::DrawObject3D(){
	levelDataManager_->Draw(levelDataHandle_, camera_, directionalLight_);
}

void WinScene::DrawPostEffect(){
	backTexture_->Draw();
}

void WinScene::DrawSprite(){

	whiteFade_->Draw();
}
