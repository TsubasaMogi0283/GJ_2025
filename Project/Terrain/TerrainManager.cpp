#include "TerrainManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "LevelDataManager.h"

TerrainManager::TerrainManager()
{
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//モデル管理クラス
	modelManager_ = Elysia::ModelManager::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
}

void TerrainManager::Init()
{
	// 使用するモデルデータの読み込み
	floorModelHandle_ = modelManager_->Load("Resources/Model/Terrain/Floor", "Floor.obj");
	wallModelHandle_ = modelManager_->Load("Resources/Model/Terrain/Wall", "Wall.obj");

}

void TerrainManager::Update()
{
	for (auto& terr : terrains_) {
		terr->Update();
	}
}

void TerrainManager::Draw(const Camera& camera, const SpotLight& spotLight)
{
	for (auto& terr : terrains_) {
		// 隠れた状態であればスキップ
		if (terr->Get_HiddenState() == TerrainHiddenState::Hidden) {
			continue;
		}
		terr->DrawObject3D(camera, spotLight);
	}
}

void TerrainManager::Create_NewFloor(const Vector3& pos)
{
	std::unique_ptr<Floor> floor =  std::make_unique<Floor>();

	floor->Set_ModelHandle(floorModelHandle_); // モデルハンドルの設定
	floor->Init(); // 初期化
	floor->Set_Translate(pos); // 座標の設定
	
	terrains_.push_back(std::move(floor));
}

void TerrainManager::Create_NewWall(const Vector3& pos)
{
	std::unique_ptr<Wall> wall = std::make_unique<Wall>();

	wall->Set_ModelHandle(wallModelHandle_); // モデルハンドルの設定
	wall->Init(); // 初期化
	wall->Set_Translate(pos); // 座標の設定

	terrains_.push_back(std::move(wall));
}
