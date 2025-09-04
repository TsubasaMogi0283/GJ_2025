#include "Wall.h"

Wall::Wall() {}

void Wall::Init()
{
	// トランスフォームの初期化
	transform_.Initialize();

	// モデルの設定
	model_.reset(Elysia::Model::Create(modelHandle_));

	// マテリアルの初期化
	material_.Initialize();
	material_.lightingKinds = LightingType::NoneLighting;
}

void Wall::Update()
{
}

void Wall::DrawObject3D(const Camera& camera, const SpotLight& spotLight)
{
	camera, spotLight;
	model_->Draw(transform_, camera, material_, spotLight);
}
