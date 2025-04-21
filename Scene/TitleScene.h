#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"
#include "Fade.h"
#include "World/World.h"
#include "Animation/AnimatedMesh.h"
#include "Data/OptionData.h"

//�^�C�g���V�[��
class TitleScene : public IScene {
public:

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
	void ResetFrag() override;
	//���̃V�[����Ԃ�
	virtual int Next()const override;
	//�I��
	virtual void End() override;
	//�Q�[���I����
	virtual bool IsGameEnd()const override;

private:

	//�X�^�[�g�X�V
	void StartUpdate(float delta_time);
	//�I�v�V�����X�V
	void OptionUpdate(float delta_time);
	//�G���h�X�V
	void EndUpdate(float delta_time);

private:

	enum TextField {
		GameStart,
		Option,
		GameEnd
	};

private:
	
	//�t�F�[�h
	Fade m_Fade;
	//���[���h
	World m_World;
	//�f�[�^
	OptionData m_Data;
	//���b�V��
	AnimatedMesh m_Mesh{ NULL,NULL,NULL };
	//�g�����X�t�H�[��
	GStransform m_Transform;
	//�e�L�X�g
	TextField m_TextField;
	//Rect
	GSrect m_Rect;

	//�I���t���O
	bool m_IsEnd{ false };
	bool m_IsGameEnd{ false };
	bool m_IsClear{ false };
	int m_NextScene{ -1 };
};

#endif
