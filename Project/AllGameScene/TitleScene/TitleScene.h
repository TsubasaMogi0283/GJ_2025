#pragma once
/**
 * @file TitleScene.h
 * @brief タイトルクラス
 * @author 茂木翼
 */

#include <memory>
#include <vector>

#include "IGameScene.h"
#include "Sprite.h"
#include "Model.h"
#include "Camera.h"
#include "BackTexture.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "RandomNoise.h"
#include "RandomNoisePostEffect.h"

#pragma region 前方宣言


 /// <summary>
 /// ElysiaEngine
 /// </summary>
namespace Elysia {
	/// <summary>
	/// 入力
	/// </summary>
	class Input;

	/// <summary>
	/// レベル管理クラス
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
	/// オーディオ
	/// </summary>
	class Audio;
}


#pragma endregion


/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Elysia::IGameScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="gameManager">ゲーム管理クラス</param>
	void Update(Elysia::GameManager* gameManager)override;

	/// <summary>
	/// 3Dオブジェクト
	/// </summary>
	void DrawObject3D()override;

	/// <summary>
	/// ポストエフェクト描画処理前
	/// </summary>
	void PreDrawPostEffect()override;

	/// <summary>
	/// ポストエフェクト描画
	/// </summary>
	void DrawPostEffect()override;


	/// <summary>
	/// スプライト
	/// </summary>
	void DrawSprite()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene() = default;


private:
	/// <summary>
	/// ImGui用関数
	/// </summary>
	void DisplayImGui();


private:
	//テクスチャ管理クラス
	Elysia::TextureManager* textureManager_ = nullptr;
	//入力クラス
	Elysia::Input* input_ = nullptr;
	//レベルエディタ
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	uint32_t levelHandle_ = 0u;
	//オーディオ
	Elysia::Audio* audio_ = nullptr;

private:

	//カメラ
	Camera camera_ = {};
	//平行光源
	DirectionalLight directionalLight_ = {};
	//ポストエフェクト
	std::unique_ptr<Elysia::BackTexture> backTexture_ = nullptr;

};