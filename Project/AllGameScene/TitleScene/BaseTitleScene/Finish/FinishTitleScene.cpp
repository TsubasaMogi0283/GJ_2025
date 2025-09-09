#include "FinishTitleScene.h"

#include <imgui.h>

#include "Input.h"
#include "TextureManager.h"
#include "LevelDataManager.h"
#include "Audio.h"

#include "TitleScene/TitleScene.h"
#include <SingleCalculation.h>

FinishTitleScene::FinishTitleScene(){
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

void FinishTitleScene::Initialize(){

}

void FinishTitleScene::Update(TitleScene* titleScene){


	threshold_ += 0.01f;
	dissolve_.threshold = SingleCalculation::Lerp(0.0f,1.0f, threshold_);

	//高速
	if (threshold_>2.0f) {
		//指定した時間を超えたらノイズシーンへ
			//ノイズへ
			titleScene->SetIsEnd();
			titleScene->SetIsGameEnd();
			return;
	}



#ifdef _DEBUG
	//ImGui表示用
	DisplayImGui();
#endif // _DEBUG

	

}


void FinishTitleScene::DrawSprite(){
}

void FinishTitleScene::DisplayImGui(){

	ImGui::Begin("終わり(タイトルシーン)");
	ImGui::SliderFloat("しきい値", &dissolve_.threshold, 0.0f, 2.0f);

	//ImGui::SliderFloat("しきい値",&dissolve_.threshold,0.0f,2.0f);
	ImGui::End();


}
