#pragma once

/**
 * @file NormalBackTexture.h
 * @brief 通常の背景
 * @author 茂木翼
 */

#include <SelectScene/BaseBackTexture/BaseSelectBackTexture.h>
#include <BackTexture.h>

/// <summary>
/// 通常の背景
/// </summary>
class NormalBackTexture : public BaseSelectBackTexture {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalBackTexture() = default;

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
	~NormalBackTexture() = default;
private:
	std::unique_ptr<Elysia::BackTexture> backTexture_ = nullptr;

};

