#include "CharacterEditScene.h"
#include "Character/Player/Player.h"
#include "Field/Field.h"
#include "Light/Light.h"
#include "Camera/TitleCamera.h"
#include "Scene/SceneManager.h"

// �W���V�F�[�_�[�̐ݒ�
#define GS_ENABLE_AUX_LIGHT                 // �⏕���C�g��L���ɂ���
#define GS_ENABLE_BAKED_LIGHTMAP_SHADOW     // �x�C�N�������C�g�}�b�v�ɉe�𗎂Ƃ�
#define GS_ENABLE_SOFT_SHADOW               // �\�t�g�V���h�E�i�e�̗֊s���ڂ����j
#define GS_ENABLE_RIM_LIGHT                 // �������C�g��L���ɂ���
#define GS_ENABLE_DITHER_TRANSPARENCY		// �f�B�U��������L���ɂ���

#include <GSstandard_shader.h>

//�g�̕`��p
void CharacterEditScene::Start(){
	ResetFrag();
	// �f�t�H���g�V�F�[�_�[�̏������i���b�V���t�@�C����ǂݍ��ޑO�ɗL���ɂ���j
	gsInitDefaultShader();

	gsEnable(GS_FRUSTUM_CULLING);

	//�V���h�E�}�b�v�쐬
	gsCreateShadowMap(2, ShadowMapSize, GS_TRUE);
	//�V���h�E�}�b�v��K�p���鋗��
	gsSetShadowMapDistance(ShadowMapDis);
	//�J�X�P�[�h�V���h�E�}�b�v�̕������鋗��(�f�t�H���g��0.5)
	gsSetShadowMapCascadeLamda(ShadowMapCascade);
	//�V���h�E�̔Z����ݒ�
	gsSetShadowMapAttenuation(ShadowMapAttenuation);

	//�L�����N�^�[
	gsLoadSkinMesh(Mesh_Player,			"Assets/Character/Player/player.mshb");
	gsLoadMesh(Mesh_Weapon,				"Assets/Character/Player/sword.mshb");

	//�e�N�X�`�����[�h
	gsLoadTexture(Equipment_Texture,	"Assets/Texture/Equipment/equipment.png");
	gsLoadTexture(Text2_Texture,		"Assets/Texture/Equipment/text2.png");
	gsLoadTexture(Sprite_Equipment,		"Assets/Texture/Equipment/equipment_bg.png");
	gsLoadTexture(Frame_Texture,		"Assets/Texture/Ability/AbilitySlot/ability_bar.png");
	gsLoadTexture(Text_Texture3,		"Assets/Texture/Text/text_texture.png");
	gsLoadTexture(Return_Texture,		"Assets/Texture/Text/return.png");
	//�G�t�F�N�g���[�h
	gsLoadEffect(Effect_BlowAttack,				"Assets/Effect/PlayerAbility/blow_attack_effect.efkefc");
	gsLoadEffect(Effect_PushAttack,				"Assets/Effect/PlayerAbility/push_attack_effect.efkefc");
	gsLoadEffect(Effect_AvoidAttack,			"Assets/Effect/PlayerAbility/avoid_attack_effect.efkefc");
	gsLoadEffect(Effect_InpactAttack,			"Assets/Effect/GroundShock/ground_shock.efkefc");
	gsLoadEffect(Effect_SlamAttack,				"Assets/Effect/PlayerAbility/slam_attack_effect.efkefc");
	gsLoadEffect(Effect_WildDance,				"Assets/Effect/PlayerAbility/wild_dance_effect.efkefc");
	gsLoadEffect(Effect_WaveWildDance,			"Assets/Effect/PlayerAbility/wave_wild_dance_effect.efkefc");
	gsLoadEffect(Effect_Arrow,					"Assets/Effect/Bullet/Arrow02/arrow_yellow.efkefc");
	gsLoadEffect(Effect_HealthUpHealBuff,		"Assets/Effect/Buff/buff_green_loop.efkefc");
	gsLoadEffect(Effect_AttackPowerUpBuff,		"Assets/Effect/Buff/buff_orenge_loop.efkefc");
	gsLoadEffect(Effect_AttackPowerLergeUpBuff, "Assets/Effect/Buff/buff_red_loop.efkefc");
	gsLoadEffect(Effect_HealSeedBuff,			"Assets/Effect/Buff/buff_ocean_loop.efkefc");
	gsLoadEffect(Effect_AvoidPerformanceBuff,	"Assets/Effect/Buff/buff_blur_loop.efkefc");
	gsLoadEffect(Effect_AvoidDistanceBuff,		"Assets/Effect/Buff/buff_yellow_loop.efkefc");
	gsLoadEffect(Effect_JustAvoidSlowBuff,		"Assets/Effect/Buff/buff_white_loop.efkefc");
	gsLoadEffect(Effect_DivineProtectionBuff,	"Assets/Effect/Buff/buff_black_loop.efkefc");
	gsLoadEffect(Effect_FullChargeBuff,			"Assets/Effect/Buff/buff_little_red_loop.efkefc");
	gsLoadEffect(Effect_CrisisChrageBuff,		"Assets/Effect/Buff/buff_purple_loop.efkefc");
	gsLoadEffect(Effect_SuperArmorBuff,			"Assets/Effect/Buff/buff_little_green_loop.efkefc");
	//SE�EBGM�ǂݍ���
	gsLoadSE(Player_Attack_SE,			"Assets/Sound/SE/Player/attack.wav",2,GS_FALSE);
	gsLoadSE(Player_Attack2_SE,			"Assets/Sound/SE/Player/attack_2.wav", 2, GS_FALSE);
	gsLoadBGM(Select_BGM,				"Assets/Sound/BGM/select_bgm.ogg", GS_TRUE);

	//�t�B�[���h�N���X�̒ǉ�
	m_World.AddField(new Field{ Octree,OctreeCollider,Texture_Skybox });

	//�J�����N���X�̒ǉ�
	m_World.AddCamera(new TitleCamera{
		&m_World,TitleCameraPos,TitleCameraAt });

	//���C�g�N���X�̒ǉ�
	m_World.AddLight(new Light{ &m_World });

	//�v���[���[�N���X�̒ǉ�
	m_World.AddActor(new Player{ &m_World,PlayerPos });

	gsPlayBGM(Select_BGM);
	m_Text = Text::GameStart;
}

