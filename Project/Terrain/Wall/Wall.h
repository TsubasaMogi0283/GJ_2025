#pragma once

/*
* @brief 壁クラス
* @author Tsumita Hinata
*/

#include "../ITerrain.h"

class Wall : public ITerrain {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Wall();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Wall() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void DrawObject3D(const Camera& camera, const SpotLight& spotLight) override;


private:

	// モデル
	std::unique_ptr<Elysia::Model> model_;
	// マテリアル
	Material material_{};
};