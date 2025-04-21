#include "AbilityEdit.h"

AbilityEdit::AbilityEdit(){
	//ロード
	TextureLoad();
}

void AbilityEdit::Update(float delta_time){
	if (m_IsSelect) {
		SelectAbilityUpdate(delta_time);
	}
	else {
		SetAbilityUpdate(delta_time);
	}
}

void AbilityEdit::PlayerAbilityAnim(World* world){
	m_Abilities.PlayerAbilityAnim(world, m_SelectCount);
}

void AbilityEdit::Draw() const{
	if (m_IsSelect) {
		//位置の計算
		int select_num = m_SelectCount - m_Abilities.FirstDrawNum();
		//選択肢の選択
		m_Abilities.Draw();
		//説明
		m_Abilities.ExplanationDraw(m_SelectCount);
		//背景描画
		GSvector2 pos{ AbilityFramePos.x , AbilityFramePos.y + (EditRectScale.y + BlankScale) * select_num };
		//フレーム描画
		gsDrawSprite2D(Select_Frame, &pos, NULL, NULL, NULL, &FrameScale, NULL);
	}
	//リターン描画
	gsDrawSprite2D(Return_Texture, &ReturnPos, NULL, NULL, NULL, NULL, NULL);

	// 選択
	GSrect field{ 
		EditRectPos.x,
		EditRectPos.y + (EditRectScale.y + AbilityBlankScale) * m_SetAbilityCount,
		EditRectPos.x + FrameRectPos.x,
		EditRectPos.y + FrameRectPos.y + (EditRectScale.y + AbilityBlankScale) * m_SetAbilityCount
	};
	gsDrawRectangle2D(&field, &SelectColor);

	//スロット・アイコン描画
	for (int i = 0; i < static_cast<int>(m_SetAbilities.size()); i++) {
		SetAbilityDraw(i);
	}
	//選択
	if (m_IsSelect) gsDrawRectangle2D(&field, &SelectColor);

}

void AbilityEdit::DrawLogo() const{
	//ボックス
	GSvector2 pos = { BoxRectScale.x,BoxRectScale.y };
	for (int i = 0; i < static_cast<int>(m_SetAbilities.size()); i++) {
		gsDrawSprite2D(Frame_Texture, &pos, NULL, NULL, NULL, &BoxScale, NULL);
		pos.y += SlotPos.y * 2;
	}
}

void AbilityEdit::Save(){
	m_Save.SaveAbility("Data/ability_data.txt", m_SetAbilities);
}

bool AbilityEdit::IsSelect() const{
	return m_IsSelect;
}

float AbilityEdit::IsSelectCount() const{
	return m_SelectCount;
}

void AbilityEdit::SetAbilityUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_SetAbilityCount++;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_SetAbilityCount--;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsSelect = true;
	}
	
	CycleArray(m_SetAbilityCount, 0, m_SetAbilities.size() - 1);
}

void AbilityEdit::SelectAbilityUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		//削除
		if (m_SelectCount == 0){
			if (m_SetAbilities.at(m_SetAbilityCount) == 0)return;
			DeleteAbilityArray();
			return;
		}
		gsPlaySE(Click_SE);
		//入れ替え
		SwapAbilityArray();
		//カウントを0にする
		m_SelectCount = 0;
		//選択肢の初期描画位置を設定
		m_Abilities.SetDrawFirst(m_SelectCount);
		//選択状態解除
		m_IsSelect = false;
		return;
	}
	//ショートカット削除
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Delete)) {
		if (m_SetAbilities.at(m_SetAbilityCount) == 0)return;
		DeleteAbilityArray();
		return;
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		m_Abilities.Initialize();
		gsPlaySE(Change_SE);
		m_SelectCount--;
		//下にいきすぎてしまうのを制限
		m_SelectCount = CLAMP(m_SelectCount, 0, m_Abilities.Size());
		m_Abilities.SetDrawFirst(std::min(m_Abilities.FirstDrawNum(), m_SelectCount));
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		m_Abilities.Initialize();
		gsPlaySE(Change_SE);
		m_SelectCount++;
		//上に行くのを制限する
		int num = m_SelectCount - FieldListNum;
		num = CLAMP(num, 0, m_Abilities.Size() - FieldListNum);
		m_Abilities.SetDrawFirst(std::max(m_Abilities.FirstDrawNum(), num));
	}
	//Rangeオーバーになってしまうので制限
	m_SelectCount = CLAMP(m_SelectCount, 0, m_Abilities.Size());
	m_Abilities.SetSelectAbilityNum(m_SelectCount);

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Return)) {
		m_IsSelect = false;
	}
}

