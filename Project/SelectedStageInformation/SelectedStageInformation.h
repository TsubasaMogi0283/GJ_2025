#pragma once
#include <cstdint>
class SelectedStageInformation{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectedStageInformation() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectedStageInformation() = default;
public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns></returns>
	static SelectedStageInformation* GetInstance() {
		static SelectedStageInformation instance;
		return &instance;
	};

	/// <summary>
	/// コピーコンストラクタ禁止
	/// </summary>
	/// <param name="selectedStageInformation"></param>
	SelectedStageInformation(const SelectedStageInformation& selectedStageInformation) = delete;

	/// <summary>
	/// 代入演算子を無効にする
	/// </summary>
	/// <param name="selectedStageInformation"></param>
	/// <returns></returns>
	SelectedStageInformation& operator=(const SelectedStageInformation& selectedStageInformation) = delete;


public:
	inline void RecordSelectedStageNumber(const uint8_t& number) {
		stageNumber_ = number;
	}

	inline uint8_t GetRecordedNumber() const{
		return stageNumber_;
	}

	/// <summary>
	/// リセット
	/// </summary>
	inline void Reset() {
		stageNumber_ = 1u;
	}
private:
	//ステージナンバー
	uint8_t stageNumber_ = 0u;

};

