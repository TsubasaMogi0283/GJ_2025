#pragma once

/*
* @brief 床&壁などの地形の基底クラス
* @author Tsumita Hinata
*/

#include "WorldTransform.h" 
#include "Model.h"
#include "Material.h"
#include "AABB.h"

#include "Collider/TerrainCollider.h"


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
enum class TerrainVisibilityState {
	Hidden,       // 完全に隠れている
	Appearing,    // 出現演出中
	Visible,      // 完全に見えている
	Disappearing  // 消失演出中
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

	/// <summary>
	/// 顕幽状態の切り替え : 現す処理
	/// </summary>
	void OnReveal();

#pragma region accessor

	// モデルハンドル
	void SetModelHandle(uint32_t handle) { this->modelHandle_ = handle; }

	// スケール
	Vector3 GetScale() const { return transform_.scale; }
	void SetScale(const Vector3& scale) { this->transform_.scale = scale; }
	// 回転
	Vector3 GetRotate() const { return transform_.rotate; }
	void SetRotate(const Vector3& rotate) { this->transform_.rotate = rotate; }
	// 座標
	Vector3 GetTranslate() const { return transform_.translate; }
	void SetTranslate(const Vector3& translate) { this->transform_.translate = translate; }

	// ワールド座標
	Vector3 GetWorldPos() const { return transform_.GetWorldPosition(); }

	// コライダーの取得
	TerrainCollider* GetCollision() const {
		return collider_.get();
	}

	// 顕幽state
	TerrainVisibilityState GetHiddenState() const { return visibilityState_; }
	void SetHiddenState(TerrainVisibilityState state) { this->visibilityState_ = state; }

#pragma endregion


protected:

	/// <summary>
	/// 
	/// </summary>
	void UpdateVisibilityState();

	/// <summary>
	/// 個別演出
	/// </summary>
	void UpdateAppearing();
	void UpdateVisible();
	void UpdateDisappearing();

protected:

	// モデルのハンドル
	uint32_t modelHandle_ = 1u;
	// モデル
	std::unique_ptr<Elysia::Model> model_;

	// マテリアル
	Material material_{};

	// ワールドトランスフォーム
	WorldTransform transform_{};

	// コライダー
	std::unique_ptr<TerrainCollider> collider_;

	// 顕幽状態
	TerrainVisibilityState visibilityState_ = TerrainVisibilityState::Hidden;

	// 出現演出の経過時間
	float appearTimer_ = 0.0f;
	const float kAppearDuration_ = 1.0f;

	// 表示中の経過時間
	float visibleTimer_ = 0.0f;
	const float kVisibleDuration_ = 300.0f;

	// 消失演出の経過時間
	float disappearTimer_ = 0.0f;
	const float kDisappearDuration_ = 10.0f;
};