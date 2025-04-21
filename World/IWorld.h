#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;
class Field;
class Number;

//ワールド抽象インターフェース
class IWorld {
public:
	//仮想デストラクタ
	virtual ~IWorld() = default;
	//アクター追加
	virtual void AddActor(Actor* actor) = 0;
	//ナンバー表示アクター
	virtual void AddNumber(Number* number) = 0;
	//メッセージの送信
	virtual void OnMessage(const std::string& message, void* param = nullptr) = 0;
	//スロータイマーの設定
	virtual void PlaySlowTimer(float time) = 0;
	//デフォルトタイマー
	virtual void DefaultTime() = 0;
	//クリアフラグの設定
	virtual void SetClearFrag() = 0;
	//終了フラグの設定
	virtual void SetGameOverFrag() = 0;

public:

	//アクターの検索
	virtual Actor* FindActor(const std::string& name) const = 0;
	//指定したタグ名を持つアクターの検索
	virtual std::vector<Actor*>FindActorWithTag(const std::string& tag) const = 0;
	//フィールドの取得
	virtual Field* GetField() = 0;
	//カメラの取得
	virtual Actor* GetCamera() = 0;
	//ライトの取得
	virtual Actor* GetLight() = 0;

public:

	//アクター数を返す
	virtual int CountActor() const = 0;
	//指定したタグ名を持つアクター数を返す
	virtual int CountActorWithTag(const std::string& tag) const = 0;

public:

	//ゲームクリアか
	virtual bool IsClear()const  = 0;
	//終了か
	virtual bool IsGameOver()const = 0;

};

#endif
