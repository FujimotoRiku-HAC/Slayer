#include "LoadScene.h"
#include "SceneManager.h"

// �W���V�F�[�_�[�̐ݒ�
#define GS_ENABLE_AUX_LIGHT                 // �⏕���C�g��L���ɂ���
#define GS_ENABLE_BAKED_LIGHTMAP_SHADOW     // �x�C�N�������C�g�}�b�v�ɉe�𗎂Ƃ�
#define GS_ENABLE_SOFT_SHADOW               // �\�t�g�V���h�E�i�e�̗֊s���ڂ����j
#define GS_ENABLE_RIM_LIGHT                 // �������C�g��L���ɂ���
#define GS_ENABLE_DITHER_TRANSPARENCY		// �f�B�U��������L���ɂ���

#include <GSstandard_shader.h>

void LoadScene::Start() {
	gsLoadTexture(Load_Texture,		"Assets/Texture/UI/Load/loading_bg.png");
	gsLoadTexture(NowLoad_Texture,	"Assets/Texture/UI/Load/now_loading_bg.png");

	//�񓯊��ŃA�Z�b�g�����[�h
	gslib::Game::run_thread([=] { AssetsLoad(); });
}

void LoadScene::Update(float delta_time){
	if (!m_IsLoad) {
		m_NextScene = (int)SceneManager::EachScene::Play;
		m_IsEnd = true;
		return;
	}
	m_Angle += delta_time;
}

void LoadScene::Draw() const{
	//�E���̃��[�h
	gsDrawSprite2D(Load_Texture, &LoadTextPos, NULL, &LoadCenterPos, NULL, NULL, m_Angle);
	//�^�񒆂̃��[�h�`��
	gsDrawSprite2D(NowLoad_Texture, &NowLoadTextPos, NULL, NULL, NULL, NULL, NULL);
}

bool LoadScene::IsEnd() const{
	return m_IsEnd;
}

bool LoadScene::StackClear() const{
	return false;
}

void LoadScene::ResetFrag(){
	m_IsEnd = false;
	m_IsLoad = true;
}

int LoadScene::Next() const{
	return m_NextScene;
}

void LoadScene::End(){}

bool LoadScene::IsGameEnd() const{
	return false;
}

void LoadScene::AssetsLoad(){

	// �f�t�H���g�V�F�[�_�[�̏������i���b�V���t�@�C����ǂݍ��ޑO�ɗL���ɂ���j
	gsInitDefaultShader();
	gsEnable(GS_FRUSTUM_CULLING);

	//�L�����N�^�[
	gsLoadSkinMesh(Mesh_Player,			"Assets/Character/Player/player.mshb");
	gsLoadMesh(Mesh_Weapon,				"Assets/Character/Player/sword.mshb");
	gsLoadSkinMesh(Mesh_StoneSoldier,	"Assets/Character/Enemy/Soldier/soldier.mshb");
	gsLoadSkinMesh(Mesh_Golem,			"Assets/Character/Enemy/golem.mshb");
	gsLoadMesh(Mesh_Door,				"Assets/Character/Door/door.mshb");
	//��
	gsLoadOctree(Octree,			"Assets/Octree/octree.oct");
	gsLoadOctree(OctreeCollider,	"Assets/Collider/collider.oct");
	gsLoadLightmap(0,				"Assets/Light/lightmap.txt");
	gsLoadReflectionProbe(0,		"Assets/Ref/reflection_probe.txt");
	gsLoadAuxLight(0,				"Assets/Light/aux_light.txt");

	//�e�N�X�`���ǂݍ���
	gsLoadTexture(IconFrame_Texture,	"Assets/Texture/UI/PlayScene/battle_icon.png");
	gsLoadTexture(AttackIcon_Texture,	"Assets/Texture/UI/PlayScene/attack_icon.png");
	gsLoadTexture(AvoidIcon_Texture,	"Assets/Texture/UI/PlayScene/avoid_icon.png");
	gsLoadTexture(Num_Texture,			"Assets/Texture/UI/PlayScene/damage_num.png");
	gsLoadTexture(Clear_Text,			"Assets/Texture/UI/Clear/clear_scene_text.png");
	gsLoadTexture(Play_Text,			"Assets/Texture/UI/PlayScene/play_scene_text.png");
	gsLoadTexture(X_Button_Texture,		"Assets/Texture/UI/PlayScene/x_button.png");

	//�G�t�F�N�g�ǂݍ���
	gsLoadEffect(Effect_Attack,			"Assets/Effect/Attack/basic_attack.efkefc");
	gsLoadEffect(Effect_Counter,		"Assets/Effect/PlayerAbility/counter.efkefc");
	gsLoadEffect(Effect_CounterLines,	"Assets/Effect/SpeedLines/speed_lines.efkefc");

	//BGM�ESE
	gsLoadBGM(Play_BGM,					"Assets/Sound/BGM/field_bgm.ogg", GS_TRUE);
	gsLoadBGM(BossFight_BGM,			"Assets/Sound/BGM/golem_fight.ogg", GS_TRUE);
	gsLoadSE(Player_JustAvoid_SE,		"Assets/Sound/SE/Player/just_avoid.wav", 4, GS_FALSE);
	gsLoadSE(Enemy_Finish_SE,			"Assets/Sound/SE/enemy_finish_se.wav", 4, GS_FALSE);
	gsLoadSE(Soldier_Attack_SE,			"Assets/Sound/SE/Soldier/soldier_attack_1.wav", 4, GS_FALSE);
	gsLoadSE(Soldier_Attack2_SE,		"Assets/Sound/SE/Soldier/soldier_attack_2.wav", 4, GS_FALSE);
	gsLoadSE(Golem_Attack_SE,			"Assets/Sound/SE/Golem/golem_attack_1.wav", 4, GS_FALSE);
	gsLoadSE(Golem_Attack2_SE,			"Assets/Sound/SE/Golem/golem_attack_2.wav", 4, GS_FALSE);
	gsLoadSE(Golem_Attack3_SE,			"Assets/Sound/SE/Golem/golem_attack_3.wav", 4, GS_FALSE);
	gsLoadSE(Golem_Attack4_SE,			"Assets/Sound/SE/Golem/golem_attack_4.wav", 4, GS_FALSE);
	gsLoadSE(Golem_Skill_SE,			"Assets/Sound/SE/Golem/golem_skill.wav", 4, GS_FALSE);
	gsLoadSE(React_SE,					"Assets/Sound/SE/react.wav", 4, GS_FALSE);
	gsLoadSE(PlayerReact_SE,			"Assets/Sound/SE/Player/player_react.wav", 4, GS_FALSE);
	gsLoadSE(PlayerFoot_SE,				"Assets/Sound/SE/Player/foot_step.wav", 4, GS_FALSE);
	gsLoadSE(PlayerPowerUp_SE,			"Assets/Sound/SE/Player/power_up.wav", 4, GS_FALSE);
	gsLoadSE(PlayerHeal_SE,				"Assets/Sound/SE/Player/heal.wav", 4, GS_FALSE);
	gsLoadSE(Charge_SE,					"Assets/Sound/SE/Player/charge.wav", 4, GS_FALSE);

	//���[�h�V�[���I��
	m_IsLoad = false;
}
