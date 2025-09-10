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
	static SelectedStageInformation* GetInstance();

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
		if (isRecord_ == false) {
			stageNumber_ = number;
			isRecord_ = true;
		}
	}

	inline uint8_t GetRecordedNumber() {
		//記録していたものを取得
		if (isRecord_ == true) {
			int result = stageNumber_;

			//一次的に記録しそれを取得させる
			stageNumber_=1u;
			isRecord_ = false;
			return result;
		}
	}

private:
	//ステージナンバー
	uint8_t stageNumber_ = 0u;
	//記録したか
	bool isRecord_ = false;;



};

