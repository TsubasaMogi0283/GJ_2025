#include "StageObjectData.h"

#include <Input.h>
#include <LevelDataManager.h>

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
	for (size_t i = 0u; i < colliderNumber_; ++i) {
		std::unique_ptr<BaseObjectForLevelEditorCollider> collider = std::make_unique<BaseObjectForLevelEditorCollider>();
		collider->SetCollisionType(ColliderType::PointType);
		collider->SetSize()
		collider->Initialize();
		colliderToFlashLight_.push_back(std::move(collider));
	}
}

void StageObjectData::Update() {
	//レベルデータの更新
	levelDataManager_->Update(levelHandle_);


	const auto& colliders = levelDataManager_->GetCollider(levelHandle_, "Stage");
	const auto& colliders = levelDataManager_->Get(levelHandle_, "Stage");
	const auto& positions = levelDataManager_->GetObjectPositions(levelHandle_, "Stage");

	for (const auto& collider : colliderToFlashLight_) {
		//レベルエディタで設置したステージオブジェクトのコライダーを登録
	}

#ifdef _DEBUG
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