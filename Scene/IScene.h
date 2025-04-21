#ifndef ISCENE_H_
#define ISCENE_H_

//シーン抽象インターフェース
class IScene {
public:
	//仮想デストラクタ
	virtual ~IScene() = default;
	//開始
	virtual void Start() = 0;
	//更新
	virtual void Update(float delta_time) = 0;
	//描画
	virtual void Draw() const = 0;
	//終了しているか
	virtual bool IsEnd() const = 0;
	//シーンの削除
	virtual bool StackClear()const = 0;
	//
	virtual void ResetFrag() = 0;
	//次のシーン名を残す
	virtual int Next() const = 0;
	//終了
	virtual void End() = 0;
	//ゲーム終了
	virtual bool IsGameEnd()const = 0;
};

#endif
