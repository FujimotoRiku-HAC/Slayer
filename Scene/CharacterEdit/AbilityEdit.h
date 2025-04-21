#ifndef SPECIAL_EDIT_H_
#define SPECIAL_EDIT_H_

#include "AbilitySelect.h"
#include "Character/Player/SaveData.h"

class AbilityEdit {
public:

	//�R���X�g���N�^
	AbilityEdit();
	//�X�V
	void Update(float delta_time);
	//�v���C���[�A�j���[�V����
	void PlayerAbilityAnim(World* world);
	//�`��
	void Draw()const;
	//���S��`��
	void DrawLogo()const;
	//�Z�[�u
	void Save();

public:

	//�I�񂾂�
	bool IsSelect()const;

public:

	//�J�E���g�擾
	float IsSelectCount()const;

private:

	//�ݒ肵���K�E�Z�̍X�V
	void SetAbilityUpdate(float delta_time);
	//�K�E�Z�I���̍X�V
	void SelectAbilityUpdate(float delta_time);
	//�ݒ肵���K�E�Z�̕`��
	void SetAbilityDraw(int num)const;
	//�K�E�Z�̍폜
	void DeleteAbilityArray();
	//����ւ�
	void SwapAbilityArray();
	// num��min����max�̊Ԃ��z������
	void CycleArray(int& num, int min, int max);
	//�e�N�X�`�������[�h
	void TextureLoad();

private:
	//�A�r���e�B�Z���N�g
	AbilitySelect m_Abilities;
	//�Z�[�u
	SaveData m_Save;
	//�A�r���e�B�Z�b�g
	std::array<int, AbilityNum> m_SetAbilities{ 0,0 };
	//�A�r���e�B�J�E���g
	int m_SetAbilityCount{ 0 };
	//�Z���N�g�J�E���g
	int m_SelectCount{ 0 };
	//�I�񂾂�
	bool m_IsSelect{ false };

};

#endif