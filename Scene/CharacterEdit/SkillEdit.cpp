#include "SkillEdit.h"

SkillEdit::SkillEdit(){
	//ロード
	TextureLoad();
}

void SkillEdit::Update(float delta_time){
	if (m_IsSelect) {
		ChoiceItemUpdate(delta_time);
	}
	else {
		SetSkillUpdate(delta_time);
	}
}

void SkillEdit::SkillEffect(World* world) {
	m_Skills.SetSkillEffect(world, m_ChoicesCount);
}

void SkillEdit::Draw() const{
	if (m_IsSelect) {
		//最初の位置計算
		int select_num = m_ChoicesCount - m_Skills.FirstDrawNum();
		//スキル描画
		m_Skills.Draw();
		//説明描画
		m_Skills.Explanation(m_ChoicesCount);
		//背景描画
		GSvector2 pos{ SkillFramePos.x , SkillFramePos.y + (EditRectScale.y + BlankScale) * select_num };
		//フレーム描画
		gsDrawSprite2D(Select_Frame, &pos, NULL, NULL, NULL, &FrameScale, NULL);
	}
	//リターン位置
	gsDrawSprite2D(Return_Texture, &ReturnPos, NULL, NULL, NULL, NULL, NULL);
	// 選択している場所を計算
	GSrect field{
		EditRectPos.x,
		EditRectPos.y + (EditRectScale.y + SkillBlankScale) * m_SetSkillCount,
		EditRectPos.x + FrameRectPos.x,
		EditRectPos.y + FrameRectPos.y + (EditRectScale.y + SkillBlankScale) * m_SetSkillCount
	};
	gsDrawRectangle2D(&field, &SelectColor);

	//スキルスロット描画
	for (int i = 0; i < static_cast<int>(m_SetSkill.size()); i++) {
		SetSkillDraw(i);
	}
	
	if (m_IsSelect)gsDrawRectangle2D(&field, &SelectColor);
}

void SkillEdit::DrawLogo() const{
	GSvector2 pos = { BoxRectScale.x,BoxRectScale.y };
	//ボックスの描画
	for (int i = 0; i < static_cast<int>(m_SetSkill.size()); i++) {
		gsDrawSprite2D(Frame_Texture, &pos, NULL, NULL, NULL, &BoxScale, NULL);
		pos.y += SlotPos.y;
	}
}

void SkillEdit::Save(){
	m_Save.SaveItem("Data/skill_data.txt", m_SetSkill);
}

//どこのボックスに選択するか
void SkillEdit::SetSkillUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_SetSkillCount--;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_SetSkillCount++;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsSelect = true;
	}
	CycleArray(m_SetSkillCount, 0, m_SetSkill.size() - 1);
}

void SkillEdit::ChoiceItemUpdate(float delta_time){

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {

		if (m_ChoicesCount == 0) {
			//スキルNoneだったら何もしない
			if (m_SetSkill.at(m_SetSkillCount) == 0)return;
			//削除
			DeleteItemArray();
			return;
		}
		gsPlaySE(Click_SE);
		//スキル入れ替え
		SwapItemArray();
		//カウント初期化
		m_ChoicesCount = 0;
		//初期位置を設定
		m_Skills.SetDrawFirstNum(m_ChoicesCount);
		//選択解除
		m_IsSelect = false;
		return;
		
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		m_Skills.Initialize();
		gsPlaySE(Change_SE);
		//上に行くのを制限
		m_ChoicesCount--;
		m_ChoicesCount = CLAMP(m_ChoicesCount, 0, m_Skills.Size());
		m_Skills.SetDrawFirstNum(std::min(m_Skills.FirstDrawNum(), m_ChoicesCount));
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		m_Skills.Initialize();
		gsPlaySE(Change_SE);
		//下に行くのを制限
		m_ChoicesCount++;
		int num = m_ChoicesCount - FieldListNum;
		num = CLAMP(num, 0, m_Skills.Size() - FieldListNum);
		m_Skills.SetDrawFirstNum(std::max(m_Skills.FirstDrawNum(), num));
	}

	//Rangeオーバーの制限
	m_ChoicesCount = CLAMP(m_ChoicesCount, 0, m_Skills.Size());
	m_Skills.SetSelectSkillNum(m_ChoicesCount);

	//Aボタンで解除
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Return)) {
		gsPlaySE(Click_SE);
		m_IsSelect = false;
	}
}

