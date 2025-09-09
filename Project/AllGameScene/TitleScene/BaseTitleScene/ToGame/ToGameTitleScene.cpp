#include "ToGameTitleScene.h"

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "WindowsSetup.h"
#include "Audio.h"

#include "TitleScene/TitleScene.h"
#include <TitleScene/BaseTitleScene/Select/SelectTitleScene.h>
#include <SingleCalculation.h>
#include <VectorCalculation.h>

ToGameTitleScene::ToGameTitleScene(){
	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void ToGameTitleScene::Initialize(){

	pointLight_.radius = MAX_RADIUS_;
	camera_.translate.y = 1.4f;
	camera_.translate.z = -9.8f;
}

void ToGameTitleScene::Update(TitleScene* titleScene){

	//加速
	velocity_ += accel_;
	camera_.translate.z += velocity_;


	if (camera_.translate.z >= 30.0f) {
		titleScene->SetIsEnd();
		return;
	}

#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG


}


void ToGameTitleScene::DrawSprite(){

}

void ToGameTitleScene::DisplayImGui(){
	ImGui::Begin("ゲームへ(タイトル)");
	ImGui::InputFloat("加速", &velocity_);
	ImGui::End();


	
}
