#pragma once
/**
 * @file LoseScene.h
 * @brief 負けシーンのクラス
 * @author 茂木翼
 */
#include <memory>

#include "IGameScene.h"
#include "Sprite.h"
#include "Model.h"
#include "Camera.h"
#include "PointLight.h" 
#include "BackTexture.h"



/// <summary>
/// EllysiaEngine(前方宣言)
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
	/// グローバル変数
	/// </summary>
	class GlobalVariables;

	/// <summary>
	/// ゲーム管理クラス
	/// </summary>
	class GameManager;

	/// <summary>
	/// オーディオ
	/// </summary>
	class Audio;
};


/// <summary>
/// 負けシーン
/// </summary>
class LoseScene : public Elysia::IGameScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	LoseScene();

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
	/// ポストエフェクト描画処理前
	/// </summary>
	void PreDrawPostEffect()override;

	/// <summary>
	/// ポストエフェクト描画処理前
	/// </summary>
	void DrawPostEffect()override;


	/// <summary>
	/// スプライト描画
	/// </summary>
	void DrawSprite()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LoseScene()=default;



private:
	/// <summary>
	/// /ImGUiの表示
	/// </summary>
	void DisplayImGui();

private:
	//入力クラス
	Elysia::Input* input_ = nullptr;
	//レベルデータ管理クラス
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	//ハンドル
	uint32_t levelDataHandle_ = 0u;
	//グローバル変数クラス
	Elysia::GlobalVariables* globalVariables_ = nullptr;
	//オーディオ
	Elysia::Audio* audio_ = nullptr;


private:
	//カメラ
	Camera camera_ = {};

	//点光源
	PointLight pointLight_ = {};

	//背景(ポストエフェクト)
	std::unique_ptr<Elysia::BackTexture>backTexture_ = nullptr;

};

