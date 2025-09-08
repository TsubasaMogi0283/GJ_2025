#pragma once

/*
* @brief 地形の一元管理クラス
* @author Tsumita Hinata
*/

#include <memory>
#include <list>
#include <vector>

#include "ITerrain.h"
#include "Floor/Floor.h"
#include "Wall/Wall.h"

namespace Elysia {
class Input; // 入力管理
class ModelManager; // モデル管理
class TextureManager; // テクスチャ管理
class LevelDataManager; // レベルデータ管理
};

class TerrainManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TerrainManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TerrainManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(const Camera& camera, const SpotLight& spotLight);

	/// <summary>
	/// 座標を指定して生成
	/// </summary>
	void Create_NewFloor(const Vector3& pos);
	void Create_NewWall(const Vector3& pos);


private:

	// 地形の配列
	std::list<std::shared_ptr<ITerrain>> terrains_;

	// モデルハンドル
	uint32_t floorModelHandle_ = 1u;
	uint32_t wallModelHandle_ = 1u;

private:

	// 入力クラス
	Elysia::Input* input_ = nullptr;
	//テクスチャ管理クラス
	Elysia::TextureManager* textureManager_ = nullptr;
	//モデル管理クラス
	Elysia::ModelManager* modelManager_ = nullptr;
	//レベルエディタ
	Elysia::LevelDataManager* levelDataManager_ = nullptr;
};