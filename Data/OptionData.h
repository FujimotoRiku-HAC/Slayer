#ifndef OPTION_DATA_H_
#define OPTION_DATA_H_

class OptionData {
public:

	//BGM,SEの音量セーブ
	void DataSave(const char* file_path, const float bgm, const float se);
	//音量のロード
	void DataLoad(const char* file_path);

public:

	//BGM音量取得
	float GetBGMValue()const;
	//SEの音量取得
	float GetSEValue()const;

private:

	//データ
	std::vector<float>m_Data;
};

#endif