void SkillEdit::SetSkillDraw(int num)const{
	GSvector2 draw_pos{ SlotPos.x, SlotPos.y + SlotPos.y * num };
	//スロット作成
	gsDrawSprite2D(SkillFrame_Texture, &draw_pos, NULL, NULL, NULL, &SlotScale, NULL);
	draw_pos.x += SkillPos.x;
	draw_pos.y += SkillPos.y;

	//スキル描画
	int skill = m_SetSkill.at(num);
	if (skill == SkillType::NoneSkill)return;
	GSuint s = HealthUpAndHeal_Skill_Texture;

	switch (skill)
	{
	case HealthUpAndHealSkill:
		s = HealthUpAndHeal_Skill_Texture;
		break;
	case AttackPowerUpSkill:
		s = AttackPowerUp_Skill_Texture;
		break;
	case AttackPowerLergeUpSkill:
		s = AttackPowerLergeUp_Skill_Texture;
		break;
	case HealthHealSeedUpSkill:
		s = HealthHealSeedUp_Skill_Texture;
		break;
	case AvoidPerformanceUpSkill:
		s = AvoidPerformanceUp_Skill_Texture;
		break;
	case AvoidDistanceUpSkill:
		s = AvoidDistanceUp_Skill_Texture;
		break;
	case JustAvoidSlowSkill:
		s = JustAvoidSlow_Skill_Texture;
		break;
	case DivineProtectionSkill:
		s = DivineProtection_Skill_Texture;
		break;
	case FullChargeSkill:
		s = FullCharge_Skill_Texture;
		break;
	case CrisisChargeSkill:
		s = CrisisCharge_Skill_Texture;
		break;
	case SuperArmorSkill:
		s = SuperArmor_Skill_Texture;
		break;
	default:
		break;
	}
	gsDrawSprite2D(s, &draw_pos, NULL, NULL, NULL, &TextScale, NULL);
}

void SkillEdit::DeleteItemArray(){
	//現在セットされているスキルを追加
	m_Skills.SetSkill(m_SetSkill.at(m_SetSkillCount));
	//スキル削除
	m_SetSkill.at(m_SetSkillCount) = SkillType::NoneSkill;
}

void SkillEdit::SwapItemArray(){
	//スキルの保存
	int storage = m_SetSkill.at(m_SetSkillCount);
	//スキル上書き
	m_SetSkill.at(m_SetSkillCount) = m_Skills.SelectSkill(m_ChoicesCount);
	//選択されたものは一覧から削除
	m_Skills.DeleteSkill(m_ChoicesCount);
	//Noneではなかったらスキルを格納
	if (storage != SkillType::NoneSkill)m_Skills.SetSkill(storage);
}

void SkillEdit::CycleArray(int& num, int min, int max){
	if (num > max) {
		num = 0;
		return;
	}
	if (num < min) {
		num = max;
		return;
	}
}
void SkillEdit::TextureLoad()
{
	gsLoadTexture(SkillFrame_Texture,				"Assets/Texture/Skill/SkillSlot/skill_slot.png");

	gsLoadTexture(HealthUpAndHeal_Skill_Texture,	"Assets/Texture/Skill/heal_skill.png");
	gsLoadTexture(AttackPowerUp_Skill_Texture,		"Assets/Texture/Skill/attack_power_up_skill.png");
	gsLoadTexture(AttackPowerLergeUp_Skill_Texture, "Assets/Texture/Skill/attack_power_lerge_up_skill.png");
	gsLoadTexture(HealthHealSeedUp_Skill_Texture,	"Assets/Texture/Skill/heal_seed_up_skill.png");
	gsLoadTexture(AvoidPerformanceUp_Skill_Texture, "Assets/Texture/Skill/avoid_performance_up_skill.png");
	gsLoadTexture(AvoidDistanceUp_Skill_Texture,	"Assets/Texture/Skill/avoid_distance_skill.png");
	gsLoadTexture(JustAvoidSlow_Skill_Texture,		"Assets/Texture/Skill/just_avoid_slow_skill.png");
	gsLoadTexture(DivineProtection_Skill_Texture,	"Assets/Texture/Skill/divine_protection_skill.png");
	gsLoadTexture(FullCharge_Skill_Texture,			"Assets/Texture/Skill/full_charge_skill.png");
	gsLoadTexture(CrisisCharge_Skill_Texture,		"Assets/Texture/Skill/crisis_scharge_skill.png");
	gsLoadTexture(SuperArmor_Skill_Texture,			"Assets/Texture/Skill/super_armor_skill.png");


}