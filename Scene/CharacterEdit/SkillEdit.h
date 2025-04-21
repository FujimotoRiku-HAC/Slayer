#ifndef SKILL_EDIT_H_
#define SKILL_EDIT_H_

#include "SkillSelect.h"
#include "Character/Player/SaveData.h"
#include "World/World.h"

class SkillEdit {
public:

	//�R���X�g���N�^
	SkillEdit();
	//�X�V
	void Update(float delta_time);
	//�v���C���[�A�j���[�V����
	void SkillEffect(World* world);
	//�`��
	void Draw()const;
	//���S�`��
	void DrawLogo()const;
	//�Z�[�u
	void Save();

private:

	//�Z�b�g���ꂽ�A�C�e�����X�V
	void SetSkillUpdate(float delta_time);
	//�X�L���I�����̍X�V
	void ChoiceItemUpdate(float delta_time);
	//�Z�b�g���ꂽ�X�L���̕`��
	void SetSkillDraw(int num)const;
	//�Z�b�g�X�L���̏���
	void DeleteItemArray();
	//�X�L������ւ�
	void SwapItemArray();
	//num��min����max�̊Ԃŏz��
	void CycleArray(int& num, int min, int max);
	//�e�N�X�`�����[�h
	void TextureLoad();

private:

	//�X�L��
	SkillSelect m_Skills;
	//�Z�[�u
	SaveData m_Save;
	//���[���h
	World m_World;
	//�A�C�e���ݒ�
	std::array<int, ItemNum>m_SetSkill{ 0,0,0 };

	//�Z�b�g�X�L���J�E���g
	int m_SetSkillCount{ 0 };
	//�I�񂾐�
	int m_ChoicesCount{ 0 };
	//�I�񂾂�
	bool m_IsSelect{ false };

};

#endif