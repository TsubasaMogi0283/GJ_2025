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

	// 地形管理クラス
	terrainManager_ = std::make_shared<TerrainManager>();
}

void GameScene::Initialize() {

	//ハンドルの取得
	levelHandle_ = levelDataManager_->Load("GameStage/Stage1.json");

	playerInitialPosition_ = levelDataManager_->GetInitialTranslate(levelHandle_, "Player");

	//生成
	player_ = std::make_unique<Player>();
	//初期化
	player_->Initialize(playerInitialPosition_);
	//ハンドルの設定
	player_->SetLevelHandle(levelHandle_);
	//最初はコントロールは出来ない用にする
	player_->SetIsAbleToControll(false);
	//ライトの制限を設定
	player_->GetFlashLight()->SetUseLimitation(lightUseLimitation_);
	//向き
	theta_ = std::numbers::pi_v<float_t>/2.0f ;
	//リスナーの設定
	levelDataManager_->SetListener(levelHandle_, player_.get());

	//矢印
	escapeAssistArrow_ = std::make_unique<EscapeAssistArrow>();
	escapeAssistArrow_->SetPlayer(player_.get());
	escapeAssistArrow_->Initialize();

	//スプライト用の座標
	const Vector2 SPRITE_INITIAL_POSITION_ = { .x = 0.0f,.y = 0.0f };

	//説明
	uint32_t operationTextureHandle = textureManager_->Load("Resources/Sprite/Operation/Operation.png");
	explanation_.reset(Elysia::Sprite::Create(operationTextureHandle, SPRITE_INITIAL_POSITION_));

	//脱出
	uint32_t escapeTextureHandle = textureManager_->Load("Resources/Sprite/Escape/EscapeText.png");
	escape_.reset(Elysia::Sprite::Create(escapeTextureHandle, SPRITE_INITIAL_POSITION_));
	//非表示
	escape_->SetInvisible(true);

	//フェード
	uint32_t whiteTextureHandle = textureManager_->Load("Resources/Sprite/Back/White.png");
	whiteSprite_.reset(Elysia::Sprite::Create(whiteTextureHandle, SPRITE_INITIAL_POSITION_));
	whiteFadeTransparency_ = 0.0f;
	whiteSprite_->SetTransparency(whiteFadeTransparency_);

	//カメラの初期化
	camera_.Initialize();
	camera_.translate = { .x = 0.0f,.y = 2.0f,.z = -5.0f };

	//ポストエフェクトの初期化
	backTexture_ = std::make_unique<Elysia::BackTexture>();
	//初期化
	backTexture_->SetClearColour({ 0.0f,0.0f,0.0f,1.0f });
	backTexture_->Initialize();
	
	//衝突管理クラス
	collisionManager_ = std::make_unique<Elysia::CollisionManager>();

	// 地形初期化
	terrainManager_->Init();
	terrainManager_->Create_NewFloor(Vector3{ -1.0f, 1.0f, 5.0f });
	terrainManager_->Create_NewWall(Vector3{ 1.0f, 1.0f, 5.0f });
}


