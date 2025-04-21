#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "Fade.h"

class IScene;

//�V�[���Ǘ��N���X
class SceneManager {
public:
	enum class EachScene {
		Title,
		CharacterEdit,
		Play,
		GameOver,
		Option,
		Load,
		Revert
	};

	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//�X�V
	void Update(float delta_time);
	//�`��
	void Draw()const;
	//�I��
	void End();
	//�V�[���ǉ�
	void Add(std::shared_ptr<IScene> scene);
	//�V�[���̒ǉ�
	void PushScene(EachScene scene);
	//�V�[���ύX
	void Change();
	//�V�[������
	void Clear();
	//�Q�[���I����
	bool IsGameEnd()const;

	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = default;
	SceneManager& operator = (const SceneManager& other) = default;
private:
	//�t�F�[�h
	Fade m_Fade;
	//�X�^�b�N
	std::stack<std::shared_ptr<IScene>>m_StackScene;
	//�Q�[���I��
	bool m_IsGameEnd = false;
};

#endif
