#include "SkillSelect.h"
#include "Character/Player/Player.h"
#include "World/World.h"

SkillSelect::SkillSelect(){
	//ロード
	SkillLoad();
	//すべてのアイテムを追加
	for (int i = 0; i < SkillType::TotalSkillNum; i++) {
		m_Skills.push_back(i);
	}
}

void SkillSelect::Draw() const{
	GSvector2 pos{ SkillTextNamePos.x,SkillTextNamePos.y };
	GSrect field{ 0.f,0.f,EditRectScale.x,EditRectScale.y };
	//背景描画
	gsDrawSprite2D(SkillBackFrame_Texture, &SkillBackFramePos, NULL, NULL, NULL, &BackGroundScale, NULL);
	for (int i = m_DrawFirstNum; i <= m_DrawFirstNum + FieldListNum; i++) {
		if (i != 0) {
			field = 
			{	0.0f,
				TextureOfSkillField.y + EditRectScale.y * m_Skills.at(i),
				TextureOfSkillField.x,
				TextureOfSkillField.y + EditRectScale.y + EditRectScale.y * m_Skills.at(i)
			};
		}
			//スキル名描画
			pos.y = pos.y + EditRectScale.y + BlankScale;
			gsDrawSprite2D(Text_Texture3, &pos, &field, NULL, NULL, &TextNameScale, NULL);
	}

	GScolor color{ 1.f,1.f,1.f,1.f };
	//スクロールバー追加
	GSrect bar_rect{ SkillBackFramePos.x + ScrollBarRect * ScrollScale.x,SkillBackFramePos.y,SkillBackFramePos.x + ScrollBarRect * ScrollScale.x + SkillScrollBarScaleRect.x,SkillBackFramePos.y + ScrollBarRect * ScrollScale.y + SkillScrollBarScaleRect.y };
	gsDrawRectangle2D(&bar_rect, &color);
	color = { 0.f,0.f,0.f,1.0f };
	bar_rect.top += 1.f;
	bar_rect.bottom -= 1.f;
	bar_rect.left += 1.f;
	bar_rect.right -= 1.f;
	gsDrawRectangle2D(&bar_rect, &color);
	color = { 1.f,1.f,1.f,0.5f };
	float height = { (bar_rect.bottom - bar_rect.top) / (Size() + 1) };
	bar_rect = { bar_rect.left,
	bar_rect.top + height * m_SkillNum,
	bar_rect.right,
	bar_rect.top + height * m_SkillNum + height };
	gsDrawRectangle2D(&bar_rect, &color);
}

void SkillSelect::Explanation(int num) const{
	//選択スキル
	int skill = m_Skills.at(num);
	//選択していないなら
	if (skill == SkillType::NoneSkill)return;
	//説明ID
	GSuint e = HealthUpAndHeal_Skill_Explanation_Texture;
	//命名規則はあとで
	switch (skill)
	{
	case SkillType::HealthUpAndHealSkill:
		e = HealthUpAndHeal_Skill_Explanation_Texture;
		break;
	case SkillType::AttackPowerUpSkill:
		e = AttackPowerUp_Skill_Explanation_Texture;
		break;
	case SkillType::AttackPowerLergeUpSkill:
		e = AttackPowerLergeUp_Skill_Explanation_Texture;
		break;
	case SkillType::HealthHealSeedUpSkill:
		e = HealthHealSeedUp_Skill_Explanation_Texture;
		break;
	case SkillType::AvoidPerformanceUpSkill:
		e = AvoidPerformanceUp_Skill_Explanation_Texture;
		break;
	case SkillType::AvoidDistanceUpSkill:
		e = AvoidDistanceUp_Skill_Explanation_Texture;
		break;
	case SkillType::JustAvoidSlowSkill:
		e = JustAvoidSlow_Skill_Explanation_Texture;
		break;
	case SkillType::DivineProtectionSkill:
		e = DivineProtection_Skill_Explanation_Texture;
		break;
	case SkillType::FullChargeSkill:
		e = FullCharge_Skill_Explanation_Texture;
		break;
	case SkillType::CrisisChargeSkill:
		e = CrisisCharge_Skill_Explanation_Texture;
		break;
	case SkillType::SuperArmorSkill:
		e = SuperArmor_Skill_Explanation_Texture;
		break;
	default:
		break;
	}
	//描画位置
	gsDrawSprite2D(e, &ExplanationRect, NULL, NULL, NULL, &ExplanationScale, NULL);
}