void GameScene::PlayerMove(){
	//何も押していない時つまり動いていないので通常はfalseと0にしておく
	//キーボードで動かしているかどうか
	bool isPlayerMoveKey = false;
	//動いているかどうか
	bool isPlayerMove = false;
	//向き
	Vector3 playerMoveDirection = { .x = 0.0f,.y = 0.0f,.z = 0.0f };


	//プレイヤーの更新
	if (input_->IsPushKey(DIK_W) == true) {
		//動く方向
		playerMoveDirection = {
			.x = std::cosf(theta_),
			.y = 0.0f,
			.z = std::sinf(theta_),
		};

		//キーボード入力をしている
		isPlayerMoveKey = true;
		//動いている
		isPlayerMove = true;
	}
	if (input_->IsPushKey(DIK_S) == true) {
		playerMoveDirection.x = std::cosf(theta_ + std::numbers::pi_v<float_t>);
		playerMoveDirection.z = std::sinf(theta_ + std::numbers::pi_v<float_t>);

		//キーボード入力をしている
		isPlayerMoveKey = true;
		//動いている
		isPlayerMove = true;
	}
	if (input_->IsPushKey(DIK_D) == true) {
		//動く方向
		playerMoveDirection = {
			.x = std::cosf(theta_ - std::numbers::pi_v<float_t> / 2.0f),
			.y = 0.0f,
			.z = std::sinf(theta_ - std::numbers::pi_v<float_t> / 2.0f),
		};

		//キーボード入力をしている
		isPlayerMoveKey = true;
		//動いている
		isPlayerMove = true;
	}
	if (input_->IsPushKey(DIK_A) == true) {
		//動く方向
		playerMoveDirection = {
			.x = std::cosf(theta_ + std::numbers::pi_v<float_t> / 2.0f),
			.y = 0.0f,
			.z = std::sinf(theta_ + std::numbers::pi_v<float_t> / 2.0f),
		};

		//キーボード入力をしている
		isPlayerMoveKey = true;
		//動いている
		isPlayerMove = true;
	}

	//方向取得
	player_->SetMoveDirection(playerMoveDirection);

	if (input_->IsPushKey(DIK_LSHIFT) == true) {
		player_->SetIsDash(true);
	}
	else {
		player_->SetIsDash(false);
	}

	//チャージ
	bool isCharge = false;
	//エンターキーまたはRSHOLDERでチャージ開始
	if (lightUseLimitation_>0u) {
		if (input_->IsPushKey(DIK_RETURN) == true || input_->IsPushButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) {

			isCharge = true;
		}
		else {
			isCharge = false;
		}



		
		//チャージ状態を設定
		player_->GetFlashLight()->SetIsCharge(isCharge);

		//エンターキーまたはYボタンを離した瞬間に攻撃する
		if (input_->IsReleaseKey(DIK_RETURN) == true || input_->IsReleaseButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true) {
			//完全にチャージしないとダメ
			if (player_->GetFlashLight()->GetChargeCondition() == ChargeCondition::StrongChargeAttack) {
				//使用回数を減らす
				lightUseLimitation_--;
				//カメラシェイク
				player_->GetEyeCamera()->SetIsShake(true);
				isReleaseAttack_ = true;
			}

			//クールタイムにする
			player_->GetFlashLight()->SetIsCoolTime(true);
		}
		else {
			isReleaseAttack_ = false;
		}
	}
	
	//ライトの制限を設定
	player_->GetFlashLight()->SetUseLimitation(lightUseLimitation_);


	//ライトのコライダーを登録
	collisionManager_->RegisterList(player_->GetFlashLight()->GetFanCollision());

	//リリース状態を取得
	player_->SetIsReleaseKey(isReleaseAttack_);
}

void GameScene::PlayerRotate() {

	//回転キーXY
	bool isRotateYKey = false;
	bool isRotateXKey = false;
	//回転の大きさ
	const float_t ROTATE_INTERVAL_ = 0.025f;

	//+が左回り
	//左を向く
	if (input_->IsPushKey(DIK_LEFT) == true) {
		theta_ += ROTATE_INTERVAL_;
		isRotateYKey = true;
	}
	//右を向く
	if (input_->IsPushKey(DIK_RIGHT) == true) {
		theta_ -= ROTATE_INTERVAL_;
		isRotateYKey = true;
	}
	//上を向く
	if (input_->IsPushKey(DIK_UP) == true) {
		phi_ -= ROTATE_INTERVAL_;
		isRotateXKey = true;
	}
	//下を向く
	if (input_->IsPushKey(DIK_DOWN) == true) {
		phi_ += ROTATE_INTERVAL_;
		isRotateXKey = true;
	}

	//2πより大きくなったら0にまた戻す
	if (theta_ > 2.0f * std::numbers::pi_v<float_t>) {
		theta_ = 0.0f;
	}
	//-2πより大きくなったら0にまた戻す
	if (theta_ < -2.0f * std::numbers::pi_v<float_t>) {
		theta_ = 0.0f;
	}

#pragma region コントローラーの回転

	//キーボード入力していない時
	if (isRotateYKey == false && isRotateXKey == false) {

		//入力
		float_t rotateMoveX = (static_cast<float_t>(input_->GetCurrentState().Gamepad.sThumbRY) / SHRT_MAX * ROTATE_INTERVAL_);
		float_t rotateMoveY = (static_cast<float_t>(input_->GetCurrentState().Gamepad.sThumbRX) / SHRT_MAX * ROTATE_INTERVAL_);

		//勝手に動くので制限を掛ける
		if (rotateMoveY < MOVE_LIMITATION_ && rotateMoveY > -MOVE_LIMITATION_) {
			rotateMoveY = 0.0f;
		}
		if (rotateMoveX < MOVE_LIMITATION_ && rotateMoveX > -MOVE_LIMITATION_) {
			rotateMoveX = 0.0f;
		}

		//補正後の値を代入する
		theta_ -= rotateMoveY;
		phi_ -= rotateMoveX;
	}

#pragma endregion

	//±π/6くらいに制限を掛けておきたい
	//それ以下以上だと首が大変なことになっているように見えるからね
	if (phi_ > std::numbers::pi_v<float_t> / 12.0f) {
		phi_ = std::numbers::pi_v<float_t> / 12.0f;
	}
	if (phi_ < -std::numbers::pi_v<float_t> / 12.0f) {
		phi_ = -std::numbers::pi_v<float_t> / 12.0f;
	}
}

