#include "OptionData.h"


void OptionData::DataSave(const char* file_path, const float bgm, const float se){
	std::ofstream filepath;
	filepath.open(file_path);

	filepath << bgm << std::endl;
	filepath << se << std::endl;

	filepath.close();
}

void OptionData::DataLoad(const char* file_path){
	std::ifstream filepath(file_path);
	std::string str;

	while (std::getline(filepath, str)) {
		m_Data.push_back(atof(str.c_str()));
	}

	filepath.close();
}

float OptionData::GetBGMValue() const{
	return m_Data[0];
}

float OptionData::GetSEValue() const{
	return m_Data[1];
}
