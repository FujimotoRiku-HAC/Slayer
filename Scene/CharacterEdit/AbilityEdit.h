#ifndef SPECIAL_EDIT_H_
#define SPECIAL_EDIT_H_

#include "AbilitySelect.h"
#include "Character/Player/SaveData.h"

class AbilityEdit {
public:

	//コンストラクタ
	AbilityEdit();
	//更新
	void Update(float delta_time);
	//プレイヤーアニメーション
	void PlayerAbilityAnim(World* world);
	//描画
	void Draw()const;
	//ロゴを描画
	void DrawLogo()const;
	//セーブ
	void Save();

public:

	//選んだか
	bool IsSelect()const;

public:

	//カウント取得
	float IsSelectCount()const;

private:

	//設定した必殺技の更新
	void SetAbilityUpdate(float delta_time);
	//必殺技選択の更新
	void SelectAbilityUpdate(float delta_time);
	//設定した必殺技の描画
	void SetAbilityDraw(int num)const;
	//必殺技の削除
	void DeleteAbilityArray();
	//入れ替え
	void SwapAbilityArray();
	// numをminからmaxの間を循環させる
	void CycleArray(int& num, int min, int max);
	//テクスチャをロード
	void TextureLoad();

private:
	//アビリティセレクト
	AbilitySelect m_Abilities;
	//セーブ
	SaveData m_Save;
	//アビリティセット
	std::array<int, AbilityNum> m_SetAbilities{ 0,0 };
	//アビリティカウント
	int m_SetAbilityCount{ 0 };
	//セレクトカウント
	int m_SelectCount{ 0 };
	//選んだか
	bool m_IsSelect{ false };

};

#endif