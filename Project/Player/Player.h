#pragma once

/**
 * @file Player.h
 * @brief プレイヤーのクラス
 * @author 茂木翼
 */

#include <memory>
#include <list>

#include "WorldTransform.h"
#include "Model.h"
#include "AABB.h"

#include "PlayerCollisionToStrongEnemy.h"
#include "PlayerCollisionToNormalEnemyAttack.h"
#include "PlayerCollisionToAudioObject.h"
#include "Light/FlashLight/FlashLight.h"
#include "Camera/PlayerCamera.h"

#pragma region 前方宣言

/// <summary>
/// カメラ
/// </summary>
struct Camera;

/// <summary>
/// マテリアル
/// </summary>
struct Material;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene;

/// <summary>
/// ElysiaEngine
/// </summary>
namespace Elysia {
	/// <summary>
	/// 入力クラス
	/// </summary>
	class Input;

	/// <summary>
	/// モデル管理クラス
	/// </summary>
	class ModelManager;

	/// <summary>
	/// テクスチャ管理クラス
	/// </summary>
	class TextureManager;

	/// <summary>
	/// レベルデータ管理クラス
	/// </summary>
	class LevelDataManager;
};



#pragma endregion

/// <summary>
/// プレイヤーの移動状態
/// </summary>
enum PlayerMoveCondition {
	//動かない
	NonePlayerMove,
	//動く
	OnPlayerMove,
};


/// <summary>
/// プレイヤー
/// </summary>
class Player {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="material"></param>
	/// <param name="spotLight"></param>
	void DrawObject3D(const Camera& camera, const SpotLight& spotLight);

	/// <summary>
	/// スプライトの描画
	/// </summary>
	void DrawSprite();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// ImGui表示用
	/// </summary>
	void DisplayImGui();

public:

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns>ワールド座標</returns>
	inline Vector3 GetWorldPosition()const {
		return worldTransform_.GetWorldPosition();
	}


	/// <summary>
	/// 移動方向を取得
	/// </summary>
	/// <returns>方向</returns>
	inline Vector3 GetMoveDirection() const {
		return moveDirection_;
	}

	/// <summary>
	/// ライトの方向を取得
	/// </summary>
	/// <returns></returns>
	inline Vector3 GetLightDirection()const {
		return flashLight_->GetSpotLight().direction;
	}


	/// <summary>
	/// 目線シータの設定
	/// </summary>
	/// <param name="theta_"></param>
	inline void SetTheta(const float_t& theta) {
		this->theta_ = theta;
	}

	/// <summary>
	/// 目線ファイの設定
	/// </summary>
	/// <param name="phi"></param>
	inline void SetPhi(const float_t& phi) {
		this->phi_ = phi;
	}


	/// <summary>
	/// AABBの取得
	/// </summary>
	/// <returns>AABB</returns>
	inline AABB GetAABB() const {
		return aabb_;
	}

	/// <summary>
	/// 幅のサイズを取得
	/// </summary>
	/// <returns>幅のサイズ</returns>
	inline float_t GetSideSize()const {
		return SIDE_SIZE;
	}

	/// <summary>
	/// 動く方向の設定
	/// </summary>
	/// <param name="move">方向</param>
	inline void SetMoveDirection(const Vector3& moveDirection) {
		this->moveDirection_ = moveDirection;
	}

	/// <summary>
	/// 走るかどうか
	/// </summary>
	/// <param name="isDash">走っているかどうか</param>
	inline void SetIsDash(const bool& isDash) {
		this->isDash_ = isDash;
	}


	/// <summary>
	/// 操作を受け付けるか受け付けないかの設定
	/// </summary>
	/// <param name="isControll">操作できるかどうか</param>
	inline void SetIsAbleToControll(const bool& isControll) {
		this->isControll_ = isControll;
	}

	/// <summary>
	/// レベルデータハンドルの設定
	/// </summary>
	/// <param name="levelHandle"></param>
	inline void SetLevelHandle(const uint32_t& levelHandle) {
		this->levelHandle_ = levelHandle;
	}

public:
	/// <summary>
	/// 懐中電灯を取得
	/// </summary>
	/// <returns>懐中電灯</returns>
	inline FlashLight* GetFlashLight()const {
		return flashLight_.get();
	}

	/// <summary>
	/// カメラ(目)を取得
	/// </summary>
	/// <returns></returns>
	inline PlayerEyeCamera* GetEyeCamera()const {
		return eyeCamera_.get();
	}


	/// <summary>
	/// 懐中電灯のコライダーを取得
	/// </summary>
	/// <returns></returns>
	inline FlashLightCollision* GetFlashLightCollision()const {
		return flashLight_->GetFanCollision();
	}

private:
	//入力クラス
	Elysia::Input* input_ = nullptr;
	//モデル管理クラス
	Elysia::ModelManager* modelManager_ = nullptr;
	//テクスチャ管理クラス
	Elysia::TextureManager* textureManager_ = nullptr;
	//レベルエディタ
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	//ハンドル
	uint32_t levelHandle_ = 0u;

private:
	//プレイヤーの最大体力
	static const uint32_t PLAYER_HP_MAX_QUANTITY_ = 3u;
	//幅のサイズ
	const float_t SIDE_SIZE = 0.5f;
	//時間変化
	const float_t DELTA_TIME = 1.0f / 60.0f;
	//チャージの増える値
	const float_t CHARGE_VALUE_ = 0.1f;
	//最大の振動の強さ
	const float_t MAX_VIBE_ = 1.0f;
	//最小の振動の強さ
	const float_t MIN_VIBE_ = 0.0f;
	//戻る時間
	const float_t RESTART_TIME_ = 0.0f;
	//歩くスピード
	const float_t NORMAL_MOVE_SPEED_ = 0.1f;
	//走るスピード
	const float_t DASH_MOVE_SPEED_ = 0.2f;
	//Yを固定させる
	const float_t HEIGHT_ = 0.0f;
	//スピード
	const float_t SPEED_ = 0.1f;
	//ダッシュスピード
	const float_t DASH_SPEED_ = 0.2f;

private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_ = {};
	//動く方向
	Vector3 moveDirection_ = {};
	//目線
	float_t theta_ = 0.0f;
	float_t phi_ = 0.0f;
	//中心座標
	Vector3 playerCenterPosition_ = {};
	//マテリアル
	Material material_ = {};
	//AABB
	AABB aabb_ = {};

	//操作可能かどうか
	bool isControll_ = false;
	//ダッシュ
	bool isDash_ = false;

	//時間
	float_t vibeTime_ = 0u;

private:
	//懐中電灯
	std::unique_ptr<FlashLight>flashLight_ = nullptr;
	//目としてのカメラクラス
	std::unique_ptr<PlayerEyeCamera>eyeCamera_ = nullptr;
};