#ifndef SKILL_SELECT_H_
#define SKILL_SELECT_H_

#include "Character/Player/Skill/SkillType.h"

class World;

class SkillSelect {
public:
	//�R���X�g���N�^
	SkillSelect();
	//�`��
	void Draw()const;
	//����
	void Explanation(int num)const;
	//�X�L���I�����ɃG�t�F�N�g�ݒu
	void SetSkillEffect(World* world,int num);
	//�X�L���폜
	void DeleteSkill(int skill);
	//�A�C�e���Z�b�g
	void SetSkill(int skill);
	//�ŏ��ɕ`�悷��ʒu
	void SetDrawFirstNum(int num);
	//�X�L���̔ԍ�
	void SetSelectSkillNum(int num);
	//
	void Initialize();

public:

	//�I�𒆂̃A�C�e��
	int SelectSkill(int num);
	//�T�C�Y�̎擾
	int Size()const;
	//�ŏ��ɕ`�悷��ʒu�̔ԍ�
	int FirstDrawNum()const;

private:

	//���[�h
	void SkillLoad();

private:
	//�X�L��
	std::vector<int> m_Skills;
	//�ŏ��̈ʒu
	int m_DrawFirstNum{ 0 };
	//�X�L���̔ԍ�
	int m_SkillNum{ 0 };

	bool m_SkillUse{ false };
};

#endif