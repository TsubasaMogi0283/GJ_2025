#include "ITerrain.h"

void ITerrain::OnHidden()
{
	// 既にStateがHiddenなら早期return
	if(hiddenState_ == TerrainHiddenState::Hidden) 
		return;

	// ステートをHiddenへ
	hiddenState_ = TerrainHiddenState::Hidden;
}

void ITerrain::OnVisible()
{
	// 既にStateがHiddenなら早期return
	if (hiddenState_ == TerrainHiddenState::Visible)
		return;

	// ステートをHiddenへ
	hiddenState_ = TerrainHiddenState::Visible;
	// タイマー設定
	hiddenTimer_ = HIDDEN_DURATION_;
}

void ITerrain::Update_HiddenTimer()
{
	// ステートがHiddenならタイマーの更新に入る
	if (hiddenState_ == TerrainHiddenState::Visible) {

		hiddenTimer_--;

		// 0以下でステートをもとに戻す
		if (hiddenTimer_ <= 0.0f) {

			hiddenState_ = TerrainHiddenState::Hidden;
			hiddenTimer_ = 0.0f;
		}
	}
}
