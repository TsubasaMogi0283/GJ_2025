#include "Wall.h"

Wall::Wall()
{
	// モデルの生成
	model_ = std::make_unique<Elysia::Model>();
}

void Wall::Init()
{
	// トランスフォームの初期化
	transform_.Initialize();

	// モデルの設定
	uint32_t modelHandle = 0;
	model_.reset(Elysia::Model::Create(modelHandle));

	// マテリアルの初期化
	material_.Initialize();
}

void Wall::Update()
{
}

void Wall::DrawObject3D(const Camera& camera, const SpotLight& spotLight)
{
	camera, spotLight;
	model_->Draw(transform_, camera, material_);
}
