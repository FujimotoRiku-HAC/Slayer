#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

//
class SceneNull : public IScene {
public:
	//�J�n
	virtual void Start() override{}
	//�X�V
	virtual void Update(float delta_time) override{}
	//�`��
	virtual void Draw() const override{}
	//�I�����邩
	virtual bool IsEnd() const override { return false; }
	//�V�[���폜���邩
	virtual bool StackClear()const override { return false; }
	//�t���O�̏�����
	virtual void ResetFrag()override{}
	//���̃V�[����Ԃ�
	virtual int Next() const override { return -1; }
	//�I��
	virtual void End() override{}
	//�Q�[���I��
	virtual bool IsGameEnd()const override { return false; }
};

#endif
