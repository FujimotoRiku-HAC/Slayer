#include "GamePlayScene.h"
#include "Character/Enemy/StoneSoldier/StoneSoldier.h"
#include "Character/Enemy/Golem/Golem.h"
#include "Character/Enemy/Ticket/Ticket.h"
#include "Character/Player/Player.h"
#include "Character/Door/Door.h"
#include "Camera/Target.h"
#include "Field/Field.h"
#include "Light/Light.h"
#include "Camera/DefalutCamera.h"
#include "SceneManager.h"

//�J�n
void GamePlayScene::Start() {

	ResetFrag();

	//�t�B�[���h�N���X�̒ǉ�
	m_World.AddField(new Field{ Octree,OctreeCollider,Texture_Skybox });
	//�J����
	m_World.AddCamera(new DefalutCamera{
		&m_World,DefaultCameraPos,DefaultCameraAt });
	//���C�g�N���X�̒ǉ�
	m_World.AddLight(new Light{ &m_World });
	//�`�P�b�g�N���X
	m_World.AddActor(new Ticket{ &m_World });
	//�v���[���[�N���X�̒ǉ�
	m_World.AddActor(new Player{ &m_World,PlayerPos });
	//�\���W���[�ǉ�
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos2,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos3,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos4,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos5,EnemyRotate });
	//�h�A�ǉ�
	m_World.GetField()->Add(new Door{ &m_World,DoorPos,Mesh_Door,Mesh_Door });
	//�^�[�Q�b�g�A�N�^�[�ǉ�
	m_World.AddActor(new Target{});

	//�V���h�E�}�b�v�쐬
	gsCreateShadowMap(2, ShadowMapSize, GS_TRUE);
	//�V���h�E�}�b�v��K�p���鋗��
	gsSetShadowMapDistance(ShadowMapDis);
	//�J�X�P�[�h�V���h�E�}�b�v�̕������鋗��(�f�t�H���g��0.5)
	gsSetShadowMapCascadeLamda(ShadowMapCascade);
	//�V���h�E�̔Z����ݒ�
	gsSetShadowMapAttenuation(ShadowMapAttenuation);

	m_Text = Text::Play;

	gsPlayBGM(Play_BGM);
}

//�X�V
void GamePlayScene::Update(float delta_time) {
	switch (m_Text)
	{
	case GamePlayScene::Play:
		PlayUpdate(delta_time);
		break;
	case GamePlayScene::TitleReturn:
		TitleUpdate(delta_time);
		break;
	case GamePlayScene::EndReturn:
		EndUpdate(delta_time);
		break;
	default:
		break;
	}
}

//�`��
void GamePlayScene::Draw() const {
	m_World.Draw();

	if (m_IsClear) {
		m_GameClear.Draw();
		GameClearDraw();
	}
}


void GamePlayScene::SpawnGolem(){
	//�������Ă��Ȃ�������
	if (m_IsGenerate)return;
	//�S�[�������o�����Ă��Ȃ�������
	if (m_World.FindActor(st_Golem) != nullptr)return;
	//�G�����Ȃ�������
	if (m_World.FindActorWithTag(st_Enemy).size() != 0)return;
	//�v���C���[�����Ȃ������烊�^�[��
	if (m_World.FindActor(st_Player) == nullptr)return;
	//�{�X��ɓ����ʒu�Ȃ�
	if (!static_cast<Player*>(m_World.FindActor(st_Player))->BossFight())return;

	m_World.AddActor(new Golem{ &m_World,GolemPos,EnemyRotate });
	gsStopBGM();
	gsPlayBGM(BossFight_BGM);
	m_IsGenerate = true;
}

void GamePlayScene::PlayUpdate(float delta_time){

	//�|�[�Y�{�^������������
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Pose)) {
		m_NextScene = (int)SceneManager::EachScene::Option;
		m_IsEnd = true;
	}
	//�Q�[���I�[�o�[�J��
	if (m_World.IsGameOver()) {
		m_NextScene = (int)SceneManager::EachScene::GameOver;
		m_IsSceneClear = true;
		m_IsEnd = true;
	}

	if (m_World.IsClear() && !m_IsClear) {
		m_IsClear = true;
		m_Timer.TimeDataSave();
		m_GameClear.Start();
		m_Text = Text::TitleReturn;
	}

	//�U�R�G�����Ȃ���������J��
	if (m_World.FindActorWithTag(st_Enemy).size() <= 0) {
		m_World.OnMessage(st_Message_OpenDoor, nullptr);
		m_World.GetCamera()->HandleMessage(st_Message_OpenDoor, nullptr);
	}
	SpawnGolem();

	m_World.Update(delta_time);
	m_Timer.Update(delta_time);
	
}

void GamePlayScene::TitleUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_Text = Text::EndReturn;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		m_NextScene = (int)SceneManager::EachScene::Title;
		m_IsEnd = true;
		gsPlaySE(Click_SE);
	}
}

