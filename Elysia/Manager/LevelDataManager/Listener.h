#pragma once

/**
 * @file Listener.h
 * @brief リスナークラス
 * @author 茂木翼
 */

#include "Vector3.h"

/// <summary>
/// リスナー
/// </summary>
class Listener {
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Listener() = default;

public:
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	inline Vector3 GetPosition()const {
		return position_;
	}

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position"></param>
	inline void SetPosition(const Vector3& position) {
		this->position_ = position;
	}

	/// <summary>
	/// 動く方向の設定
	/// </summary>
	/// <returns></returns>
	inline Vector3 GetMove()const {
		return move_;
	}

	/// <summary>
	/// 方向の設定
	/// </summary>
	/// <param name="move"></param>
	inline void SetMove(const Vector3& move) {
		this->move_ = move;
	}

	/// <summary>
	/// リリース状態を設定
	/// </summary>
	/// <param name="isReleaseKey"></param>
	inline void SetIsReleaseKey(const bool& isReleaseKey) {
		this->isReleaseKey_ = isReleaseKey;
	}

	/// <summary>
	/// リリース状態を取得
	/// </summary>
	/// <returns></returns>
	inline bool GetIsReleaseKey()const {
		return isReleaseKey_;
	}

protected:
	//位置
	Vector3 position_ = {};
	//動き
	Vector3 move_ = {};
	//キーを離した瞬館を取得するためにこの変数を入れた
	bool isReleaseKey_ = false;

};