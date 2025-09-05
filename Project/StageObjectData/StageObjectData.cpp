#include "StageObjectData.h"
#include <imgui.h>
#include <Input.h>
#include <LevelDataManager.h>
#include <Model/StageObjectForLevelEditorCollider.h>
#include <CollisionConfig.h>

StageObjectData::StageObjectData(){
	//インスタンスの取得
	//入力	
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
}

void StageObjectData::Initialize(){
	//ハンドルの取得
	levelHandle_ = levelDataManager_->Load("GameStage/GameStage.json");

	//コライダーの数
	colliderNumber_ = levelDataManager_->GetCollider(levelHandle_, "Stage").size();
	const auto& sizes = levelDataManager_->GetSizes(levelHandle_, "Stage");
	for (size_t i = 0u; i < colliderNumber_; ++i) {
		//ライト用のコライダーを取得
		std::unique_ptr<BaseObjectForLevelEditorCollider> collider = std::make_unique<StageObjectForLevelEditorCollider>();
		collider->Initialize();
		collider->SetCollisionType(ColliderType::PointType);
		collider->SetCollisionAttribute(COLLISION_ATTRIBUTE_STAGE_OBJECT);
		collider->SetCollisionMask(COLLISION_ATTRIBUTE_FLASH_LIGHT);
		collider->SetSize(sizes[i]);
		//挿入
		colliderToFlashLight_.push_back(std::move(collider));
	}
}

void StageObjectData::Update() {
	//レベルデータの更新
	levelDataManager_->Update(levelHandle_);


	//座標の取得
	const auto& positions = levelDataManager_->GetObjectPositions(levelHandle_, "Stage");
	
	for (size_t i = 0u; i < colliderToFlashLight_.size();++i) {
		//中心座標の登録
		colliderToFlashLight_[i]->SetObjectPosition(positions[i]);
	}

	const auto& objectDatas = levelDataManager_->GetObjectDatas(levelHandle_, "Stage");
	int a = 0;
	for (const auto& objectData : objectDatas) {
		//見つかった時だけ通す
		if (objectData.name.find("Cube")!=std::string::npos) {
			++a;
			objectData.objectForLeveEditor->SetTransparency(1.0f);
		}
	}

	a;


#ifdef _DEBUG
	ImGui::Begin("ステージデータ");
	for (size_t i = 0u; i < colliderToFlashLight_.size(); ++i) {
		int32_t newI = static_cast<int32_t>(i);
		ImGui::InputInt("数", &newI);
		bool isCollision = colliderToFlashLight_[i]->GetIsTouch();
		ImGui::Checkbox("衝突したかどうか", &isCollision);

	}
	
	ImGui::End();

	//再読み込み
	if (input_->IsTriggerKey(DIK_R) == true) {
		levelDataManager_->Reload(levelHandle_);
	}
#endif // _DEBUG

}

void StageObjectData::Draw(const Camera& camera, const SpotLight& spotLight) {
	//レベルエディタのオブジェクトを描画
	levelDataManager_->Draw(levelHandle_, camera, spotLight);
}