#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "Fade.h"

class IScene;

//シーン管理クラス
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

	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//更新
	void Update(float delta_time);
	//描画
	void Draw()const;
	//終了
	void End();
	//シーン追加
	void Add(std::shared_ptr<IScene> scene);
	//シーンの追加
	void PushScene(EachScene scene);
	//シーン変更
	void Change();
	//シーン消去
	void Clear();
	//ゲーム終了か
	bool IsGameEnd()const;

	//コピー禁止
	SceneManager(const SceneManager& other) = default;
	SceneManager& operator = (const SceneManager& other) = default;
private:
	//フェード
	Fade m_Fade;
	//スタック
	std::stack<std::shared_ptr<IScene>>m_StackScene;
	//ゲーム終了
	bool m_IsGameEnd = false;
};

#endif
