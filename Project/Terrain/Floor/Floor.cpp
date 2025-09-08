#include "Floor.h"
#include <VectorCalculation.h>

Floor::Floor() 
{
	// コライダー生成
	collider_ = std::make_unique<TerrainCollider>(this);

}

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
	visibilityState_ = TerrainVisibilityState::Hidden;
	// マテリアルはcolor.wを0.0fで透明に
	material_.color.w = 0.0f;

}

void Floor::Update()
{
	// トランスフォームの更新
	transform_.Update();
	// マテリアルの更新
	material_.Update();

	// 顕幽タイマーの更新
	UpdateVisibilityState();
}

void Floor::DrawObject3D(const Camera& camera, const SpotLight& spotLight)
{
	camera, spotLight;
	model_->Draw(transform_, camera, material_, spotLight);
}
