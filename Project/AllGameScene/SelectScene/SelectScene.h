#pragma once
/**
 * @file SelectScene.h
 * @brief 選択のクラス
 * @author 茂木翼
 */
#include <memory>
#include <array>
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
/// 選択シーン
/// </summary>
class SelectScene : public Elysia::IGameScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectScene();

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
	~SelectScene()=default;



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


	const std::string one_ = "One";
	const std::string two_ = "Two";
	const std::string three_ = "Three";
	const std::string four_ = "Four";
	const std::string five_ = "Five";
	const std::string six_ = "Six";
	const std::string seven_ = "Seven";
	const std::string eight_ = "Eight";
	const std::string nine_ = "Nine";
	const std::string returnString_ = "Return";

	//数字
	static const uint8_t NUMBER_QUANTITY_ = 10u;
	//移動の間隔
	const float_t INTERVAL_ = 4.0f;
	//初期スケール
	const Vector3 INITIAL_SCALE_ = { 1.0f,1.0f,1.0f };
	//選択時のスケール
	const Vector3 SELECTED_SCALE_ = { 3.0f,3.0f,3.0f };

private:
	//カメラ
	Camera camera_ = {};

	//点光源
	PointLight pointLight_ = {};

	//背景(ポストエフェクト)
	std::unique_ptr<Elysia::BackTexture>backTexture_ = nullptr;

	//初期座標
	Vector3 initialPosition_ = {};

	std::array<Vector3, NUMBER_QUANTITY_>numberPositions_ = {};

	//
	Vector3 moveInterval_ = {};

	//ステージ
	uint8_t stageNumber_ = 1u;

};

