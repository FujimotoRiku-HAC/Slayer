#ifndef OPTION_DATA_H_
#define OPTION_DATA_H_

class OptionData {
public:

	//BGM,SE�̉��ʃZ�[�u
	void DataSave(const char* file_path, const float bgm, const float se);
	//���ʂ̃��[�h
	void DataLoad(const char* file_path);

public:

	//BGM���ʎ擾
	float GetBGMValue()const;
	//SE�̉��ʎ擾
	float GetSEValue()const;

private:

	//�f�[�^
	std::vector<float>m_Data;
};

#endif