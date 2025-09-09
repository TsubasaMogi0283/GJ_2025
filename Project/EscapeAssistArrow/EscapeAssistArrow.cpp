#include "EscapeAssistArrow.h"

#include <VectorCalculation.h>
#include <Easing.h>
#include <Player/Player.h>
#include <TextureManager.h>
#include <WindowsSetup.h>
#include <imgui.h>

EscapeAssistArrow::EscapeAssistArrow(){
	//インスタンスの取得
	//テクスチャ管理クラス
	textureManager_ = Elysia::TextureManager::GetInstance();
	//ウィンドウクラス
	windowsSetup_ = Elysia::WindowsSetup::GetInstance();
}

void EscapeAssistArrow::Initialize(){
	//プレイヤーが空だった場合停止
	assert(player_);

	float_t windowWidth = static_cast<float_t>(windowsSetup_->GetClientWidth());

	//フレーム
	uint32_t frameTextureHandle = textureManager_->Load("Resources/Sprite/Arrow/ArrowFrame.png");
	Vector2 frameSize = { 
		.x = static_cast<float_t>(textureManager_->GetTextureWidth(frameTextureHandle)),
		.y = static_cast<float_t>(textureManager_->GetTextureHeight(frameTextureHandle))
	};

	frame_.reset(Elysia::Sprite::Create(frameTextureHandle, {.x= windowWidth -frameSize.x,.y=0.0f}));
	//メイン
	uint32_t mainTextureHandle= textureManager_->Load("Resources/Sprite/Arrow/Arrow.png");
	//サイズ
	//アンカー設定するので半分にする
	Vector2 mainSize_ = { 
		.x = static_cast<float_t>(textureManager_->GetTextureWidth(mainTextureHandle))/2.0f,
		.y = static_cast<float_t>(textureManager_->GetTextureHeight(mainTextureHandle)/2.0f)
	};
	
	main_.reset(Elysia::Sprite::Create(mainTextureHandle, {.x = windowWidth - mainSize_.x,.y = mainSize_.y }));
	main_->SetAnchorPoint({ 0.5f,0.5f });
}

void EscapeAssistArrow::Update() {

	//スプライト、いわゆる2次元なのでY軸はいらない
	//XZだけ使う
	//差分
	difference_ = VectorCalculation::Subtract(goalPosition_, { .x = player_->GetWorldPosition().x,.y = player_->GetWorldPosition().z });
	//角度を計算
	arrowTheta_ = std::atan2f(difference_.y, difference_.x) - theta_;
	main_->SetRotate(-(arrowTheta_ + offset_));

#ifdef _DEBUG
	ImGui::Begin("矢印");
	ImGui::InputFloat2("差分", &difference_.x);
	ImGui::InputFloat("角度", &arrowTheta_);
	ImGui::SliderFloat("角度の補正", &offset_,-3.0f,3.0f);
	ImGui::End();
#endif // _DEBUG

}


void EscapeAssistArrow::DrawSprite() {
	//フレーム
	frame_->Draw();
	//メイン
	main_->Draw();
}