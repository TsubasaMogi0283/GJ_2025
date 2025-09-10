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

	//入力クラス
	Elysia::Input* input_ = nullptr;

private:
	const std::string NEXT_ = "Next";
	const std::string TITLE_ = "Title";

	const Vector3 INITIAL_SCALE_ = { 0.3f,0.3f,0.3f };
	const Vector3 SELECTED_SCALE_ = { 0.6f,0.6f,0.6f };

	const float_t NORMAL_ROTATE_AMOUNT_ = 0.05f;
	const float_t RAPID_ROTATE_AMOUNT_ = 0.2f;

	//時間変化
	const float_t DELTA_TIME_ = 1.0f / 60.0f;
	//フェードの変化
	const float_t FADE_AMOUNT_ = 0.01f;

private:

	Camera camera_ = {};
	//平行光源
	DirectionalLight directionalLight_ = {};

	//ポストエフェクト
	std::unique_ptr<Elysia::BackTexture> backTexture_ = nullptr;
	//決定
	bool isDecide_ = false;

	//右
	bool isRight_ = false;
	//右のスケール
	Vector3 rightScale_ = SELECTED_SCALE_;
	//右の回転
	float_t rightRotate_ = 0.0f;
	
	//左
	bool isLeft_ = true;
	//左のスケール
	Vector3 leftScale_ = INITIAL_SCALE_;
	//左の回転
	float_t leftRotate_ = 0.0f;

	//高速回転
	float_t rapidRotateTime_ = 0.0f;

	//スケール小さくするときの線形補間
	float_t scaleDownT_ = 0.0f;
	//カメラが動き出すか
	bool isCameraMove_ = false;
	//加速
	float_t cameraAccel_ = 0.01f;
	float_t cameraVelocity_ = 0.0f;

	//白フェード
	std::unique_ptr<Elysia::Sprite> whiteFade_ = nullptr;
	float_t whiteTramsparency_ = 0.0f;

	uint32_t selectBgmhandle_ = 0u;
	float_t bgmVolume_ = 0.0f;

	uint32_t decideSEhandle_ = 0u;
	uint32_t selectSEHandle_ = 0u;
};