void GamePlayScene::EndUpdate(float delta_time){

	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_Text = Text::TitleReturn;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		m_IsGameEnd = true;
		gsPlaySE(Click_SE);
	}
}

void GamePlayScene::GameClearDraw()const{
	GSvector2 pos{ ScreenWidth / 2 - ClearTextPosOffset,ScreenHeight / 2 };
	GSrect rect{ 0.0f,ClearRectScale.y * 3,ClearRectScale.x ,ClearRectScale.y * 4 };
	GScolor color{ 0.f,0.f,0.f,1.0f };
	
	//�e�L�X�g�`��
	for (int i = ClearFirstTextNum;i < ClearTextNum; ++i) {
		if (i == m_Text)color = { 0.f,0.f,1.f,1.f };
		else color = { 1.f,1.f,1.f,1.f };
		gsDrawSprite2D(Clear_Text, &pos, &rect, NULL, &color, NULL, NULL);
		rect.top += ClearRectScale.y;
		rect.bottom += ClearRectScale.y;
		pos.x += ClearTextShiftPosOffset.x;
		pos.y += ClearTextShiftPosOffset.y;
	}
}

//�I�����Ă��邩
bool GamePlayScene::IsEnd() const {
	return m_IsEnd;
}

bool GamePlayScene::StackClear() const{
	return m_IsSceneClear;
}

void GamePlayScene::ResetFrag(){
	m_IsSceneClear = false;
	m_IsEnd = false;
}

//���̃V�[����Ԃ�
int GamePlayScene::Next() const {
	return m_NextScene;
}

//�I��
void GamePlayScene::End() {
	//���[���h����
	m_World.Clear();
	//�G�t�F�N�g�S�N���A
	gsStopAllEffects();

	gsDeleteSkinMesh(Mesh_Player);
	gsDeleteSkinMesh(Mesh_Weapon);
	gsDeleteSkinMesh(Mesh_StoneSoldier);
	gsDeleteSkinMesh(Mesh_Golem);

	gsDeleteTexture(IconFrame_Texture);
	gsDeleteTexture(AttackIcon_Texture);
	gsDeleteTexture(Num_Texture);
	gsDeleteTexture(AvoidIcon_Texture);
	gsDeleteTexture(BlowAttack_Ability_UI_Taxture);
	gsDeleteTexture(PushAttack_Ability_UI_Taxture);
	gsDeleteTexture(AvoidAttack_Ability_UI_Taxture);
	gsDeleteTexture(RotatingAttack_Ability_UI_Taxture);
	gsDeleteTexture(InpactGroundAttack_Ability_UI_Taxture);
	gsDeleteTexture(SlamAttack_Ability_UI_Taxture);
	gsDeleteTexture(WildDance_UI_Taxture);
	gsDeleteTexture(WaveWildDance_Ability_UI_Taxture);
	gsDeleteTexture(Fangs_Ability_UI_Taxture);
	gsDeleteTexture(Heal_Portion_Texture);
	gsDeleteTexture(Attack_PowerUp_Portion_Texture);
	gsDeleteTexture(NumText_Texture);
	gsDeleteTexture(NotIconFrame_Texture);
	gsDeleteTexture(HealthUpAndHeal_Skill_UI_Texture);
	gsDeleteTexture(AttackPowerUp_Skill_UI_Texture);
	gsDeleteTexture(AttackPowerLergeUp_Skill_UI_Texture);
	gsDeleteTexture(HealthHealSeedUp_Skill_UI_Texture);
	gsDeleteTexture(AvoidPerformanceUp_Skill_UI_Texture);
	gsDeleteTexture(AvoidDistanceUp_Skill_UI_Texture);
	gsDeleteTexture(JustAvoidSlow_Skill_UI_Texture);
	gsDeleteTexture(DivineProtection_Skill_UI_Texture);
	gsDeleteTexture(FullCharge_Skill_UI_Texture);
	gsDeleteTexture(CrisisCharge_Skill_UI_Texture);
	gsDeleteTexture(SuperArmor_Skill_UI_Texture);

	gsDeleteSE(Player_JustAvoid_SE);
	gsDeleteSE(Enemy_Finish_SE);
	gsDeleteSE(Soldier_Attack_SE);
	gsDeleteSE(Soldier_Attack2_SE);
	gsDeleteSE(Golem_Attack_SE);
	gsDeleteSE(Golem_Attack2_SE);
	gsDeleteSE(Golem_Attack3_SE);
	gsDeleteSE(Golem_Attack4_SE);
	gsDeleteSE(Golem_Skill_SE);
	gsDeleteSE(React_SE);
	gsDeleteSE(PlayerReact_SE);
	gsDeleteSE(PlayerFoot_SE);
	gsDeleteSE(PlayerPowerUp_SE);
	gsDeleteSE(PlayerHeal_SE);
	gsDeleteSE(Charge_SE);
}

bool GamePlayScene::IsGameEnd() const
{
	return m_IsGameEnd;
}