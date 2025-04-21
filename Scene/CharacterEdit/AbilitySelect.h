#ifndef ABILITY_SELECT_H_
#define ABILITY_SELECT_H_

#include "Character/Player/Ability/AbilityType.h"
#include "Animation/AnimatedMesh.h"

class World;

class AbilitySelect {
public:

	//コンストラクタ
	AbilitySelect();
	//描画
	void Draw()const;
	//説明
	void ExplanationDraw(int num)const;
	//アニメーション変更
	void PlayerAbilityAnim(World* world, int num);
	//必殺技削除
	void DeleteAbility(int num);
	//アビリティ追加
	void SetAbility(int special);
	//最初の位置の番号
	void SetDrawFirst(int num);
	//選択しているアビリティの番号
	void SetSelectAbilityNum(int num);
	//アビリティ使用初期化
	void Initialize();

public:

	//必殺技の選択
	int SelectAbility(int num);
	//サイズ設定
	int Size()const;
	//最初に描画する位置の番号
	int FirstDrawNum()const;

private:

	//必殺技説明のロード
	void SpecialExplanationLoad();

private:
	//アビリティ
	std::vector<int> m_Abilities;

	//アビリティ使用したか
	bool m_IsAbilityUse{ false };

	//最初の位置
	int m_DrawFirstNum{ 0 };

	//アビリティナンバー
	int m_AbilityNum{ 0 };
};

#endif