void SkillSelect::SetSkillEffect(World* world,int num){
	auto player = static_cast<Player*>(world->FindActor(st_Player));

	//選択スキル
	int skill = m_Skills.at(num);
	//選択していないなら
	if (skill == SkillType::NoneSkill)return;
	//説明ID
	GSuint e = Effect_HealthUpHealBuff;
	//命名規則はあとで
	switch (skill)
	{
	case SkillType::HealthUpAndHealSkill:
		e = Effect_HealthUpHealBuff;
		break;
	case SkillType::AttackPowerUpSkill:
		e = Effect_AttackPowerUpBuff;
		break;
	case SkillType::AttackPowerLergeUpSkill:
		e = Effect_AttackPowerLergeUpBuff;
		break;
	case SkillType::HealthHealSeedUpSkill:
		e = Effect_HealSeedBuff;
		break;
	case SkillType::AvoidPerformanceUpSkill:
		e = Effect_AvoidPerformanceBuff;
		break;
	case SkillType::AvoidDistanceUpSkill:
		e = Effect_AvoidDistanceBuff;
		break;
	case SkillType::JustAvoidSlowSkill:
		e = Effect_JustAvoidSlowBuff;
		break;
	case SkillType::DivineProtectionSkill:
		e = Effect_DivineProtectionBuff;
		break;
	case SkillType::FullChargeSkill:
		e = Effect_FullChargeBuff;
		break;
	case SkillType::CrisisChargeSkill:
		e = Effect_CrisisChrageBuff;
		break;
	case SkillType::SuperArmorSkill:
		e = Effect_SuperArmorBuff;
		break;
	default:
		break;
	}

	if (m_SkillUse)return;
	player->SetEffect(e, true);
	m_SkillUse = true;
}

void SkillSelect::DeleteSkill(int item){
	m_Skills.erase(m_Skills.begin() + item);
}

void SkillSelect::SetSkill(int item){
	m_Skills.push_back(item);
	std::sort(m_Skills.begin(), m_Skills.end());
}

void SkillSelect::SetDrawFirstNum(int num){
	m_DrawFirstNum = num;
}

void SkillSelect::SetSelectSkillNum(int num)
{
	m_SkillNum = num;
}

void SkillSelect::Initialize(){
	m_SkillUse = false;
}

int SkillSelect::SelectSkill(int num){
	if(num == 0)return SkillType::NoneSkill;

	return m_Skills.at(num);
}

int SkillSelect::Size() const{
	return m_Skills.size() - 1;
}

int SkillSelect::FirstDrawNum() const{
	return m_DrawFirstNum;
}

void SkillSelect::SkillLoad(){
	gsLoadTexture(SkillBackFrame_Texture,						"Assets/Texture/Skill/SkillSlot/bg_green.png");
	gsLoadTexture(HealthUpAndHeal_Skill_Explanation_Texture,	"Assets/Texture/Skill/Explanation/health_up_explanation.png");
	gsLoadTexture(AttackPowerUp_Skill_Explanation_Texture,		"Assets/Texture/Skill/Explanation/attack_power_up_explanation.png");
	gsLoadTexture(AttackPowerLergeUp_Skill_Explanation_Texture, "Assets/Texture/Skill/Explanation/attack_power_lerge_up_explanation.png");
	gsLoadTexture(HealthHealSeedUp_Skill_Explanation_Texture,	"Assets/Texture/Skill/Explanation/heal_seed_explanation.png");
	gsLoadTexture(AvoidPerformanceUp_Skill_Explanation_Texture, "Assets/Texture/Skill/Explanation/avoid_peformance_explanation.png");
	gsLoadTexture(AvoidDistanceUp_Skill_Explanation_Texture,	"Assets/Texture/Skill/Explanation/avoid_distance_explanation.png");
	gsLoadTexture(JustAvoidSlow_Skill_Explanation_Texture,		"Assets/Texture/Skill/Explanation/just_avoid_slow_explanation.png");
	gsLoadTexture(DivineProtection_Skill_Explanation_Texture,	"Assets/Texture/Skill/Explanation/divine_protection_explanation.png");
	gsLoadTexture(FullCharge_Skill_Explanation_Texture,			"Assets/Texture/Skill/Explanation/full_charge_explanation.png");
	gsLoadTexture(CrisisCharge_Skill_Explanation_Texture,		"Assets/Texture/Skill/Explanation/crisis_charge_explanation.png");
	gsLoadTexture(SuperArmor_Skill_Explanation_Texture,			"Assets/Texture/Skill/Explanation/super_armor_explanation.png");

}
