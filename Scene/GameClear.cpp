#include "GameClear.h"
#include "SceneManager.h"
#include "Number/NumberTexture.h"

GSrect m_Rect{ 0.0f,0.0f,0.0f,0.0f };

GameClear::~GameClear(){}

void GameClear::Start(){
	//BGM�ǂݍ���
	gsLoadBGM(Clear_BGM,					"Assets/Sound/BGM/clear.ogg", GS_TRUE);
	//�e�N�X�`���ǂݍ���
	gsLoadTexture(Clear_Background_Texture, "Assets/Texture/UI/Clear/clear_bg.png");
	gsLoadTexture(Clear_Rank_Texture,		"Assets/Texture/UI/Clear/rank.png");
	gsLoadTexture(Clear_SRank_bg,			"Assets/Texture/UI/Clear/s_rank_bg.png");
	gsLoadTexture(Clear_ARank_bg,			"Assets/Texture/UI/Clear/a_rank_bg.png");
	gsLoadTexture(Clear_BRank_bg,			"Assets/Texture/UI/Clear/b_rank_bg.png");
	gsLoadTexture(Clear_CRank_bg,			"Assets/Texture/UI/Clear/c_rank_bg.png");

	gsPlayBGM(Clear_BGM);
	//�^�C�����[�h
	LoadTimeData();
	//�����N�̌v�Z
	Calclate();
}

void GameClear::Draw() const{
	//�w�i
	gsDrawRectangle2D(&ClearRectBG, &m_Color);
	//�����N�ɂ����BG�ω�
	RankBackCalulateDraw(m_Rank);
	//�Q�[���N���A�\��
	m_Rect = { 0.0f,0.0f,ClearRectScale.x ,ClearRectScale.y };
	gsDrawSprite2D(Clear_Text, &ClearPos, &m_Rect, NULL, NULL, NULL, NULL);
	//�\��
	m_Rect = { 0.0f,ClearRectScale.y,ClearRectScale.x ,ClearRectScale.y* 2  };
	gsDrawSprite2D(Clear_Text, &ClearTextPos, &m_Rect, NULL, NULL, NULL, NULL);

}

void GameClear::LoadTimeData(){
	std::ifstream filepath("Data/time_data.txt");
	std::string str;

	std::vector<int>time;
	while (std::getline(filepath, str)) {
		time.push_back(atoi(str.c_str()));
	}

	filepath.close();

	m_Minutes = time.at(0);
	m_Second = time.at(1);
}

void GameClear::Calclate(){
	if (m_Second > CRankTime) {
		m_Rank = 'C';
	}
	else if(m_Second > BRankTime){
		m_Rank = 'B';
	}
	else if (m_Second > ARankTime) {
		m_Rank = 'A';
	}
	else {
		m_Rank = 'S';
	}
}

void GameClear::RankBackCalulateDraw(char rank) const{

	//�N���A�V�[���؂���T�C�Y
	GSuint n = Clear_SRank_bg;

	GScolor color{ 1.0f,1.0f,1.0f,1.0f };

	switch (rank){
	case 'S':
		n = Clear_SRank_bg;
		m_Rect = { 0.0f,0.0f,RankRectScale.x,RankRectScale.y };
		color = { 1.0f,1.0f,0.0f,1.0f };
		break;
	case 'A':
		n = Clear_ARank_bg;
		m_Rect = { 0.0f,RankRectScale.y,RankRectScale.x,RankRectScale.y * 2 };
		color = { 1.0f,0.0f,0.0f,1.0f };
		break;
	case 'B':
		n = Clear_BRank_bg;
		m_Rect = { 0.0f,RankRectScale.y * 2,RankRectScale.x,RankRectScale.y * 3 };
		color = { 0.5f,0.0f,1.0f,1.0f };
		break;
	case 'C':
		n = Clear_CRank_bg;
		m_Rect = { 0.0f,RankRectScale.y * 3 ,RankRectScale.x,RankRectScale.y * 4 };
		color = { 0.8f,0.8f,0.8f,1.0f };
		break;
	default:
		break;
	}
	gsDrawSprite2D(n, &ClearRankPos, NULL, NULL, NULL, &ClearScale, NULL);
	gsDrawSprite2D(Clear_Rank_Texture, &RankPos, &m_Rect, NULL, &color, &RankScale, NULL);

}
