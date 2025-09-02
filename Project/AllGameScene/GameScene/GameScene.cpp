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
	//ビネット生成
	vignettePostEffect_ = std::make_unique<Elysia::VignettePostEffect>();
	//初期化
	vignettePostEffect_->Initialize();
	//値の設定
	vignette_.Initialize();
	vignette_.pow = 0.0f;

	//環境音の読み込み
	enviromentAudioHandle_ = audio_->Load("Resources/Audio/Environment/Environment.wav");


	//再生
	audio_->Play(enviromentAudioHandle_, true);
	//最初は音量を0にする
	audio_->ChangeVolume(enviromentAudioHandle_, enviromentAudioVolume_);
}

void GameScene::VigntteProcess(){
	//HPが1でピンチの場合
	const uint32_t DANGEROUS_HP = 1u;
	//プレイヤーがダメージを受けた場合ビネット
	if (player_->GetIsDamaged() == true) {
		//時間の加算
		vignetteChangeTime_ += DELTA_TIME_;

		//線形補間で滑らかに変化
		vignette_.pow = SingleCalculation::Lerp(MAX_VIGNETTE_POW_, 0.0f, vignetteChangeTime_);
	}
	//ピンチ演出
	else if (player_->GetHP() == DANGEROUS_HP) {
		warningTime_ += DELTA_TIME_;
		vignette_.pow = SingleCalculation::Lerp(MAX_VIGNETTE_POW_, 0.0f, warningTime_);

		//最大時間
		const float_t MAX_WARNING_TIME = 1.0f;
		//最小時間
		const float_t MIN_WARNING_TIME = 1.0f;

		if (warningTime_ > MAX_WARNING_TIME) {
			warningTime_ = MIN_WARNING_TIME;
		}
	}
	//通常時の場合
	else {
		vignette_.pow = 0.0f;
		vignetteChangeTime_ = 0.0f;
	}
	//ビネットの更新
	vignette_.Update();
}

void GameScene::DisplayImGui() {

	ImGui::Begin("ゲームシーン");

	if (ImGui::TreeNode("ビネット")==true) {
		ImGui::InputFloat("POW", &vignette_.pow);
		ImGui::InputFloat("変化の時間", &vignetteChangeTime_);
		ImGui::TreePop();
	}

	ImGui::End();

}

void GameScene::Update(Elysia::GameManager* gameManager) {

	//プレイヤーの更新
	player_->Update();
	//カメラの更新
	//レールカメラから2つの行列を取得
	camera_.viewMatrix = player_->GetEyeCamera()->GetCamera().viewMatrix;
	//転送
	camera_.Transfer();
	//レベルエディタで使うリスナーの設定
	Listener listener = {
		.position = player_->GetWorldPosition(),
		.move = player_->GetMoveDirection(),
	};
	levelDataManager_->SetListener(levelHandle_, listener);
	//レベルエディタの更新
	levelDataManager_->Update(levelHandle_);

	//ビネットの処理
	VigntteProcess();

	//音量の設定
	audio_->ChangeVolume(enviromentAudioHandle_, enviromentAudioVolume_);

	//処理が終わった時
	if (isEnd_ == true) {
		//勝ったとき
		if (isWin_ == true) {
			gameManager->ChangeScene("Win");
			return;
		}
		//負けた時
		if (isLose_ == true) {
			gameManager->ChangeScene("Lose");
			return;
		}
	}

	
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
	vignettePostEffect_->PreDraw();
}

void GameScene::DrawObject3D() {


	//懐中電灯を取得
	SpotLight spotLight = player_->GetFlashLight()->GetSpotLight();

	//レベルエディタ  
	levelDataManager_->Draw(levelHandle_, camera_, spotLight);
	//プレイヤー
	player_->DrawObject3D(camera_, spotLight);

}

void GameScene::DrawPostEffect() {
	//ビネット描画
	vignettePostEffect_->Draw(vignette_);
}

void GameScene::DrawSprite() {
}
