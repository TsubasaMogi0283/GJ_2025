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
	colliderNumber_ = levelDataManager_->GetColliderToPlayer(levelHandle_, "Stage").size();
}

void StageObjectData::Update() {
	//レベルデータの更新
	levelDataManager_->Update(levelHandle_);



	const auto& objectDatas = levelDataManager_->GetObjectDatas(levelHandle_, "Stage");
	for (const auto& objectData : objectDatas) {
		//見つかった時だけ通す
		if (objectData.name.find("Cube")!=std::string::npos&& objectData.isHavingCollider==true) {
			objectData.objectForLeveEditor->SetTransparency(1.0f);
		}

		
	}



#ifdef _DEBUG
	ImGui::Begin("ステージデータ");
	
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