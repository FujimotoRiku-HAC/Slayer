#include "SceneManager.h"
#include "SceneNull.h"
#include "TitleScene.h"
#include "Scene/CharacterEdit/CharacterEditScene.h"
#include "GamePlayScene.h"
#include "OptionScene.h"
#include "LoadScene.h"
#include "GameOver.h"
#include "Fade.h"

static SceneNull scene_null;//null�V�[��

//�R���X�g���N�^
SceneManager::SceneManager(){}

//�f�X�g���N�^
SceneManager::~SceneManager() {
	Clear();
}

//�X�V
void SceneManager::Update(float delta_time) {

	//�Q�[���I��
	if (m_StackScene.top()->IsGameEnd()) {
		m_IsGameEnd = true;
	}

	//�V�[�����I�����Ă��邩
	if (m_StackScene.top()->IsEnd()) {
		if(m_Fade.FadeIn(delta_time))return;

		//�V�[���ύX
		PushScene((EachScene)m_StackScene.top()->Next());
	}
	//�V�[���̍X�V
	m_StackScene.top()->Update(delta_time);
	//�t�F�[�h�A�E�g
	m_Fade.FadeOut(delta_time);
}

//�`��
void SceneManager::Draw() const {
	//���݂̃V�[����`��
	m_StackScene.top()->Draw();
	m_Fade.Draw();
}

//�I��
void SceneManager::End() {
	Clear();
}

//�V�[���̒ǉ�
void SceneManager::Add(std::shared_ptr<IScene> scene) {
	m_StackScene.push(scene);
	m_StackScene.top()->Start();
}

//�V�[���̕ύX
void SceneManager::Change() {

	m_StackScene.top()->End();
	m_StackScene.pop();
	m_StackScene.top()->ResetFrag();

}

void SceneManager::PushScene(EachScene scene){
	//�V�[���̍폜
	// �X�^�b�N���폜
	if (m_StackScene.top()->StackClear())Clear();

	switch (scene){
	case EachScene::Title:m_StackScene.push(std::make_shared<TitleScene>());break;
	case EachScene::CharacterEdit:CharacterEdit:m_StackScene.push(std::make_shared<CharacterEditScene>()); break;
	case EachScene::Play:m_StackScene.push(std::make_shared<GamePlayScene>()); break;
	case EachScene::GameOver:m_StackScene.push(std::make_shared<GameOver>()); break;
	case EachScene::Option:m_StackScene.push(std::make_shared<OptionScene>()); break;
	case EachScene::Load:m_StackScene.push(std::make_shared<LoadScene>()); break;
	case EachScene::Revert:Change(); return; break;
	}
	m_StackScene.top()->Start();
}

//�V�[������
void SceneManager::Clear() {
	while (!m_StackScene.empty()) {
		//�V�[���폜
		m_StackScene.top()->End();
		m_StackScene.pop();
	}
}

bool SceneManager::IsGameEnd() const{
	return m_IsGameEnd;
}
