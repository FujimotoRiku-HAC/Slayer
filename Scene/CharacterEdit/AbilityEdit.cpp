#include "AbilityEdit.h"

AbilityEdit::AbilityEdit(){
	//���[�h
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
		//�ʒu�̌v�Z
		int select_num = m_SelectCount - m_Abilities.FirstDrawNum();
		//�I�����̑I��
		m_Abilities.Draw();
		//����
		m_Abilities.ExplanationDraw(m_SelectCount);
		//�w�i�`��
		GSvector2 pos{ AbilityFramePos.x , AbilityFramePos.y + (EditRectScale.y + BlankScale) * select_num };
		//�t���[���`��
		gsDrawSprite2D(Select_Frame, &pos, NULL, NULL, NULL, &FrameScale, NULL);
	}
	//���^�[���`��
	gsDrawSprite2D(Return_Texture, &ReturnPos, NULL, NULL, NULL, NULL, NULL);

	// �I��
	GSrect field{ 
		EditRectPos.x,
		EditRectPos.y + (EditRectScale.y + AbilityBlankScale) * m_SetAbilityCount,
		EditRectPos.x + FrameRectPos.x,
		EditRectPos.y + FrameRectPos.y + (EditRectScale.y + AbilityBlankScale) * m_SetAbilityCount
	};
	gsDrawRectangle2D(&field, &SelectColor);

	//�X���b�g�E�A�C�R���`��
	for (int i = 0; i < static_cast<int>(m_SetAbilities.size()); i++) {
		SetAbilityDraw(i);
	}
	//�I��
	if (m_IsSelect) gsDrawRectangle2D(&field, &SelectColor);

}

void AbilityEdit::DrawLogo() const{
	//�{�b�N�X
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
		//�폜
		if (m_SelectCount == 0){
			if (m_SetAbilities.at(m_SetAbilityCount) == 0)return;
			DeleteAbilityArray();
			return;
		}
		gsPlaySE(Click_SE);
		//����ւ�
		SwapAbilityArray();
		//�J�E���g��0�ɂ���
		m_SelectCount = 0;
		//�I�����̏����`��ʒu��ݒ�
		m_Abilities.SetDrawFirst(m_SelectCount);
		//�I����ԉ���
		m_IsSelect = false;
		return;
	}
	//�V���[�g�J�b�g�폜
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Delete)) {
		if (m_SetAbilities.at(m_SetAbilityCount) == 0)return;
		DeleteAbilityArray();
		return;
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		m_Abilities.Initialize();
		gsPlaySE(Change_SE);
		m_SelectCount--;
		//���ɂ��������Ă��܂��̂𐧌�
		m_SelectCount = CLAMP(m_SelectCount, 0, m_Abilities.Size());
		m_Abilities.SetDrawFirst(std::min(m_Abilities.FirstDrawNum(), m_SelectCount));
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		m_Abilities.Initialize();
		gsPlaySE(Change_SE);
		m_SelectCount++;
		//��ɍs���̂𐧌�����
		int num = m_SelectCount - FieldListNum;
		num = CLAMP(num, 0, m_Abilities.Size() - FieldListNum);
		m_Abilities.SetDrawFirst(std::max(m_Abilities.FirstDrawNum(), num));
	}
	//Range�I�[�o�[�ɂȂ��Ă��܂��̂Ő���
	m_SelectCount = CLAMP(m_SelectCount, 0, m_Abilities.Size());
	m_Abilities.SetSelectAbilityNum(m_SelectCount);

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Return)) {
		m_IsSelect = false;
	}
}

void AbilityEdit::SetAbilityDraw(int num) const{

	GSvector2 draw_pos{ SlotPos.x, SlotPos.y + (SlotPos.y + SlotPos.y) * num };

	//�X���b�g�쐬
	gsDrawSprite2D(AbilityFrame_Texture, &draw_pos, NULL, NULL, NULL, &SlotScale, NULL);
	draw_pos.x += AbilityPos.x;
	draw_pos.y += AbilityPos.y;

	//�X�L���`��
	int ability = m_SetAbilities.at(num);
	if (ability == Ability::NoneAbility)return;
	GSuint a = BlowAttack_Ability_Taxture;

	switch (ability) {
	case Ability::BlowAttackAbility:			//�t����΂�
		a = BlowAttack_Ability_Taxture;
		break;
	case Ability::PushAttackAbility:			//�˂��グ
		a = PushAttack_Ability_Taxture;
		break;
	case Ability::AvoidAttackAbility:			//����U��
		a = AvoidAttack_Ability_Taxture;	
		break;
	case Ability::RotatingAttackAbility:		//��]�a��
		a = RotatingAttack_Ability_Taxture;
		break;
	case Ability::InpactGroundAttackAbility:	//�Ռ��U��
		a = InpactGroundAttack_Ability_Taxture;
		break;
	case Ability::SlamAttackAbility:			//�󒆂ɔ�΂�
		a = SlamAttack_Ability_Taxture;
		break;
	case Ability::WildDance:					//����
		a = WildDance_Taxture;
		break;
	case Ability::WaveWildDanceAbility:			//�g������
		a = WaveWildDance_Ability_Taxture;
		break;
	case Ability::FangsAbility:					//���
		a = Fangs_Ability_Taxture;
		break;
	default:
		break;
	}
	gsDrawSprite2D(a, &draw_pos, NULL, NULL, NULL, &TextScale, NULL);

}

void AbilityEdit::DeleteAbilityArray(){
	//�X�L�����Z�b�g����
	m_Abilities.SetAbility(m_SetAbilities.at(m_SetAbilityCount));
	//�X�L������
	m_SetAbilities.at(m_SetAbilityCount) = Ability::NoneAbility;
}

void AbilityEdit::SwapAbilityArray(){
	//�ۊǂ��Ă���
	int strage = m_SetAbilities.at(m_SetAbilityCount);
	//�X�L�����㏑��
	m_SetAbilities.at(m_SetAbilityCount) = m_Abilities.SelectAbility(m_SelectCount);
	//�X�L���폜
	m_Abilities.DeleteAbility(m_SelectCount);
	//NONE�ł͂Ȃ�������i�[
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
