#include "StageObjectForLevelEditor.h"

#include <imgui.h>

#include "VectorCalculation.h"

void StageObjectForLevelEditor::Initialize(const uint32_t& modelhandle, const Transform& transform, const bool& isHavingCollider, const Vector3& objectSize) {
	
	//レベルエディタ用のオブジェクトのタイプ
	objectType_ = LevelEditorObjectType::StageObject;

	//モデルの生成
	model_.reset(Elysia::Model::Create(modelhandle));

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.scale = transform.scale;
	worldTransform_.rotate = transform.rotate;
	worldTransform_.translate = transform.translate;

	//マテリアルの初期化
	material_.Initialize();

	//コライダーを持っていれば生成
	if (isHavingCollider == true) {
		isGenerateCollider_ = true;
		collider_ = std::make_unique<StageObjectForLevelEditorCollider>();
		collider_->Initialize();
		collider_->SetSize(objectSize);
	}

}

void StageObjectForLevelEditor::Update(){

	//ワールドトランスフォームの更新
	worldTransform_.Update();

	//AABBの設定
	aabb_ = {
		.min = VectorCalculation::Subtract(worldTransform_.GetWorldPosition(),size_),
		.max = VectorCalculation::Add(worldTransform_.GetWorldPosition(),size_)
	};

	//中心座標を設定
	if (isGenerateCollider_ == true) {
		collider_->SetCenterPosition(worldTransform_.GetWorldPosition());

	}
	
#ifdef _DEBUG
	ImGui::Begin("ステージオブジェクト"); 
	Vector3 position = worldTransform_.GetWorldPosition();
	ImGui::InputFloat3("座標", &position.x);
	ImGui::InputFloat3("AABB_Max", &aabb_.max.x);
	ImGui::InputFloat3("AABB_Min", &aabb_.min.x);
	ImGui::End();
#endif // _DEBUG



}

void StageObjectForLevelEditor::Draw(const Camera& camera){
	//スポットライトに設定
	material_.lightingKinds = LightingType::NoneLighting;
	//変更したのでここで更新させる
	material_.Update();
	//モデルの描画
	model_->Draw(worldTransform_, camera, material_);
}

void StageObjectForLevelEditor::Draw(const Camera& camera, const SpotLight& spotLight){
	//スポットライトに設定
	material_.lightingKinds = LightingType::SpotLighting;
	//変更したのでここで更新させる
	material_.Update();
	//モデルの描画
	model_->Draw(worldTransform_, camera, material_, spotLight);
}
