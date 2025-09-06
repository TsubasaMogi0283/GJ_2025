#pragma once

/**
 * @file StageObjectData.h
 * @brief ステージオブジェクトクラス
 * @author 茂木翼
 */

#include <memory>
#include <vector>
#include <Model/BaseObjectForLevelEditorCollider.h>

 /// <summary>
 /// ElysiaEngine(前方宣言)
 /// </summary>
namespace Elysia {
	/// <summary>
	/// レベルエディタ
	/// </summary>
	class LevelDataManager;

	/// <summary>
	/// 入力クラス
	/// </summary>
	class Input;
}


/// <summary>
/// カメラ
/// </summary>
struct Camera;

/// <summary>
/// スポットライト
/// </summary>
struct SpotLight;

/// <summary>
/// ステージオブジェクト
/// </summary>
class StageObjectData{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageObjectData();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="spotLight"></param>
	void Draw(const Camera& camera, const SpotLight& spotLight);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageObjectData() = default;

public:

private:
	//インプット
	Elysia::Input* input_ = nullptr;
	//レベルエディタ
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
	//ハンドル
	uint32_t levelHandle_ = 0u;


private:
	//コライダーの数
	size_t colliderNumber_ = 0u;

};

