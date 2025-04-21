#ifndef WORLD_H_
#define WORLD_H_

#include "Actor/ActorManager.h"
#include "Number/NumberManager.h"

//���[���h�N���X
class World : public IWorld {
public:

	//�R���X�g���N�^
	World() = default;
	//�f�X�g���N�^
	~World();
	//�X�V
	void Update(float delta_time);
	//�`��
	void Draw() const;
	//����
	void Clear();
	//�J�����̒ǉ�
	void AddCamera(Actor* camera);
	//���C�g�̒ǉ�
	void AddLight(Actor* light);
	//�t�B�[���h�ǉ�
	void AddField(Field* field);
	//���b�Z�[�W�̑��M
	virtual void OnMessage(const std::string& message, void* param = nullptr) override;
	//�N���A�t���O
	virtual void SetClearFrag()override;
	//�I���t���O
	virtual void SetGameOverFrag()override;
	//�X���[��ԃ^�C�}�[�{��
	virtual void PlaySlowTimer(float time);
	//�A�N�^�[�̒ǉ�
	virtual void AddActor(Actor* actor) override;
	//�i���o�[�\���N���X�̒ǉ�
	virtual void AddNumber(Number* number);
	//�f�t�H���g�^�C�}�[
	virtual void DefaultTime();
	//
	static void ShadowMapCallback(void* param, const GSmatrix4*, const GSmatrix4*);

public:

	//�J�����̎擾
	virtual Actor* GetCamera() override;
	//���C�g�̎擾
	virtual Actor* GetLight() override;
	//�t�B�[���h�̎擾
	virtual Field* GetField() override;
	//�A�N�^�[�̌���
	virtual Actor* FindActor(const std::string& name) const override;
	//�w�肵���^�O�������A�N�^�[�̌���
	virtual std::vector<Actor*> FindActorWithTag(const std::string& tag) const override;

public:

	//�A�N�^�[����Ԃ�
	virtual int CountActor() const override;
	//�w�肵���^�O�������A�N�^�[����Ԃ�
	virtual int CountActorWithTag(const std::string& tag) const override;

public:

	//�N���A��
	virtual bool IsClear()const override;
	//�I����
	virtual bool IsGameOver()const override;

	//�R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

private:
	//�i���o�[�N���X
	NumberManager m_Numbers;
	//s�N�^�[�}�l�[�W���[
	ActorManager m_Actors;
	//���C�g
	Actor* m_Light{ nullptr };
	//�J����
	Actor* m_Camera{ nullptr };
	//�t�B�[���h
	Field* m_Field{ nullptr };

	//�X���[��Ԃɂ���p�̃^�C�}�[
	float m_ScaleTimer{ 1.0f };

	//�Q�[���I��
	bool m_ClearFrag{ false };
	bool m_GameOverFrag{ false };
};
#endif
