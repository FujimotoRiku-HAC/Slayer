#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include "IScene.h"

class GameOver : public IScene {
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

	//���g���C�X�V
	void RetryUpdate(float delta_time);
	//�^�C�g���X�V
	void TitleUpdate(float delta_time);
	//�G���h�X�V
	void EndUpdate(float delta_time);

private:

	enum Field {
		GameStart,
		Title,
		Return
	};

private:
	//�t�B�[���h
	Field m_Field;
	//Rect
	GSrect m_Rect;
	//�I������
	bool m_IsEnd{ false };
	bool m_IsClear{ false };
	bool m_IsGameEnd{ false };
	int m_NextScene = -1;

};


#endif