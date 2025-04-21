#include "AbilitySelect.h"
#include "Character/Player/PlayerState/PlayerOwnedState.h"
#include "Character/Player/Player.h"
#include "World/World.h"

AbilitySelect::AbilitySelect(){
	//ロード
	SpecialExplanationLoad();
	//必殺技の初期化
	for (int i = 0; i < Ability::TotalAbilitynum; i++) {
		m_Abilities.push_back(i);
	}
}

void AbilitySelect::Draw() const{
	GSvector2 pos{ AbilityTextNamePos.x,AbilityTextNamePos.y };
	GSrect field{ 0.0f,0.f,EditRectScale.x,EditRectScale.y };
	//背景描画
	gsDrawSprite2D(AbilityBackFrame_Texture, &AbilityBackFramePos, NULL, NULL, NULL, &BackGroundScale, NULL);
	for (int i = m_DrawFirstNum; i <= m_DrawFirstNum + FieldListNum; i++) {
		if (i != 0) {
			field = 
			{	0.0f,
				TextureOfAbilityField.y + EditRectScale.y + EditRectScale.y * m_Abilities.at(i),
				EditRectScale.x,
				TextureOfAbilityField.y + EditRectScale.y + EditRectScale.y + EditRectScale.y * m_Abilities.at(i)
			};
		}
		//アビリティ名描画
		pos.y = pos.y + EditRectScale.y + BlankScale;
		gsDrawSprite2D(Text_Texture3, &pos, &field, NULL, NULL, &TextNameScale, NULL);
	}
	//スクロールバー追加
	GScolor color{ 1.f,1.f,1.f,1.0f };
	GSrect bar_rect{ AbilityBackFramePos.x + ScrollBarRect * ScrollScale.x,AbilityBackFramePos.y,AbilityBackFramePos.x + ScrollBarRect * ScrollScale.x + AbilityScrollBarScaleRect.x,AbilityBackFramePos.y + ScrollBarRect * ScrollScale.y + AbilityScrollBarScaleRect.y};
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
	bar_rect.top + height * m_AbilityNum,
	bar_rect.right,
	bar_rect.top + height * m_AbilityNum + height };
	gsDrawRectangle2D(&bar_rect, &color);
}

void AbilitySelect::ExplanationDraw(int num) const{
	//選択アビリティ
	int ability = m_Abilities.at(num);
	//選択していないなら
	if (ability == Ability::NoneAbility)return;
	//説明ID
	GSuint n = BlowAttack_Ability_Explanation_Taxture;
	switch (ability)
	{
	case Ability::BlowAttackAbility://アビリティ１(吹き飛ばし)
		n = BlowAttack_Ability_Explanation_Taxture;
		break;
	case Ability::PushAttackAbility://アビリティ２(突き上げ攻撃)
		n = PushAttack_Ability_Explanation_Taxture;
		break;
	case Ability::AvoidAttackAbility://アビリティ３(回避斬り)
		n = AvoidAttack_Ability_Explanation_Texure;
		break;
	case Ability::RotatingAttackAbility://アビリティ４(回転斬り)
		n = RotatingAttack_Ability_Explanation_Texure;
		break;
	case Ability::InpactGroundAttackAbility://アビリティ５(衝撃波攻撃)
		n = InpactGroundAttack_Ability_Explanation_Texure;
		break;
	case Ability::SlamAttackAbility://アビリティ６(叩きつけ攻撃)
		n = SlamAttack_Ability_Explanation_Texure;
		break;
	case Ability::WildDance://アビリティ７(乱舞)
		n = WildDance_Ability_Explanation_Texure;
		break;
	case Ability::WaveWildDanceAbility://アビリティ８(波動乱舞)
		n = WaveWildDance_Ability_Explanation_Texure;
		break;
	case Ability::FangsAbility://アビリティ９(牙突)
		n = Fangs_Ability_Explanation_Texure;
		break;
	default:
		break;
	}
	//説明描画
	gsDrawSprite2D(n, &ExplanationRect, NULL, NULL, NULL, &ExplanationScale, NULL);
}

