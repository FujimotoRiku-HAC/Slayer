#ifndef LOAD_SCENE_H_
#define LOAD_SCENE_H_

#include "IScene.h"

class LoadScene : public IScene {
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

	//�A�Z�b�g���[�h
	void AssetsLoad();

private:

	//�I������
	bool m_IsLoad{ true };
	bool m_IsEnd{ false };
	int m_NextScene{ -1 };
	//�^�C�}�[
	int m_Timer{ 0 };
	//��]����
	float m_Angle{ 0 };
};

#endif