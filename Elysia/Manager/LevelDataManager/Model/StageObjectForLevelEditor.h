#pragma once

/**
 * @file StageObjectForLevelEditor.h
 * @brief レベルエディタ用のステージオブジェクトクラス
 * @author 茂木翼
 */

#include "BaseObjectForLevelEditor.h"
#include "StageObjectForLevelEditorCollider.h"


#pragma region 見え隠れの状態列挙型 顕幽
enum class SOFLEEVisibilityState {
	Hidden,       // 完全に隠れている
	Appearing,    // 出現演出中
	Visible,      // 完全に見えている
	Disappearing  // 消失演出中
};
#pragma endregion

/// <summary>
/// レベルエディタ用のステージオブジェクト
/// </summary>
class StageObjectForLevelEditor :public BaseObjectForLevelEditor {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageObjectForLevelEditor() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="modelhandle"></param>
	/// <param name="transform"></param>
	/// <param name="isHavingCollider"></param>
	/// <param name="isGenerateColliderToLight"></param>
	/// <param name="objectSize"></param>
	void Initialize(const uint32_t& modelhandle, const Transform& transform, const bool& isHavingCollider, const bool& isGenerateColliderToLight, const Vector3& objectSize) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	void Draw(const Camera& camera)override;

	/// <summary>
	/// 描画(スポットライト)
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="material"></param>
	/// <param name="spotLight"></param>
	void Draw(const Camera& camera, const SpotLight& spotLight)override;


public:

	/// <summary>
	/// AABB用のサイズを設定。コライダーのサイズから取得してね。
	/// </summary>
	/// <param name="main_size_"></param>
	inline void SetSize(const Vector3& size) {
		this->size_ = size;
	}


private:

	/// <summary>
	/// 現す処理
	/// </summary>
	void OnDisplay();

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
	void UpdateHidden();

private:
	//AABB用のサイズ
	Vector3 size_ = {};
	bool isDisplay_ = false;


	float_t transparency_ = 0.0f;

	SOFLEEVisibilityState sofleeState_ = SOFLEEVisibilityState::Hidden;

	// 出現演出の経過時間
	float appearTimer_ = 0.0f;
	const float kAppearDuration_ = 1.0f;

	// 表示中の経過時間
	float visibleTimer_ = 0.0f;
	const float kVisibleDuration_ = 5.0f * 60.0f;

	// 消失演出の経過時間
	float disappearTimer_ = 0.0f;
	const float kDisappearDuration_ = 3.0f * 60.0f;
};

