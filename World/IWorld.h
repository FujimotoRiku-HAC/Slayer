#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;
class Field;
class Number;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	//���z�f�X�g���N�^
	virtual ~IWorld() = default;
	//�A�N�^�[�ǉ�
	virtual void AddActor(Actor* actor) = 0;
	//�i���o�[�\���A�N�^�[
	virtual void AddNumber(Number* number) = 0;
	//���b�Z�[�W�̑��M
	virtual void OnMessage(const std::string& message, void* param = nullptr) = 0;
	//�X���[�^�C�}�[�̐ݒ�
	virtual void PlaySlowTimer(float time) = 0;
	//�f�t�H���g�^�C�}�[
	virtual void DefaultTime() = 0;
	//�N���A�t���O�̐ݒ�
	virtual void SetClearFrag() = 0;
	//�I���t���O�̐ݒ�
	virtual void SetGameOverFrag() = 0;

public:

	//�A�N�^�[�̌���
	virtual Actor* FindActor(const std::string& name) const = 0;
	//�w�肵���^�O�������A�N�^�[�̌���
	virtual std::vector<Actor*>FindActorWithTag(const std::string& tag) const = 0;
	//�t�B�[���h�̎擾
	virtual Field* GetField() = 0;
	//�J�����̎擾
	virtual Actor* GetCamera() = 0;
	//���C�g�̎擾
	virtual Actor* GetLight() = 0;

public:

	//�A�N�^�[����Ԃ�
	virtual int CountActor() const = 0;
	//�w�肵���^�O�������A�N�^�[����Ԃ�
	virtual int CountActorWithTag(const std::string& tag) const = 0;

public:

	//�Q�[���N���A��
	virtual bool IsClear()const  = 0;
	//�I����
	virtual bool IsGameOver()const = 0;

};

#endif
