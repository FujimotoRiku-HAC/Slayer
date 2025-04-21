#ifndef SKILL_SELECT_H_
#define SKILL_SELECT_H_

#include "Character/Player/Skill/SkillType.h"

class World;

class SkillSelect {
public:
	//コンストラクタ
	SkillSelect();
	//描画
	void Draw()const;
	//説明
	void Explanation(int num)const;
	//スキル選択時にエフェクト設置
	void SetSkillEffect(World* world,int num);
	//スキル削除
	void DeleteSkill(int skill);
	//アイテムセット
	void SetSkill(int skill);
	//最初に描画する位置
	void SetDrawFirstNum(int num);
	//スキルの番号
	void SetSelectSkillNum(int num);
	//
	void Initialize();

public:

	//選択中のアイテム
	int SelectSkill(int num);
	//サイズの取得
	int Size()const;
	//最初に描画する位置の番号
	int FirstDrawNum()const;

private:

	//ロード
	void SkillLoad();

private:
	//スキル
	std::vector<int> m_Skills;
	//最初の位置
	int m_DrawFirstNum{ 0 };
	//スキルの番号
	int m_SkillNum{ 0 };

	bool m_SkillUse{ false };
};

#endif