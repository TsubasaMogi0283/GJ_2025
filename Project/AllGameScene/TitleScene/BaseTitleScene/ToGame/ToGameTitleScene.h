#pragma once


/**
 * @file ToGameTitleScene.h
 * @brief ゲームを始めるクラス
 * @author 茂木翼
 */

#include <array>
#include <numbers>
#include <string>
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
/// ゲームを始める
/// </summary>
class ToGameTitleScene : public BaseTitleScene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ToGameTitleScene();

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
	~ToGameTitleScene()override=default;


private:
	/// <summary>
	/// ImGUi表示用
	/// </summary>
	void DisplayImGui()override;

private:

	float_t velocity_ = {};
	float_t accel_ = 0.005f;
};