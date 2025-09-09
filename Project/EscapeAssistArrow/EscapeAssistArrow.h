#pragma once
/**
 * @file EscapeAssistArrow.h
 * @brief 脱出アシストの矢印のクラス
 * @author 茂木翼
 */

#include <memory>
#include <Model.h>
#include <Sprite.h>

/// <summary>
/// ElysiaEngine
/// </summary>
namespace Elysia {
	/// <summary>
	/// テクスチャ管理クラス
	/// </summary>
	class TextureManager;

	/// <summary>
	/// ウィンドウクラス
	/// </summary>
	class WindowsSetup;

}


/// <summary>
/// カメラ
/// </summary>
struct Camera;

/// <summary>
/// スポットライト
/// </summary>
struct SpotLight;

/// <summary>
/// プレイヤー
/// </summary>
class Player;

/// <summary>
/// 脱出アシストの矢印
/// </summary>
class EscapeAssistArrow{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EscapeAssistArrow();

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
	void DrawSprite();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EscapeAssistArrow() = default;

public:
	/// <summary>
	/// プレイヤーの設定
	/// </summary>
	/// <param name="player"></param>
	inline void SetPlayer(Player* player) {
		this->player_ = player;
	}

	/// <summary>
	/// ゴールの座標を設定
	/// </summary>
	/// <param name="position"></param>
	void SetGoalPosition(const Vector2& position) {
		this->goalPosition_ = position;
	}

	/// <summary>
	/// シータの設定
	/// </summary>
	/// <param name="theta"></param>
	inline void SetTheta(const float_t& theta) {
		this->theta_ = theta;
	}

private:
	//テクスチャ管理クラス
	Elysia::TextureManager* textureManager_ = nullptr;
	//ウィンドウクラス
	Elysia::WindowsSetup* windowsSetup_ = nullptr;

private:

	//大きさ
	const float_t SCALE_ = 0.3f;
	//線形補間の増える量
	const float_t INCREASE_T_VALUE_ = 0.01f;

	//透明度の増える値
	const float_t INCREASE_TRANSPARENCY_VALUE_ = 0.01f;

private:
	//プレイヤー
	Player* player_ = nullptr;
	//フレーム
	std::unique_ptr<Elysia::Sprite>frame_ = nullptr;
	//メインの矢印
	std::unique_ptr<Elysia::Sprite>main_ = nullptr;


	//シータ
	float_t theta_ = 0.0f;
	//ゴールの中心座標
	Vector2 goalPosition_ = {};
	//差分
	Vector2 difference_ = {};
	//角度
	float_t arrowTheta_ = 0.0f;

	float_t offset_ = 0.0f;
};

