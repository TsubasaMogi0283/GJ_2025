#pragma once

/**
 * @file NightBackTexture.h
 * @brief 夜の背景クラス
 * @author 茂木翼
 */

#include "SelectScene/BaseBackTexture/BaseSelectBackTexture.h"

#include <RandomNoise.h>
#include <RandomNoisePostEffect.h>

/// <summary>
/// 隠し
/// </summary>
class SecretBackTexture : public BaseSelectBackTexture {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SecretBackTexture() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SecretBackTexture() = default;

private:
	RandomNoise randomNoise_ = {};
	std::unique_ptr<Elysia::RandomNoisePostEffect>randomPostEffect_ = nullptr;


};

