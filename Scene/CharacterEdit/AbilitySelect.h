#ifndef ABILITY_SELECT_H_
#define ABILITY_SELECT_H_

#include "Character/Player/Ability/AbilityType.h"
#include "Animation/AnimatedMesh.h"

class World;

class AbilitySelect {
public:

	//�R���X�g���N�^
	AbilitySelect();
	//�`��
	void Draw()const;
	//����
	void ExplanationDraw(int num)const;
	//�A�j���[�V�����ύX
	void PlayerAbilityAnim(World* world, int num);
	//�K�E�Z�폜
	void DeleteAbility(int num);
	//�A�r���e�B�ǉ�
	void SetAbility(int special);
	//�ŏ��̈ʒu�̔ԍ�
	void SetDrawFirst(int num);
	//�I�����Ă���A�r���e�B�̔ԍ�
	void SetSelectAbilityNum(int num);
	//�A�r���e�B�g�p������
	void Initialize();

public:

	//�K�E�Z�̑I��
	int SelectAbility(int num);
	//�T�C�Y�ݒ�
	int Size()const;
	//�ŏ��ɕ`�悷��ʒu�̔ԍ�
	int FirstDrawNum()const;

private:

	//�K�E�Z�����̃��[�h
	void SpecialExplanationLoad();

private:
	//�A�r���e�B
	std::vector<int> m_Abilities;

	//�A�r���e�B�g�p������
	bool m_IsAbilityUse{ false };

	//�ŏ��̈ʒu
	int m_DrawFirstNum{ 0 };

	//�A�r���e�B�i���o�[
	int m_AbilityNum{ 0 };
};

#endif