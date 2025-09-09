#pragma once

/**
 * @file FinishTitleScene.h
 * @brief 終わりのタイトルシーン
 * @author 茂木翼
 */

#include "Sprite.h"

#include "TitleScene/BaseTitleScene/BaseTitleScene.h"


/// <summary>
/// 終わりのタイトルシーン
/// </summary>
class FinishTitleScene : public BaseTitleScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	FinishTitleScene();

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
	~FinishTitleScene()override=default;


private:
	/// <summary>
	/// ImGui表示用
	/// </summary>
	void DisplayImGui()override;

private:
	//点滅の制限
	const uint32_t FLASH_TIME_LIMIT_ = 30u;
	//高速点滅の制限
	const uint32_t FAST_FLASH_TIME_LIMIT_ = 60u;
	//高速点滅の間隔
	const uint32_t FAST_FLASH_TIME_INTERVAL_ = 3u;
	//カウントが増える時間
	const uint32_t INCREASE_COUNT_TIME = 0u;
	//表示
	const uint32_t DISPLAY_TIME_ = 0u;
	//点滅の間隔
	const uint32_t FLASH_INTERVAL_ = 2u;
private:

	float_t threshold_ = 0.0f;

};