void AbilityEdit::SetAbilityDraw(int num) const{

	GSvector2 draw_pos{ SlotPos.x, SlotPos.y + (SlotPos.y + SlotPos.y) * num };

	//スロット作成
	gsDrawSprite2D(AbilityFrame_Texture, &draw_pos, NULL, NULL, NULL, &SlotScale, NULL);
	draw_pos.x += AbilityPos.x;
	draw_pos.y += AbilityPos.y;

	//スキル描画
	int ability = m_SetAbilities.at(num);
	if (ability == Ability::NoneAbility)return;
	GSuint a = BlowAttack_Ability_Taxture;

	switch (ability) {
	case Ability::BlowAttackAbility:			//付き飛ばし
		a = BlowAttack_Ability_Taxture;
		break;
	case Ability::PushAttackAbility:			//突き上げ
		a = PushAttack_Ability_Taxture;
		break;
	case Ability::AvoidAttackAbility:			//回避攻撃
		a = AvoidAttack_Ability_Taxture;	
		break;
	case Ability::RotatingAttackAbility:		//回転斬り
		a = RotatingAttack_Ability_Taxture;
		break;
	case Ability::InpactGroundAttackAbility:	//衝撃攻撃
		a = InpactGroundAttack_Ability_Taxture;
		break;
	case Ability::SlamAttackAbility:			//空中に飛ばす
		a = SlamAttack_Ability_Taxture;
		break;
	case Ability::WildDance:					//乱舞
		a = WildDance_Taxture;
		break;
	case Ability::WaveWildDanceAbility:			//波動乱舞
		a = WaveWildDance_Ability_Taxture;
		break;
	case Ability::FangsAbility:					//牙突
		a = Fangs_Ability_Taxture;
		break;
	default:
		break;
	}
	gsDrawSprite2D(a, &draw_pos, NULL, NULL, NULL, &TextScale, NULL);

}

void AbilityEdit::DeleteAbilityArray(){
	//スキルをセットする
	m_Abilities.SetAbility(m_SetAbilities.at(m_SetAbilityCount));
	//スキル消去
	m_SetAbilities.at(m_SetAbilityCount) = Ability::NoneAbility;
}

void AbilityEdit::SwapAbilityArray(){
	//保管しておく
	int strage = m_SetAbilities.at(m_SetAbilityCount);
	//スキルを上書き
	m_SetAbilities.at(m_SetAbilityCount) = m_Abilities.SelectAbility(m_SelectCount);
	//スキル削除
	m_Abilities.DeleteAbility(m_SelectCount);
	//NONEではなかったら格納
	if (strage != Ability::NoneAbility)m_Abilities.SetAbility(strage);
}

void AbilityEdit::CycleArray(int& num, int min, int max) {
	if (num > max) {
		num = 0;
		return;
	}
	if (num < min) {
		num = max;
		return;
	}
}

void AbilityEdit::TextureLoad(){
	gsLoadTexture(BlowAttack_Ability_Taxture,			"Assets/Texture/Ability/blow_attack_bg.png");
	gsLoadTexture(PushAttack_Ability_Taxture,			"Assets/Texture/Ability/push_attack_bg.png");
	gsLoadTexture(AvoidAttack_Ability_Taxture,			"Assets/Texture/Ability/avoid_attack_bg.png");
	gsLoadTexture(RotatingAttack_Ability_Taxture,		"Assets/Texture/Ability/rotating_attack_bg.png");
	gsLoadTexture(InpactGroundAttack_Ability_Taxture,	"Assets/Texture/Ability/inpact_attack_bg.png");
	gsLoadTexture(SlamAttack_Ability_Taxture,			"Assets/Texture/Ability/slam_attack_bg.png");
	gsLoadTexture(WildDance_Taxture,					"Assets/Texture/Ability/wild_dance_bg.png");
	gsLoadTexture(WaveWildDance_Ability_Taxture,		"Assets/Texture/Ability/wave_wild_dance_bg.png");
	gsLoadTexture(Fangs_Ability_Taxture,				"Assets/Texture/Ability/fangs_attack_bg.png");
	gsLoadTexture(Select_Frame,							"Assets/Texture/Ability/AbilitySlot/ability_bar_slot.png");
	gsLoadTexture(AbilityFrame_Texture,					"Assets/Texture/Ability/AbilitySlot/ability_slot.png");
}
