#include "SceneManager.h"
#include "SceneNull.h"
#include "TitleScene.h"
#include "Scene/CharacterEdit/CharacterEditScene.h"
#include "GamePlayScene.h"
#include "OptionScene.h"
#include "LoadScene.h"
#include "GameOver.h"
#include "Fade.h"

static SceneNull scene_null;//nullシーン

//コンストラクタ
SceneManager::SceneManager(){}

//デストラクタ
SceneManager::~SceneManager() {
	Clear();
}

//更新
void SceneManager::Update(float delta_time) {

	//ゲーム終了
	if (m_StackScene.top()->IsGameEnd()) {
		m_IsGameEnd = true;
	}

	//シーンが終了しているか
	if (m_StackScene.top()->IsEnd()) {
		if(m_Fade.FadeIn(delta_time))return;

		//シーン変更
		PushScene((EachScene)m_StackScene.top()->Next());
	}
	//シーンの更新
	m_StackScene.top()->Update(delta_time);
	//フェードアウト
	m_Fade.FadeOut(delta_time);
}

//描画
void SceneManager::Draw() const {
	//現在のシーンを描画
	m_StackScene.top()->Draw();
	m_Fade.Draw();
}

//終了
void SceneManager::End() {
	Clear();
}

//シーンの追加
void SceneManager::Add(std::shared_ptr<IScene> scene) {
	m_StackScene.push(scene);
	m_StackScene.top()->Start();
}

//シーンの変更
void SceneManager::Change() {

	m_StackScene.top()->End();
	m_StackScene.pop();
	m_StackScene.top()->ResetFrag();

}

void SceneManager::PushScene(EachScene scene){
	//シーンの削除
	// スタックを削除
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

//シーン消去
void SceneManager::Clear() {
	while (!m_StackScene.empty()) {
		//シーン削除
		m_StackScene.top()->End();
		m_StackScene.pop();
	}
}

bool SceneManager::IsGameEnd() const{
	return m_IsGameEnd;
}
