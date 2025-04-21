#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include "IScene.h"
#include "World/World.h"
#include "Fade.h"
#include "Assets.h"
#include "Animation/AnimatedMesh.h"
#include "CharacterEdit/SkillEdit.h"
#include "Data/ClearTimer.h"
#include "GameClear.h"

class GamePlayScene : public IScene {
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

	// �X�|�[��
	void SpawnGolem();

private:

	//�v���C�V�[��
	void PlayUpdate(float delta_time);
	//�^�C�g���ɖ߂�
	void TitleUpdate(float delta_time);
	//�Q�[���I��
	void EndUpdate(float delta_time);
	//�N���A�`��
	void GameClearDraw()const;

private:

	enum Text {
		Play,
		TitleReturn,
		EndReturn
	};

private:

	//���[���h
	World m_World;
	//�t�F�[�h
	Fade m_Fade;
	//�^�C�}�[
	ClearTimer m_Timer;
	//�N���A
	GameClear m_GameClear;
	//�e�L�X�g
	Text m_Text;
	//�o��������
	bool m_IsGenerate{ false };
	//�N���A�^�C�}�[
	float m_ClearTimer{ 0.0f };

	//�I������
	bool m_IsEnd{ false };
	bool m_IsClear{ false };
	bool m_IsSceneClear{ false };
	bool m_IsGameEnd{ false };
	int m_NextScene{ 0 };
};

#endif