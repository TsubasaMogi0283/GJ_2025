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

}

void ToGameTitleScene::Update(TitleScene* titleScene){
	titleScene;
#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG


}


void ToGameTitleScene::DrawSprite(){

}

void ToGameTitleScene::DisplayImGui(){
	ImGui::Begin("ゲームへ(タイトル)");

	ImGui::End();


	
}