void AbilitySelect::PlayerAbilityAnim(World* world,int num){
	auto player = static_cast<Player*>(world->FindActor(st_Player));
	//選択スキル
	int ability = m_Abilities.at(num);

	GSuint a = PlayerOwnedState::Idle;

	//命名規則はあとで
	switch (ability)
	{
	case Ability::NoneAbility://アビリティ１(吹き飛ばし)
		break;
	case Ability::BlowAttackAbility://アビリティ１(吹き飛ばし)
		a = PlayerOwnedState::AbilityBlowAttack;
		break;
	case Ability::PushAttackAbility://アビリティ２(突き上げ攻撃)
		a = PlayerOwnedState::AbilityPushAttack;
		break;
	case Ability::AvoidAttackAbility://アビリティ３(回避斬り)
		a = PlayerOwnedState::AbilityAvoidAttack;
		break;
	case Ability::RotatingAttackAbility://アビリティ４(回転斬り)
		a = PlayerOwnedState::AbilityRotatingAttack;
		break;
	case Ability::InpactGroundAttackAbility://アビリティ５(衝撃波攻撃)
		a = PlayerOwnedState::AbilityInpactAttack;
		break;
	case Ability::SlamAttackAbility://アビリティ６(叩きつけ攻撃)
		a = PlayerOwnedState::AbilitySlamAttack;
		break;
	case Ability::WildDance://アビリティ７(乱舞)
		a = PlayerOwnedState::AbilityWildDance;
		break;
	case Ability::WaveWildDanceAbility://アビリティ８(波動乱舞)
		a = PlayerOwnedState::AbilityWaveWildDance_1;
		break;
	case Ability::FangsAbility://アビリティ９(牙突)
		a = PlayerOwnedState::AbilitySlashAttack;
		break;
	default:
		break;
	}

	//プレイヤーのステート変更
	if (m_IsAbilityUse)return;
	player->ChangeState(a);
	m_IsAbilityUse = true;

}

void AbilitySelect::DeleteAbility(int num){
	m_Abilities.erase(m_Abilities.begin() + num);
}

void AbilitySelect::SetAbility(int special){
	m_Abilities.push_back(special);
	std::sort(m_Abilities.begin(), m_Abilities.end());
}

void AbilitySelect::SetDrawFirst(int num){
	m_DrawFirstNum = num;
}

void AbilitySelect::SetSelectAbilityNum(int num){
	m_AbilityNum = num;
}

int AbilitySelect::SelectAbility(int num){
	if (num == 0)return Ability::NoneAbility;

	return m_Abilities.at(num);
}

int AbilitySelect::Size() const{
	return m_Abilities.size() - 1;
}

int AbilitySelect::FirstDrawNum() const{
	return m_DrawFirstNum;
}

void AbilitySelect::Initialize(){
	m_IsAbilityUse = false;
}

void AbilitySelect::SpecialExplanationLoad(){
	gsLoadTexture(BlowAttack_Ability_Explanation_Taxture,			"Assets/Texture/Ability/AbilityExplanation/blow_explanation.png");
	gsLoadTexture(PushAttack_Ability_Explanation_Taxture,			"Assets/Texture/Ability/AbilityExplanation/push_up_explanation.png");
	gsLoadTexture(AvoidAttack_Ability_Explanation_Texure,			"Assets/Texture/Ability/AbilityExplanation/avoid_attack_explanation.png");
	gsLoadTexture(RotatingAttack_Ability_Explanation_Texure,		"Assets/Texture/Ability/AbilityExplanation/rotate_attack_explanation.png");
	gsLoadTexture(InpactGroundAttack_Ability_Explanation_Texure,	"Assets/Texture/Ability/AbilityExplanation/inpact_attack_explanation.png");
	gsLoadTexture(SlamAttack_Ability_Explanation_Texure,			"Assets/Texture/Ability/AbilityExplanation/slam_attack_explanation.png");
	gsLoadTexture(WildDance_Ability_Explanation_Texure,				"Assets/Texture/Ability/AbilityExplanation/wild_dance_explanation.png");
	gsLoadTexture(WaveWildDance_Ability_Explanation_Texure,			"Assets/Texture/Ability/AbilityExplanation/wave_wild_dance_explanation.png");
	gsLoadTexture(Fangs_Ability_Explanation_Texure,					"Assets/Texture/Ability/AbilityExplanation/fangs_ability_explanation.png");

	gsLoadTexture(AbilityBackFrame_Texture,							"Assets/Texture/Ability/AbilitySlot/bg_red.png");


}
