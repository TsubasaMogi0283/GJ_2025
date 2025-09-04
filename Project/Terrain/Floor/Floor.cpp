#include "Floor.h"

Floor::Floor() {}

void Floor::Init()
{
	// トランスフォームの初期化
	transform_.Initialize();

	// モデルの設定
	model_.reset(Elysia::Model::Create(modelHandle_));

	// マテリアルの初期化
	material_.Initialize();
	material_.lightingKinds = LightingType::NoneLighting;

	// 見え隠れの初期ステート
	hiddenState_ = TerrainHiddenState::Hidden;
}

void Floor::Update()
{
	// トランスフォームの更新
	transform_.Update();
	// マテリアルの更新
	material_.Update();

	// 顕幽タイマーの更新
	Update_HiddenTimer();
}

void Floor::DrawObject3D(const Camera& camera, const SpotLight& spotLight)
{
	camera, spotLight;
	model_->Draw(transform_, camera, material_, spotLight);
}
