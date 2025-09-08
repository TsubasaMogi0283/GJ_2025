#include "StageObjectForLevelEditor.h"

#include <imgui.h>

#include "VectorCalculation.h"
#include <CollisionConfig.h>
#include <Listener.h>

void StageObjectForLevelEditor::Initialize(const uint32_t& modelhandle, const Transform& transform, const bool& isHavingCollider, const bool& isGenerateColliderToLight, const Vector3& objectSize) {
	
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
		colliderToPlayer_ = std::make_unique<StageObjectForLevelEditorCollider>();
		colliderToPlayer_->Initialize();
		colliderToPlayer_->SetSize(objectSize);
	}
	if (isGenerateColliderToLight == true) {

		material_.color.w = 0.0f;

#ifdef _DEBUG
		material_.color.w = 0.1f;
#endif // _DEBUG
		

		colliderToLight_ = std::make_unique<StageObjectForLevelEditorCollider>();
		colliderToLight_->Initialize();
		colliderToLight_->SetName("ForLight");
		colliderToLight_->SetCollisionType(ColliderType::PointType);
		colliderToLight_->SetCollisionAttribute(COLLISION_ATTRIBUTE_STAGE_OBJECT);
		colliderToLight_->SetCollisionMask(COLLISION_ATTRIBUTE_FLASH_LIGHT);
	}


}

void StageObjectForLevelEditor::Update(){

	//ワールドトランスフォームの更新
	worldTransform_.Update();

	Vector3 worldPosition = worldTransform_.GetWorldPosition();

	//AABBの設定
	aabb_ = {
		.min = VectorCalculation::Subtract(worldPosition,size_),
		.max = VectorCalculation::Add(worldPosition,size_)
	};
	if (colliderToPlayer_ != nullptr) {
		colliderToPlayer_->SetObjectPosition(worldPosition);
		colliderToPlayer_->SetCenterPosition(worldPosition);
		colliderToPlayer_->Update();
	}

	if (colliderToLight_ != nullptr) {
		colliderToLight_->SetObjectPosition(worldPosition);
		colliderToLight_->SetCenterPosition(worldPosition);
		colliderToLight_->Update();

		if (colliderToLight_->GetIsTouch() == true&& listener_->GetIsReleaseKey()==true) {
			isDisplay_ = true;
		}


		if (isDisplay_ == true) {
			
			displayTime_ += 1.0f / 60.0f;


			if (displayTime_ > 3.0f) {
				material_.color.w -= 0.01f;

			}
			else {
				material_.color.w = 1.0f;
			}

			if (material_.color.w <= 0.0f) {
				material_.color.w = 0.0f;
				isDisplay_ = false;
				displayTime_ = 0.0f;
			}
		}
		else {
#ifdef _DEBUG
			material_.color.w = 0.1f;
#endif // _DEBUG

		}

	}

	
	




	

#ifdef _DEBUG
	ImGui::Begin("ステージオブジェクト"); 
	Vector3 position = worldTransform_.GetWorldPosition();
	if (colliderToLight_ != nullptr) {
		ImGui::InputFloat3("座標", &position.x);

	}
	if (colliderToPlayer_ != nullptr) {
		ImGui::InputFloat3("AABB_Max", &aabb_.max.x);
		ImGui::InputFloat3("AABB_Min", &aabb_.min.x);

	}

	ImGui::InputFloat("透明度", &material_.color.w);
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
