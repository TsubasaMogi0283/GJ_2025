#include "StageObjectForLevelEditor.h"

#include <imgui.h>

#include "VectorCalculation.h"
#include <CollisionConfig.h>
#include <Listener.h>
#include <numbers>

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


	// 初期SOFLEEStateはHiddenに設定しておく
	sofleeState_ = SOFLEEVisibilityState::Hidden;
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
			
			// 出現瞬間時の処理
			OnDisplay();
		}

		// 出現中の処理
		if (isDisplay_ == true) {

			UpdateVisibilityState();
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


void StageObjectForLevelEditor::OnDisplay()
{
	// 既に見えている or 出現中なら何もしない
	if (sofleeState_ == SOFLEEVisibilityState::Visible ||
		sofleeState_ == SOFLEEVisibilityState::Appearing) {
		return;
	}

	// 出現演出の開始
	sofleeState_ = SOFLEEVisibilityState::Appearing;
	appearTimer_ = 0.0f;

	//
	isDisplay_ = true;
}

void StageObjectForLevelEditor::UpdateVisibilityState()
{
	switch (sofleeState_) {
	case SOFLEEVisibilityState::Appearing:
	UpdateAppearing();
	break;

	case SOFLEEVisibilityState::Visible:
	UpdateVisible();
	break;

	case SOFLEEVisibilityState::Disappearing:
	UpdateDisappearing();
	break;

	case SOFLEEVisibilityState::Hidden:
	default:
	UpdateHidden();
	break;
	}
}

void StageObjectForLevelEditor::UpdateAppearing()
{
	appearTimer_++;
	if (appearTimer_ >= kAppearDuration_) {
		appearTimer_ = 0.0f;
		sofleeState_ = SOFLEEVisibilityState::Visible;
		material_.color.w = 1.0f;  // 透明を解除
	}
}

void StageObjectForLevelEditor::UpdateVisible()
{
	visibleTimer_++;
	if (visibleTimer_ >= kVisibleDuration_) {
		visibleTimer_ = 0.0f;
		sofleeState_ = SOFLEEVisibilityState::Disappearing;
	}
}

void StageObjectForLevelEditor::UpdateDisappearing()
{
	disappearTimer_++;

	// 進行度 0.0f ~ 1.0f
	float t = disappearTimer_ / kDisappearDuration_;

	// --- 追加: 点滅の周期を時間経過で短くする ---
	// 最初はゆっくり(周期0.5秒)、最後は超高速(周期0.05秒)くらいにする
	float basePeriod = 0.5f;     // 最初の点滅周期
	float minPeriod = 0.05f;    // 最後の点滅周期
	float currentPeriod = std::lerp(basePeriod, minPeriod, t);

	// sin波を使って点滅
	float flickerValue = std::sin(disappearTimer_ * (1.0f / currentPeriod) * 2.0f * std::numbers::pi_v<float>);

	if (flickerValue > 0.0f) {
		material_.color.w = 1.0f; // ON
	}
	else {
		material_.color.w = 0.0f; // OFF
	}

	// 完全に消えたら状態変更
	if (disappearTimer_ >= kDisappearDuration_) {
		disappearTimer_ = 0.0f;
		sofleeState_ = SOFLEEVisibilityState::Hidden;
		material_.color.w = 0.0f; // 完全に透明にする
		isDisplay_ = false;
	}
}

void StageObjectForLevelEditor::UpdateHidden()
{
	material_.color.w = 0.0f;
#ifdef _DEBUG
	material_.color.w = 0.1f;
#endif // _DEBUG
}
