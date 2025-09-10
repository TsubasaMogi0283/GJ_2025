#pragma once

/**
 * @file BaseSelectBackTexture.h
 * @brief 背景テクスチャの基底クラス
 * @author 茂木翼
 */

#include <memory>

#include "BackTexture.h"

/// <summary>
/// 背景テクスチャの基底クラス
/// </summary>
class BaseSelectBackTexture {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画前処理
	/// </summary>
	virtual void PreDraw()=0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw()=0;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseSelectBackTexture() = default;


};

