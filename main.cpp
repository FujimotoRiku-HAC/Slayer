#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Scene/OptionScene.h"
#include "Scene/CharacterEdit/CharacterEditScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameOver.h"
#include "Tween/Tween.h"

class MyGame : public gslib::Game {
public:
	//�R���X�g���N�^
	MyGame() : gslib::Game{ ScreenWidth,ScreenHeight }{}
	//�J�n
	void start() override {
		//�G�t�F�N�g�̏�����
		gsInitEffect();
		m_SceneManager.Add(std::make_shared<TitleScene>());

	}
	//�X�V
	void update(float delta_time) {
		m_SceneManager.Update(delta_time);
		//Tween�̍X�V
		Tween::Update(delta_time);
	}
	//�`��
	void draw() override {
		m_SceneManager.Draw();
	}
	//�I��
	void end() override {
		m_SceneManager.End();
		//�G�t�F�N�g�I��
		gsFinishEffect();
	}

	// �I�����菈�����I�[�o�[���C�h
	bool is_running() override {
		// �p�b�h��Back��Start������������Ă�����I������
		if ((InputManager::Instance().IsBottonDown(InputManager::InputType::Back))&&
			(InputManager::Instance().IsBottonDown(InputManager::InputType::Pose)))
			return false;
		// �L�[�{�[�h��Escape��������Ă�����I������
		if (gsGetKeyState(GKEY_ESCAPE))
			return false;
		if (m_SceneManager.IsGameEnd())
			return false;

		// ��L�ɊY�����Ȃ���΁A�Q�[�����s
		return true;
	}

private:
	//�V�[���}�l�[�W���[
	SceneManager m_SceneManager;
};

int main() {
	return MyGame().run();
}