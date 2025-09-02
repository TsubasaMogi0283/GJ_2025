#include "Player.h"

#include <imgui.h>
#include <numbers>

#include "Input.h"
#include "VectorCalculation.h"
#include "SingleCalculation.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "SpotLight.h"
#include "LevelDataManager.h"
#include "PushBackCalculation.h"

Player::Player(){

	//インスタンスの取得
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//モデル管理クラス
	modelManager_ = Elysia::ModelManager::GetInstance();
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
}

void Player::Initialize(){

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	const Vector3 INITIAL_POSITION = { .x=0.0f,.y=0.0f,.z=-15.0f };
	worldTransform_.translate = INITIAL_POSITION;

	//懐中電灯
	flashLight_ = std::make_unique<FlashLight>();
	flashLight_->Initialize();

	//カメラ
	eyeCamera_ = std::make_unique<PlayerEyeCamera>();
	eyeCamera_->Initialize();

	//マテリアル
	material_.Initialize();
	material_.lightingKinds = LightingType::SpotLighting;
	material_.color = { .x = 1.0f,.y = 1.0f,.z = 1.0f,.w = 1.0f };

}

void Player::Update(){
	
	//移動処理
	Move();
	//ワールドトランスフォームの更新
	worldTransform_.translate=VectorCalculation::Add(worldTransform_.translate, moveDirection_);
	worldTransform_.Update();


	//AABBの計算
	aabb_.min = VectorCalculation::Subtract(worldTransform_.GetWorldPosition(), { SIDE_SIZE ,SIDE_SIZE ,SIDE_SIZE });
	aabb_.max = VectorCalculation::Add(worldTransform_.GetWorldPosition(), { SIDE_SIZE ,SIDE_SIZE ,SIDE_SIZE });


	//懐中電灯
	//角度はゲームシーンで取得する
	flashLight_->SetPlayerPosition(worldTransform_.GetWorldPosition());
	//目線の角度の設定
	flashLight_->SetTheta(theta_);
	flashLight_->SetPhi(-phi_);
	//更新
	flashLight_->Update();

	//カメラ(目)
	//座標の設定
	eyeCamera_->SetPlayerPosition(GetWorldPosition());
	//角度の設定
	eyeCamera_->SetTheta(theta_);
	eyeCamera_->SetPhi(phi_);
	//カメラ(目)の更新
	eyeCamera_->Update();
	//マテリアルの更新
	material_.Update();

	
#ifdef _DEBUG
	//ImGui表示
	DisplayImGui();
#endif
}

void Player::DrawObject3D(const Camera& camera, const SpotLight& spotLight){

	spotLight;

	//懐中電灯
	flashLight_->DrawObject3D(camera);

}

void Player::DrawSprite(){
}

Player::~Player() {
	//振動を止める
	input_->StopVibration();
}

void Player::Move() {
	
}

void Player::DisplayImGui() {


	ImGui::Begin("プレイヤー");
	if (ImGui::TreeNode("状態")==true) {
		ImGui::InputFloat3("座標", &worldTransform_.translate.x);
		ImGui::InputFloat3("方向", &moveDirection_.x);
		ImGui::InputFloat("Theta", &theta_);
		ImGui::InputFloat("Phi", &phi_);

		ImGui::TreePop();
	}

	
	
	ImGui::End();

}

