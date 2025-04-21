#ifndef GAME_CLEAR_H_
#define GAME_CLEAR_H_

class GameClear {
public:

	//�f�t�H���g�R���X�g���N�^
	GameClear() = default;
	//�f�X�g���N�^
	~GameClear();
	//�J�n
	void Start();
	//�`��
	void Draw()const;

private:

	//���ԃf�[�^�̎擾
	void LoadTimeData();
	//�����N�̌v�Z
	void Calclate();
	//�������N��`�悷�邩
	void RankBackCalulateDraw(char rank)const;

private:
	//��
	int m_Minutes{ 0 };
	//�b
	int m_Second{ 0 };
	//�����N
	char m_Rank;
	//�J���[
	const GScolor m_Color{ 0.f,0.f,0.f,0.7f };
};

#endif
