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

class TerrainManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TerrainManager() = default;

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
	void Create_NewTerrain(const Vector3& pos);


private:

	// 地形の配列
	std::list<std::shared_ptr<ITerrain>> terrains_;


};