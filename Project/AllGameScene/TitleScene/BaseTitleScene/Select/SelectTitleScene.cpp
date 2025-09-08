#include "SelectTitleScene.h"

#include <imgui.h>

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "TitleScene/TitleScene.h"

SelectTitleScene::SelectTitleScene(){

	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//入力クラス
	input_ = Elysia::Input::GetInstance();
	//レベルエディタ管理クラス
	levelDataManager_ = Elysia::LevelDataManager::GetInstance();
}

void SelectTitleScene::Initialize(){

}

void SelectTitleScene::Update(TitleScene* titleScene){


	titleScene;
	
#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG

}

void SelectTitleScene::DrawSprite(){
}

void SelectTitleScene::DisplayImGui(){
	ImGui::Begin("ゲームシーンへ(タイトル)");

	ImGui::End();

}
