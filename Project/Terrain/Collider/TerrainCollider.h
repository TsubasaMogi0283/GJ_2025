#pragma once
#include "Collider.h"

/*
* @brief Terrainのコリジョンクラス
* @author Tsumita Hinata
*/


#pragma region 前方宣言
struct Camera;	  // カメラ
struct Material;  // マテリアル
struct SpotLight; // スポットライト
class ITerrain;   // 親クラス
#pragma endregion

class TerrainCollider : public Collider {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TerrainCollider() = default;
	TerrainCollider(ITerrain* p_owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TerrainCollider() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 接触
	/// </summary>
	void OnCollision([[maybe_unused]] const Collider& collider) override;

	/// <summary>
	/// 非接触
	/// </summary>
	void OffCollision() override;

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition() override;


private:

	// 親クラス
	ITerrain* owner_ = nullptr;
};