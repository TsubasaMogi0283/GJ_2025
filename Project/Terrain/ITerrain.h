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

#pragma region 見え隠れの状態列挙型 顕幽
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

	void On() {
		OnVisible();
	}

#pragma region accessor

	// モデルハンドル
	void Set_ModelHandle(uint32_t handle) { this->modelHandle_ = handle; }

	// スケール
	Vector3 Get_Scale() const { return transform_.scale; }
	void Set_Scale(const Vector3& scale) { this->transform_.scale = scale; }
	// 回転
	Vector3 Get_Rotate() const { return transform_.rotate; }
	void Set_Rotate(const Vector3& rotate) { this->transform_.rotate = rotate; }
	// 座標
	Vector3 Get_Translate() const { return transform_.translate; }
	void Set_Translate(const Vector3& translate) { this->transform_.translate = translate; }

	// 顕幽state
	TerrainHiddenState Get_HiddenState() const { return hiddenState_; }
	void Set_HiddenState(TerrainHiddenState state) { this->hiddenState_ = state; }

#pragma endregion


protected:

	/// <summary>
	/// 顕幽状態の切り替え : 隠れる処理
	/// </summary>
	void OnHidden();

	/// <summary>
	/// 顕幽う状態の切り替え : 現れる処理
	/// </summary>
	void OnVisible();

	/// <summary>
	/// 顕幽タイマーの更新
	/// </summary>
	void Update_HiddenTimer();


protected:

	// モデルのハンドル
	uint32_t modelHandle_ = 1u;
	
	// ワールドトランスフォーム
	WorldTransform transform_{};
	
	// 顕幽状態
	TerrainHiddenState hiddenState_ = TerrainHiddenState::Hidden;

	// 顕幽タイマー
	float hiddenTimer_ = 0.0f;
	const float HIDDEN_DURATION_ = 1.0f * 60.0f;
};