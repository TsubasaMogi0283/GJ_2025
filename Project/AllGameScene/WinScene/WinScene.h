#pragma once
/**
 * @file WinScene.h
 * @brief 勝利シーン
 * @author 茂木翼
 */
#include <memory>

#include "IGameScene.h"
#include "Sprite.h"
#include "Model.h"
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "BackTexture.h"


/// <summary>
/// ElysiaEngine(前方宣言)
/// </summary>
namespace Elysia {

	/// <summary>
	/// 入力
	/// </summary>
	class Input;

	/// <summary>
	/// レベルデータ管理クラス
	/// </summary>
	class LevelDataManager;


	/// <summary>
	/// ゲーム管理クラス
	/// </summary>
	class GameManager;

	/// <summary>
	/// オーディオ
	/// </summary>
	class Audio;
}



/// <summary>
/// 勝利シーン
/// </summary>
class WinScene : public Elysia::IGameScene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WinScene();

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
	/// ポストエフェクト描画処理前
	/// </summary>
	void PreDrawPostEffect()override;

	/// <summary>
	/// 描画(3D描画)
	/// </summary>
	void DrawObject3D()override;

	/// <summary>
	/// ポストエフェクト描画
	/// </summary>
	void DrawPostEffect()override;

	/// <summary>
	/// スプライトの描画
	/// </summary>
	void DrawSprite()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WinScene()override=default;

private:
	//レベルデータ管理クラス
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	//ハンドル
	uint32_t levelDataHandle_ = 0u;
	//オーディオ
	Elysia::Audio* audio_ = nullptr;

private:

	Camera camera_ = {};
	//平行光源
	DirectionalLight directionalLight_ = {};

	//ポストエフェクト
	std::unique_ptr<Elysia::BackTexture> backTexture_ = nullptr;

};

