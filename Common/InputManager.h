#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class InputManager {
public:
	enum InputType {
		Decision,			//����
		Return,				//�߂�
		Delete,				//����
		Pose,				//�|�[�Y�{�^��
		Back,				//�o�b�N�{�^��
		Attack,				//�U��
		Ability,			//�A�r���e�B
		Avoid,				//���
		Ability1,			//�A�r���e�B�P
		Ability2,			//�A�r���e�B�Q
		SelectMoveUp,		//�I���o�\�����
		SelectMoveDown,		//�I���o�\������
		SelectMoveRight,	//�I���o�\���E��
		SelectMoveLeft,		//�I���o�\������
		ResetCamera,		//�J�������Z�b�g
		SkillSelect,		//�Z���N�g

	};

private:

	enum {
		Trigger = 1,
		State	= 2,
		Detach  = 3,
		Short   = 4
	};

public:

	//�C���X�^���X
	static InputManager Instance();
	//�R���X�g���N�^
	InputManager();
	//���X�e�B�b�N�̓��͂̎󂯎��
	GSvector2 LeftAxis();
	//�E�X�e�B�b�N�̓��͂��󂯎��
	GSvector2 RightAxis();

public:

	//�������Ƃ�
	bool IsBottonDown(InputType type);
	//���������Ă���Ƃ�
	bool IsBottonState(InputType type);
	//�������Ƃ�
	bool IsBottonDetach(InputType type);
	//�{�^�����������u��
	bool IsBottonShortPress(InputType type);
	//�����ԃ{�^�����������Ƃ�
	bool IsBottonLongPress(InputType type);

private:

	//���������ԂŎ�ނ�Ԃ�
	int IsBottonPressType(InputType type);

private:

	//�C���v�b�g
	std::unordered_map<InputType, GSushort>m_InputLibrary;
	//�i���o�[
	int m_Num = 0;
	//�^�C�}�[
	static float m_Timer;
};

#endif