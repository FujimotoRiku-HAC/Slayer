#ifndef FADE_H_
#define FADE_H_

class Fade{
public:

	//�R���X�g���N�^
	Fade(float speed = 0.1f);
	//�`��
	void Draw()const;
	//�X�s�[�h����
	void SetSpeed(float speed);

public:

	//�t�F�[�h�C��
	bool FadeIn(float delta_time);
	//�t�F�[�h�A�E�g
	bool FadeOut(float delta_time);

public:

	//�A���t�@�l�擾
	float GetAlpha()const;

private:
	//�X�s�[�h
	float m_Speed{ 0.0f };
	//�A���t�@�l
	float m_Alpha{ 0.0f };
};

#endif