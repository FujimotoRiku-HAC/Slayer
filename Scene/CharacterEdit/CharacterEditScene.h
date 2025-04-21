#ifndef CHEARACTER_EDIT_SCENE_H_
#define CHEARACTER_EDIT_SCENE_H_

#include "Scene/IScene.h"
#include "Scene/Fade.h"
#include "World/World.h"
#include "Scene/CharacterEdit/AbilityEdit.h"
#include "Scene/CharacterEdit/SkillEdit.h"
#include "Animation/AnimatedMesh.h"


class CharacterEditScene : public IScene {
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
	//�A�r���e�B�X�V
	void AbilityUpdate(float delta_time);
	//�X�L���X�V
	void SkillUpdate(float delta_time);
	//�߂�X�V
	void ReturnUpdate(float delta_time);
	//�v���C���[�̍s��
	void PlayerAction();

private:
	enum Text{
		GameStart,
		Ability,
		Skill,
		Return
	};
private:

	//���b�V��
	AnimatedMesh m_Mesh{NULL,NULL};
	//�g�����X�t�H�[��
	GStransform m_Transform;
	//�e�L�X�g
	Text m_Text;
	//�t�F�[�h
	Fade m_Fade;
	//���[���h
	World m_World;
	//�A�r���e�B
	AbilityEdit m_Ability;
	//�X�L��
	SkillEdit m_Skill;

	//�I������
	bool m_IsEnd{ false };
	bool m_IsSelect{ false };
	bool m_IsClear{ false };
	int m_NextScene{ -1 };

};

#endif