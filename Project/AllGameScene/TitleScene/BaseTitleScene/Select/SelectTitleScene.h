#pragma once

/**
* @file SelectTitleScene.h
* @brief 選択クラス
* @author 茂木翼
*/

#include "Sprite.h"
#include "TitleScene/BaseTitleScene/BaseTitleScene.h"

/// <summary>
/// 選択へ
/// </summary>
class SelectTitleScene : public BaseTitleScene {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectTitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="titleScene">タイトルシーン(メイン)</param>
	void Update(TitleScene* titleScene)override;


	/// <summary>
	/// スプライト
	/// </summary>
	void DrawSprite()override;


	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectTitleScene() override =default;

private:
	/// <summary>
	/// ImGui用
	/// </summary>
	void DisplayImGui();


private:
	//透明度の変化
	const float_t INITIAL_TRANSPARENCY = 0.01f;

	const std::string ARROW_ = "Arrow";
	const std::string START_ = "Start";
	const std::string END_ = "End";

	//高速回転の値
	const float_t RAPID_ROTATE_VALUE_ = 0.4f;

	//矢印の高さ補正
	const float_t ARROW_POSITION_OFFSET_ = 0.2f;

	//選択時のスケール
	float_t SELECTED_SCALE_=0.5f;
	//選択時ではない時のスケール
	float_t NO_SELECTED_SCALE_ = 0.3f;

private:
	//初期座標
	Vector3 startInitialPosition_ = {};
	Vector3 endInitialPosition_ = {};
	Vector3 arrowInitialPosition_ = {};
	//上
	bool isArrowUp_ = false;
	//下
	bool isArrowDown_ = false;
	
	//矢印
	//座標
	Vector3 arrowPosition_ = {};
	//回転
	Vector3 arrowRotate_ = {};
	//高速回転をするかどうか
	bool isRapidRotate_ = true;
	//高速回転の時間
	float_t rapidRotateTime_ = 0.0f;
	//回転用の線形補間
	float_t rotateT_ = 0.0;
	//回転速度
	float_t rotateVelocity_ = 0.0f;

	// 待機時間
	float_t changeWaitingTime_ = 0.0f;
	
	//開始のスケール
	Vector3 startScale_ = {};
	//終了のスケール
	Vector3 endScale_ = {};

	//選択
	bool isDecice_ = false;

	//BGM
	uint32_t titleBgmHandle_ = 0u;
	float_t bgmVolume_ = 1.0f;


	uint32_t decideSEhandle_ = 0u;
	uint32_t selectSEHandle_ = 0u;

};

