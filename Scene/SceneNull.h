#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

//
class SceneNull : public IScene {
public:
	//開始
	virtual void Start() override{}
	//更新
	virtual void Update(float delta_time) override{}
	//描画
	virtual void Draw() const override{}
	//終了するか
	virtual bool IsEnd() const override { return false; }
	//シーン削除するか
	virtual bool StackClear()const override { return false; }
	//フラグの初期化
	virtual void ResetFrag()override{}
	//次のシーンを返す
	virtual int Next() const override { return -1; }
	//終了
	virtual void End() override{}
	//ゲーム終了
	virtual bool IsGameEnd()const override { return false; }
};

#endif
