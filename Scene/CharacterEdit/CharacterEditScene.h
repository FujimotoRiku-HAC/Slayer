#ifndef CHEARACTER_EDIT_SCENE_H_
#define CHEARACTER_EDIT_SCENE_H_

#include "Scene/IScene.h"
#include "Scene/Fade.h"
#include "World/World.h"
#include "Scene/CharacterEdit/AbilityEdit.h"
#include "Scene/CharacterEdit/SkillEdit.h"
#include "Animation/AnimatedMesh.h"


class CharacterEditScene : public IScene {
public:

	//開始
	virtual void Start() override;
	//更新
	virtual void Update(float delta_time) override;
	//描画
	virtual void Draw() const override;
	//終了しているか
	virtual bool IsEnd() const override;
	//シーン削除
	bool StackClear()const override;
	//フラグ初期化
	void ResetFrag() override;
	//次のシーンを返す
	virtual int Next()const override;
	//終了
	virtual void End() override;
	//ゲーム終了か
	virtual bool IsGameEnd()const override;

private:

	//スタート更新
	void StartUpdate(float delta_time);
	//アビリティ更新
	void AbilityUpdate(float delta_time);
	//スキル更新
	void SkillUpdate(float delta_time);
	//戻る更新
	void ReturnUpdate(float delta_time);
	//プレイヤーの行動
	void PlayerAction();

private:
	enum Text{
		GameStart,
		Ability,
		Skill,
		Return
	};
private:

	//メッシュ
	AnimatedMesh m_Mesh{NULL,NULL};
	//トランスフォーム
	GStransform m_Transform;
	//テキスト
	Text m_Text;
	//フェード
	Fade m_Fade;
	//ワールド
	World m_World;
	//アビリティ
	AbilityEdit m_Ability;
	//スキル
	SkillEdit m_Skill;

	//終了処理
	bool m_IsEnd{ false };
	bool m_IsSelect{ false };
	bool m_IsClear{ false };
	int m_NextScene{ -1 };

};

#endif