void GameScene::Goal() {
	//ゴール座標の取得
	Vector3 goalPosition = levelDataManager_->GetInitialTranslate(levelHandle_, "Goal");
	//サイズ
	const float_t SIZE = 2.0f;
	//プレイヤーの座標
	Vector3 playerWorldPosition = player_->GetWorldPosition();

	//エリア内にいた場合
	if (playerWorldPosition.x >= goalPosition.x - SIZE &&
		playerWorldPosition.x <= goalPosition.x + SIZE &&
		playerWorldPosition.z >= goalPosition.z - SIZE &&
		playerWorldPosition.z <= goalPosition.z + SIZE) {
		isOnGoalArea_ = true;
	}
	else {
		isOnGoalArea_ = false;
	}

	//ゴールの座標を設定
	escapeAssistArrow_->SetGoalPosition({ .x = goalPosition.x,.y = goalPosition.z });
	escapeAssistArrow_->SetTheta(theta_);

}

void GameScene::DisplayImGui() {

	ImGui::Begin("ゲームシーン");
	if (ImGui::TreeNode("カメラ") == true) {
		ImGui::SliderFloat3("座標", &camera_.translate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("回転", &camera_.rotate.x, -3.0f, 3.0f);
		ImGui::TreePop();
	}

	ImGui::Checkbox("ゴールエリア上", &isOnGoalArea_);
	ImGui::InputFloat("フェードの透明度", &whiteFadeTransparency_);
	ImGui::End();
}

void GameScene::Update(Elysia::GameManager* gameManager) {
	//中身を空にする
	collisionManager_->ClearList();
	
	//レベルエディタの更新
	levelDataManager_->Update(levelHandle_);
	//レベルエディタのオブジェクトのコライダーを取得し登録
	//レベルエディタの更新
	levelDataManager_->Update(levelHandle_);
	//レベルエディタのオブジェクトのコライダーを取得し登録
	const auto& lightColliders = levelDataManager_->GetColliderToLight(levelHandle_, "Stage");
	const auto& playerColliders = levelDataManager_->GetColliderToPlayer(levelHandle_, "Stage");

	for (const auto& collider : lightColliders) {
		if (collider != nullptr) {
			collisionManager_->RegisterList(collider);
		}
	}
	for (const auto& collider : playerColliders) {
		if (collider != nullptr) {
			collisionManager_->RegisterList(collider);
		}
	}
	//プレイヤーの移動と回転
	PlayerMove();
	PlayerRotate();
	//プレイヤーにそれぞれの角度を設定する
	player_->SetTheta(theta_);
	player_->SetPhi(phi_);
	//プレイヤー
	player_->Update();
	//ゴール処理
	Goal();
	//矢印
	escapeAssistArrow_->Update();
	//プレイヤーのコリジョンを登録
	collisionManager_->RegisterList(player_->GetPlayerCollision());
	//カメラの更新
	camera_.viewMatrix = player_->GetEyeCamera()->GetCamera().viewMatrix;
	//転送
	camera_.Transfer();

	// 地形
	terrainManager_->Update();

	//衝突判定の計算
	collisionManager_->CheckAllCollision();

	//リセット
	if (input_->IsTriggerKey(DIK_R) == true||input_->IsTriggerButton(XINPUT_GAMEPAD_START)==true) {
		lightUseLimitation_ = 9u;
		player_->ResetPosition(playerInitialPosition_);
	}

	//ゴールエリア上
	if (isOnGoalArea_ == true) {
		//表示
		escape_->SetInvisible(false);

		if (input_->IsTriggerKey(DIK_SPACE) == true || input_->IsTriggerButton(XINPUT_GAMEPAD_B) == true) {
			isSucceed_ = true;
		}
	}
	else {
		//表示
		escape_->SetInvisible(true);

	}

	//成功時
	if (isSucceed_ == true) {
		whiteFadeTransparency_ += 0.01f;
		whiteSprite_->SetTransparency(whiteFadeTransparency_);
	}
	//フェードが終わったら勝ち(成功へ)
	if (whiteFadeTransparency_ >= 1.0f) {
		gameManager->ChangeScene("Win");
		return;
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
	backTexture_->PreDraw();
}

void GameScene::DrawObject3D() {

	//ライトの更新
	SpotLight spotLight = player_->GetFlashLight()->GetSpotLight();

	//レベルエディタのオブジェクトを描画
	levelDataManager_->Draw(levelHandle_, camera_, spotLight);
	//プレイヤーの描画
	player_->DrawObject3D(camera_,spotLight);
	// 地形
	terrainManager_->Draw(camera_, spotLight);
}

void GameScene::DrawPostEffect() {
	//ビネット描画
	backTexture_->Draw();
}

void GameScene::DrawSprite() {
	//プレイヤー
	player_->DrawSprite();

	//矢印
	escapeAssistArrow_->DrawSprite();
	//説明
	explanation_->Draw();
	//脱出
	escape_->Draw();

	//白フェード
	whiteSprite_->Draw();
}
