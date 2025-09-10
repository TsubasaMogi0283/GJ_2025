
#include "SecretBackTexture.h"

void SecretBackTexture::Initialize() {
	//生成
	randomPostEffect_ = std::make_unique<Elysia::RandomNoisePostEffect>();

	//初期化
	randomPostEffect_->Initialize();

	randomNoise_.Initialize();

}

void SecretBackTexture::Update()
{
	randomNoise_.Update();
}

void SecretBackTexture::PreDraw()
{
	randomPostEffect_->PreDraw();
}

void SecretBackTexture::Draw()
{
	randomPostEffect_->Draw(randomNoise_);
}

