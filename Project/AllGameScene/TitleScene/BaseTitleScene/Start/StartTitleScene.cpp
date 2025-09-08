#include "StartTitleScene.h"

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "WindowsSetup.h"
#include "Audio.h"

#include "TitleScene/TitleScene.h"
#include <TitleScene/BaseTitleScene/Select/SelectTitleScene.h>
#include <SingleCalculation.h>

StartTitleScene::StartTitleScene(){
	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
	//ウィンドウクラス
	windowsSetup_ = Elysia::WindowsSetup::GetInstance();
	//オーディオ
	audio_ = Elysia::Audio::GetInstance();
}

void StartTitleScene::Initialize(){


}

void StartTitleScene::Update(TitleScene* titleScene){
	//線形補間で増やす
	radiusT_ += INCREASE_T_VALUE_;
	radiusT_=std::clamp(radiusT_,0.0f, 1.0f);
	pointLight_.radius = SingleCalculation::Lerp(MIN_, MAX_RADIUS_, radiusT_);

	if (pointLight_.radius >= MAX_RADIUS_) {
		pointLight_.radius = MAX_RADIUS_;
	}

	titleScene;

#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG


}


void StartTitleScene::DrawSprite(){

}

void StartTitleScene::DisplayImGui(){
	ImGui::Begin("開始(タイトル)");
	ImGui::InputFloat("半径", &pointLight_.radius);
	ImGui::End();


	
}