void CharacterEditScene::Update(float delta_time){
	m_World.Update(delta_time);

	PlayerAction();
	switch (m_Text)
	{
	case CharacterEditScene::GameStart:
		StartUpdate(delta_time);
		break;
	case CharacterEditScene::Ability:
		AbilityUpdate(delta_time);
		break;
	case CharacterEditScene::Skill:
		SkillUpdate(delta_time);
		break;
	case CharacterEditScene::Return:
		ReturnUpdate(delta_time);
		break;
	default:
		break;
	}

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		m_IsSelect = true;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Return)) {
		m_IsSelect = false;
	}
}

void CharacterEditScene::Draw() const{
	m_World.Draw();
	//�w�i��`��
	GSvector2 bg_pos{ 0.0f, 0.0f };
	gsDrawSprite2D(Sprite_Equipment, &bg_pos, NULL, NULL, NULL, NULL, NULL);
	bg_pos = { 10.0f,20.0f };
	gsDrawSprite2D(Equipment_Texture, &bg_pos, NULL, NULL, NULL, NULL, NULL);

	switch (m_Text)
	{
	case CharacterEditScene::GameStart:
		break;
	case CharacterEditScene::Ability:
		if (m_IsSelect) {
			m_Ability.DrawLogo();
			m_Ability.Draw();
		}
		break;
	case CharacterEditScene::Skill:
		if (m_IsSelect) {
			m_Skill.DrawLogo();
			m_Skill.Draw();
		}
		break;
	case CharacterEditScene::Return:
		break;

	}

	GSrect frame_rect{ EditFrameRect.left, EditFrameRect.top , EditFrameRect.right , EditFrameRect.bottom };

	GScolor frame_color{ 1.f,1.f,1.f,0.5f };
	//�g�̒��̕`��
	GSrect frame_rect2{ 0.0f, EditFrameRect.top + 1.0f , EditFrameRect.right -1.0f, EditFrameRect.bottom -1.0f };
	GScolor frame_color2{ 0.f,0.f,0.f,1.0f };
	//���S�̍쐬
	GSvector2 draw_pos{ EditTextPos.x,EditTextPos.y };
	GSrect text_rect{ 0.0f,0.0f,EditRect.right,EditRect.bottom };

	//�I�𒆂Ȃ�F���ς��
	if (!m_IsSelect) {
		for (int i = 0; i < EditTextNum; i++) {
			if (i == m_Text)frame_color = { 0.f,0.f,1.f,1.0f };
			else frame_color = { 1.f,1.f,1.f,1.0f };
			//�g�̕`��
			gsDrawRectangle2D(&frame_rect, &frame_color);
			frame_rect.top += EditDrawShift;
			frame_rect.bottom += EditDrawShift;
			//�g�̕`��(���g)
			gsDrawRectangle2D(&frame_rect2, &frame_color2);
			frame_rect2.top += EditDrawShift;
			frame_rect2.bottom += EditDrawShift;
			//�e�L�X�g�̕`��
			gsDrawSprite2D(Text2_Texture, &draw_pos, &text_rect, NULL, &EditTextColor, NULL, NULL);
			text_rect.top += EditRect.bottom;
			text_rect.bottom += EditRect.bottom;
			draw_pos.y += RectShiftPos;

		}
	}
}

