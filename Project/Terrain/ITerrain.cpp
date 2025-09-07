#include "ITerrain.h"

void ITerrain::OnReveal()
{
    // 既に見えている or 出現中なら何もしない
    if (visibilityState_ == TerrainVisibilityState::Visible ||
        visibilityState_ == TerrainVisibilityState::Appearing) {
        return;
    }

    // 出現演出の開始
    visibilityState_ = TerrainVisibilityState::Appearing;
    appearTimer_ = 0.0f;
}

void ITerrain::UpdateVisibilityState()
{
    switch (visibilityState_) {
    case TerrainVisibilityState::Appearing:
    UpdateAppearing();
    break;

    case TerrainVisibilityState::Visible:
    UpdateVisible();
    break;

    case TerrainVisibilityState::Disappearing:
    UpdateDisappearing();
    break;

    case TerrainVisibilityState::Hidden:
    default:
    break;
    }
}

void ITerrain::UpdateAppearing()
{
    appearTimer_++;
    if (appearTimer_ >= kAppearDuration_) {
        appearTimer_ = 0.0f;
        visibilityState_ = TerrainVisibilityState::Visible;
        material_.color.w = 1.0f;
    }
}

void ITerrain::UpdateVisible()
{
    visibleTimer_++;
    if (visibleTimer_ >= kVisibleDuration_) {
        visibleTimer_ = 0.0f;
        visibilityState_ = TerrainVisibilityState::Disappearing;
    }
}

void ITerrain::UpdateDisappearing()
{
    disappearTimer_++;

    // 進行度 0.0f ~ 1.0f
    float t = disappearTimer_ / kDisappearDuration_;

    // 点滅のパターン：短い周期でランダムにON/OFF
    // 例：だんだんOFFの時間が増える
    float flicker = (std::rand() % 100) / 100.0f; // 0.0〜1.0 ランダム

    if (flicker > t) {
        // まだ点灯している
        material_.color.w = 1.0f;
    }
    else {
        // 消えている
        material_.color.w = 0.0f;
    }

    if (disappearTimer_ >= kDisappearDuration_) {
        disappearTimer_ = 0.0f;
        visibilityState_ = TerrainVisibilityState::Hidden;
        material_.color.w = 0.0f;
    }
}

