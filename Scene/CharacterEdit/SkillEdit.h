#ifndef SKILL_EDIT_H_
#define SKILL_EDIT_H_

#include "SkillSelect.h"
#include "Character/Player/SaveData.h"
#include "World/World.h"

class SkillEdit {
public:

	//コンストラクタ
	SkillEdit();
	//更新
	void Update(float delta_time);
	//プレイヤーアニメーション
	void SkillEffect(World* world);
	//描画
	void Draw()const;
	//ロゴ描画
	void DrawLogo()const;
	//セーブ
	void Save();

private:

	//セットされたアイテムを更新
	void SetSkillUpdate(float delta_time);
	//スキル選択肢の更新
	void ChoiceItemUpdate(float delta_time);
	//セットされたスキルの描画
	void SetSkillDraw(int num)const;
	//セットスキルの消去
	void DeleteItemArray();
	//スキル入れ替え
	void SwapItemArray();
	//numをminからmaxの間で循環
	void CycleArray(int& num, int min, int max);
	//テクスチャロード
	void TextureLoad();

private:

	//スキル
	SkillSelect m_Skills;
	//セーブ
	SaveData m_Save;
	//ワールド
	World m_World;
	//アイテム設定
	std::array<int, ItemNum>m_SetSkill{ 0,0,0 };

	//セットスキルカウント
	int m_SetSkillCount{ 0 };
	//選んだ数
	int m_ChoicesCount{ 0 };
	//選んだか
	bool m_IsSelect{ false };

};

#endif