bool CharacterEditScene::IsEnd() const{
	return m_IsEnd;
}

bool CharacterEditScene::StackClear() const{
	return m_IsClear;
}

void CharacterEditScene::ResetFrag(){
	m_IsClear = false;
	m_IsEnd = false;
}

int CharacterEditScene::Next() const{
	return m_NextScene;
}

void CharacterEditScene::End(){
	m_World.Clear();
	gsStopAllEffects();
	gsDeleteTexture(Equipment_Texture);
	gsDeleteTexture(Text2_Texture);
	gsDeleteTexture(Sprite_Equipment);
	gsDeleteTexture(Frame_Texture);
	gsDeleteTexture(Text_Texture3);
	gsDeleteBGM(Select_BGM);
}

bool CharacterEditScene::IsGameEnd() const{
	return false;
}

void CharacterEditScene::StartUpdate(float delta_time){
	if (m_IsSelect) {
		gsPlaySE(Click_SE);
		m_IsClear = true;
		m_NextScene = (int)SceneManager::EachScene::Load;
		m_Ability.Save();
		m_Skill.Save();
		m_IsEnd = true;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Ability;
	}
}

void CharacterEditScene::AbilityUpdate(float delta_time){
	if (m_IsSelect) {
		gsPlaySE(Click_SE);
		m_Ability.Update(delta_time);
		//�v���C���[�̃A�j���[�V�����X�V
		m_Ability.PlayerAbilityAnim(&m_World);
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Text = Text::GameStart;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Skill;
	}
}

void CharacterEditScene::SkillUpdate(float delta_time) {
	if (m_IsSelect) {
		gsPlaySE(Click_SE);
		m_Skill.Update(delta_time);
		m_Skill.SkillEffect(&m_World);
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Ability;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Return;
	}
}

//�߂�
void CharacterEditScene::ReturnUpdate(float delta_time){
	if (m_IsSelect) {
		gsPlaySE(Click_SE);
		m_IsClear = true;
		m_NextScene = (int)SceneManager::EachScene::Title;
		m_IsEnd = true;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Text = Text::Skill;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Text = Text::GameStart;
	}
}

void CharacterEditScene::PlayerAction(){
	//���b�Z�[�W���M
	static_cast<Player*>(m_World.FindActor(st_Player))->HandleMessage(st_Message_SelectScene, nullptr);
}
