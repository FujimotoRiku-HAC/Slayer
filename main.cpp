#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Scene/OptionScene.h"
#include "Scene/CharacterEdit/CharacterEditScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/GameOver.h"
#include "Tween/Tween.h"

class MyGame : public gslib::Game {
public:
	//コンストラクタ
	MyGame() : gslib::Game{ ScreenWidth,ScreenHeight }{}
	//開始
	void start() override {
		//エフェクトの初期化
		gsInitEffect();
		m_SceneManager.Add(std::make_shared<TitleScene>());

	}
	//更新
	void update(float delta_time) {
		m_SceneManager.Update(delta_time);
		//Tweenの更新
		Tween::Update(delta_time);
	}
	//描画
	void draw() override {
		m_SceneManager.Draw();
	}
	//終了
	void end() override {
		m_SceneManager.End();
		//エフェクト終了
		gsFinishEffect();
	}

	// 終了判定処理をオーバーライド
	bool is_running() override {
		// パッドのBackとStartが両方押されていたら終了する
		if ((InputManager::Instance().IsBottonDown(InputManager::InputType::Back))&&
			(InputManager::Instance().IsBottonDown(InputManager::InputType::Pose)))
			return false;
		// キーボードのEscapeが押されていたら終了する
		if (gsGetKeyState(GKEY_ESCAPE))
			return false;
		if (m_SceneManager.IsGameEnd())
			return false;

		// 上記に該当しなければ、ゲーム続行
		return true;
	}

private:
	//シーンマネージャー
	SceneManager m_SceneManager;
};

int main() {
	return MyGame().run();
}