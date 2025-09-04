#pragma once

/*
* @brief 床&壁などの地形の基底クラス
* @author Tsumita Hinata
*/

#include "WorldTransform.h" 
#include "Model.h"
#include "Material.h"
#include "AABB.h"

#pragma region 前方宣言
struct Camera; // カメラ
struct Material; // マテリアル
namespace Elysia { 
class Input; // 入力
class ModelManager; // モデル管理
class TextureManager; // テクスチャ管理
class LevelDataManager; // レベルデータ管理
};
#pragma endregion 

#pragma region 見え隠れの状態列挙型
enum class TerrainHiddenState {
	Visible,   // 見えている
	Hidden     // 隠れている
};
#pragma endregion

class ITerrain {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ITerrain() = default;

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ITerrain() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void DrawObject3D(const Camera& camera, const SpotLight& spotLight) = 0;

protected:

	// ワールドトランスフォーム
	WorldTransform transform_{};
	// 状態 隠れているのが初期状態
	TerrainHiddenState hiddenState_ = TerrainHiddenState::Hidden;
};