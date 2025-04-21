#ifndef OPTION_SCENE_H_
#define OPTION_SCENE_H_

#include "IScene.h"
#include "UI/Slider.h"
#include "Data/OptionData.h"
#include "Fade.h"

class OptionScene : public IScene {
public:

	//�f�X�g���N�^
	~OptionScene();
	//�J�n
	virtual void Start() override;
	//�X�V
	virtual void Update(float delta_time) override;
	//�`��
	virtual void Draw() const override;
	//�I�����Ă��邩
	virtual bool IsEnd() const override;
	//�V�[���폜
	bool StackClear()const override;
	//�t���O������
	void ResetFrag()override;
	//���̃V�[����Ԃ�
	virtual int Next()const override;
	//�I��
	virtual void End() override;
	//�Q�[���I����
	virtual bool IsGameEnd()const override;

private:

	//BGM�o�[�̍X�V
	void BGMUpdate(float delta_time);
	//SE�o�[�̍X�V
	void SEUpdate(float delta_time);
	//�߂�{�^������
	void BackUpdate(float delta_time);

private:

	enum Field{
		BGM,
		SE,
		Back
	};

private:

	//�t�F�[�h
	Fade m_Fade;
	//�f�[�^
	OptionData m_Data;
	//BGM�X���C�_�[
	Slider* m_BGMSlider;
	//SE�X���C�_�[
	Slider* m_SESlider;
	//Rect
	GSrect m_Rect;
	//Pos
	GSvector2 m_Pos;
	//�t�B�[���h
	Field m_Field = Field::BGM;
	//BGM�̒l
	float m_BGMValue{ 1.0f };
	//SE�̒l
	float m_SEValue{ 1.0f };

	//�I������
	bool m_IsEnd{ false };
	bool m_IsSelect{ false };
};

#endif