#pragma once


/**
 * @file StartTitleScene.h
 * @brief タイトルの始めのクラス
 * @author 茂木翼
 */

#include <array>
#include <numbers>
#include <string>
#include <array>
#include "Sprite.h"
#include "TitleScene/BaseTitleScene/BaseTitleScene.h"

/// <summary>
/// ElysiaEngine
/// </summary>
namespace Elysia {

	/// <summary>
	/// ウィンドウクラス
	/// </summary>
	class WindowsSetup;

	/// <summary>
	/// オーディオ
	/// </summary>
	class Audio;
}

/// <summary>
/// タイトルの始め
/// </summary>
class StartTitleScene : public BaseTitleScene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StartTitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="titleScene">タイトルシーン(メイン)</param>
	void Update(TitleScene* titleScene)override;

	/// <summary>
	/// スプライト
	/// </summary>
	void DrawSprite()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StartTitleScene()override=default;


private:
	/// <summary>
	/// ImGUi表示用
	/// </summary>
	void DisplayImGui()override;

private:
	//ウィンドウクラス
	Elysia::WindowsSetup* windowsSetup_ = nullptr;

private:
	//サイズの減少値
	const float_t SIZE_DOWN_VALUE_ = 0.05f;
	//最小サイズ
	const float_t CIRCLE_MIN_SIZE_ = 0.0f;
	//最大音量
	const float_t MAX_VOLUME_ = 0.6f;
	//音量の増える値
	const float_t VOLUME_INCREASE_VALUE_ = 0.0005f;

	//テキストの数
	static const uint8_t TEXT_QUANTITY_ = 4u;
	//待ち回転
	const Vector3 WAITING_ROTATE_ = {.x =0.0f,.y = std::numbers::pi_v<float_t>*10.0f,.z=0.0f };
	//初期回転
	const Vector3 INITIAL_ROTATE_ = {};

	//テキストが後ろから飛んでくるまでの座標
	const float_t waitingPositionZ_ = -20.0f;

	const std::string textSyo_ = "Syo";
	const std::string textKai_ = "Kai";
	const std::string textMei_ = "Mei";
	const std::string textRo_ = "Ro";

private:
	enum TextCharacter {
		Syo,
		Kai,
		Mei,
		Ro
	};

	/// <summary>
	/// テキスト情報
	/// </summary>
	struct TextInformation {
		//初期座標
		Vector3 initialPosition = {};
		//待機座標
		Vector3 waitingPosition = {};
		//移動開始
		bool isStartMove_ = false;
		//移動終了
		bool isEndMove_ = false;

		//線形補間用変数
		//回転
		float_t rotateT_=0.0f;
		//座標
		float_t positionT_ = 0.0f;
		

		//番号
		std::string name_ = "";
	};

private:

	float_t radiusT_ = 0.0f;

	//ライトアップ終わったかどうか
	bool isEndLightUp_ = false;
	std::array<TextInformation,TEXT_QUANTITY_>textInformations_ = {};
	uint8_t releaseTextNumber_ = 0u;
	//移動開始タイマー
	float_t moveStartTimer_ = 0.0f;

	//テキストの移動が終わったかどうか
	bool isEndTextMove_ = false;
	//選択肢表示したか
	float_t selectTransparency_ = 0.0f;
	bool isDisplaySelection_ = false;

	uint32_t textSeHandle_ = 0u;

};