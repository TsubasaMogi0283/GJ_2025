#include "TerrainManager.h"

void TerrainManager::Init()
{

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
		terr->DrawObject3D(camera, spotLight);
	}
}

void TerrainManager::Create_NewTerrain(const Vector3& pos)
{
	pos;
}
