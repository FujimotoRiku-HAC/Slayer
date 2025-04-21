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

//開始
void GamePlayScene::Start() {

	ResetFrag();

	//フィールドクラスの追加
	m_World.AddField(new Field{ Octree,OctreeCollider,Texture_Skybox });
	//カメラ
	m_World.AddCamera(new DefalutCamera{
		&m_World,DefaultCameraPos,DefaultCameraAt });
	//ライトクラスの追加
	m_World.AddLight(new Light{ &m_World });
	//チケットクラス
	m_World.AddActor(new Ticket{ &m_World });
	//プレーヤークラスの追加
	m_World.AddActor(new Player{ &m_World,PlayerPos });
	//ソルジャー追加
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos2,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos3,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos4,EnemyRotate });
	m_World.AddActor(new StoneSoldier{ &m_World,SoldierPos5,EnemyRotate });
	//ドア追加
	m_World.GetField()->Add(new Door{ &m_World,DoorPos,Mesh_Door,Mesh_Door });
	//ターゲットアクター追加
	m_World.AddActor(new Target{});

	//シャドウマップ作成
	gsCreateShadowMap(2, ShadowMapSize, GS_TRUE);
	//シャドウマップを適用する距離
	gsSetShadowMapDistance(ShadowMapDis);
	//カスケードシャドウマップの分割する距離(デフォルトは0.5)
	gsSetShadowMapCascadeLamda(ShadowMapCascade);
	//シャドウの濃さを設定
	gsSetShadowMapAttenuation(ShadowMapAttenuation);

	m_Text = Text::Play;

	gsPlayBGM(Play_BGM);
}

//更新
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

//描画
void GamePlayScene::Draw() const {
	m_World.Draw();

	if (m_IsClear) {
		m_GameClear.Draw();
		GameClearDraw();
	}
}


void GamePlayScene::SpawnGolem(){
	//生成していなかったら
	if (m_IsGenerate)return;
	//ゴーレムが出現していなかったら
	if (m_World.FindActor(st_Golem) != nullptr)return;
	//敵がいなかったら
	if (m_World.FindActorWithTag(st_Enemy).size() != 0)return;
	//プレイヤーがいなかったらリターン
	if (m_World.FindActor(st_Player) == nullptr)return;
	//ボス戦に入れる位置なら
	if (!static_cast<Player*>(m_World.FindActor(st_Player))->BossFight())return;

	m_World.AddActor(new Golem{ &m_World,GolemPos,EnemyRotate });
	gsStopBGM();
	gsPlayBGM(BossFight_BGM);
	m_IsGenerate = true;
}

void GamePlayScene::PlayUpdate(float delta_time){

	//ポーズボタンを押したら
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Pose)) {
		m_NextScene = (int)SceneManager::EachScene::Option;
		m_IsEnd = true;
	}
	//ゲームオーバー遷移
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

	//ザコ敵がいなかったら扉開く
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
	
	//テキスト描画
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

//終了しているか
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

//次のシーンを返す
int GamePlayScene::Next() const {
	return m_NextScene;
}

//終了
void GamePlayScene::End() {
	//ワールド消去
	m_World.Clear();
	//エフェクト全クリア
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