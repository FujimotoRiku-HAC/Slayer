#ifndef WORLD_H_
#define WORLD_H_

#include "Actor/ActorManager.h"
#include "Number/NumberManager.h"

//ワールドクラス
class World : public IWorld {
public:

	//コンストラクタ
	World() = default;
	//デストラクタ
	~World();
	//更新
	void Update(float delta_time);
	//描画
	void Draw() const;
	//消去
	void Clear();
	//カメラの追加
	void AddCamera(Actor* camera);
	//ライトの追加
	void AddLight(Actor* light);
	//フィールド追加
	void AddField(Field* field);
	//メッセージの送信
	virtual void OnMessage(const std::string& message, void* param = nullptr) override;
	//クリアフラグ
	virtual void SetClearFrag()override;
	//終了フラグ
	virtual void SetGameOverFrag()override;
	//スロー状態タイマー倍率
	virtual void PlaySlowTimer(float time);
	//アクターの追加
	virtual void AddActor(Actor* actor) override;
	//ナンバー表示クラスの追加
	virtual void AddNumber(Number* number);
	//デフォルトタイマー
	virtual void DefaultTime();
	//
	static void ShadowMapCallback(void* param, const GSmatrix4*, const GSmatrix4*);

public:

	//カメラの取得
	virtual Actor* GetCamera() override;
	//ライトの取得
	virtual Actor* GetLight() override;
	//フィールドの取得
	virtual Field* GetField() override;
	//アクターの検索
	virtual Actor* FindActor(const std::string& name) const override;
	//指定したタグ名を持つアクターの検索
	virtual std::vector<Actor*> FindActorWithTag(const std::string& tag) const override;

public:

	//アクター数を返す
	virtual int CountActor() const override;
	//指定したタグ名を持つアクター数を返す
	virtual int CountActorWithTag(const std::string& tag) const override;

public:

	//クリアか
	virtual bool IsClear()const override;
	//終了か
	virtual bool IsGameOver()const override;

	//コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

private:
	//ナンバークラス
	NumberManager m_Numbers;
	//sクターマネージャー
	ActorManager m_Actors;
	//ライト
	Actor* m_Light{ nullptr };
	//カメラ
	Actor* m_Camera{ nullptr };
	//フィールド
	Field* m_Field{ nullptr };

	//スロー状態にする用のタイマー
	float m_ScaleTimer{ 1.0f };

	//ゲーム終了
	bool m_ClearFrag{ false };
	bool m_GameOverFrag{ false };
};
#endif
