#pragma once

/**
 * @file GameScene.h
 * @brief ゲームシーンのクラス
 * @author 茂木翼
 */

#include <memory>

#include "IGameScene.h"
#include "Sprite.h"
#include "Camera.h"
#include "SpotLight.h"
#include <Material.h>
#include <Model.h>
#include "Player/Player.h"
#include "CollisionManager.h"
#include "CollisionCalculation.h"
#include <WorldTransform.h>
#include "VignettePostEffect.h"
#include "Vignette.h"
#include <BackTexture.h>

#include "Terrain/TerrainManager.h"


 /// <summary>
 /// ElysiaEngine(前方宣言)
 /// </summary>
namespace Elysia {
	/// <summary>
	/// レベルエディタ
	/// </summary>
	class LevelDataManager;

	/// <summary>
	/// ゲーム管理クラス
	/// </summary>
	class GameManager;

	/// <summary>
	/// テクスチャ管理クラス
	/// </summary>
	class TextureManager;

	/// <summary>
	/// モデル管理クラス
	/// </summary>
	class ModelManager;

	/// <summary>
	/// 入力クラス
	/// </summary>
	class Input;

	/// <summary>
	/// 調整項目クラス
	/// </summary>
	class GlobalVariables;

	/// <summary>
	/// オーディオ
	/// </summary>
	class Audio;
}


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public Elysia::IGameScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="gameManager"></param>
	void Update(Elysia::GameManager* gameManager)override;

	/// <summary>
	/// 3Dオブジェクト
	/// </summary>
	void DrawObject3D()override;

	/// <summary>
	/// ポストエフェクト描画前
	/// </summary>
	void PreDrawPostEffect()override;

	/// <summary>
	/// ポストエフェクトの描画
	/// </summary>
	void DrawPostEffect()override;

	/// <summary>
	/// スプライト
	/// </summary>
	void DrawSprite()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene() = default;

private:
	
	/// <summary>
	/// プレイヤーの動き
	/// </summary>
	void PlayerMove();
	
	/// <summary>
	/// プレイヤーの回転
	/// </summary>
	void PlayerRotate();

	/// <summary>
	/// ImGuiの表示
	/// </summary>
	void DisplayImGui();

private:
	//インプット
	Elysia::Input* input_ = nullptr;
	//テクスチャ管理クラス
	Elysia::TextureManager* textureManager_ = nullptr;
	//モデル管理クラス
	Elysia::ModelManager* modelManager_ = nullptr;
	//レベルエディタ
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	//ハンドル
	uint32_t levelHandle_ = 0u;
	//グローバル変数クラス
	Elysia::GlobalVariables* globalVariables_ = nullptr;
	//オーディオ
	Elysia::Audio* audio_ = nullptr;

	//コントローラーがある場合
	const float_t MOVE_LIMITATION_ = 0.02f;

private:
	//カメラ
	Camera camera_ = {};
	//スポットライト
	SpotLight spotLight_ = {};
	//ポストエフェクト
	std::unique_ptr<Elysia::BackTexture> backTexture_ = nullptr;
	//プレイヤー
	std::unique_ptr<Player> player_ = nullptr;
	//移動方向
	Vector3 playerDirection_ = {};
	float_t theta_ = 0.0f;
	float_t phi_ = 0.0f;

	//衝突判定管理クラス
	std::unique_ptr<Elysia::CollisionManager> collisionManager_ = nullptr;

	// 地形管理クラス
	std::shared_ptr<TerrainManager> terrainManager_;

	//離したかどうか
	bool isReleaseAttack_ = false;
	

};