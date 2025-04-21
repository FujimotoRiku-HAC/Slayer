#include "TitleScene.h"
#include "Field/Field.h"
#include "Light/Light.h"
#include "Camera/TitleCamera.h"
#include "Character/Player/PlayerAnim.h"
#include "SceneManager.h"
#include "Character/Door/Door.h"

#include <GSstandard_shader.h>

void TitleScene::Start() {
	//初期化
	ResetFrag();

	//視錐台カリング有効
	gsEnable(GS_FRUSTUM_CULLING);
	// デフォルトシェーダーの初期化（メッシュファイルを読み込む前に有効にする）
	gsInitDefaultShader();
	//シャドウマップ作成
	gsCreateShadowMap(2, ShadowMapSize, GS_TRUE);
	//シャドウマップを適用する距離
	gsSetShadowMapDistance(ShadowMapDis);
	//カスケードシャドウマップの分割する距離(デフォルトは0.5)
	gsSetShadowMapCascadeLamda(ShadowMapCascade);
	//シャドウの濃さを設定
	gsSetShadowMapAttenuation(ShadowMapAttenuation);

	//データの読み込み
	gsLoadBGM(Title_BGM,				"Assets/Sound/BGM/title_bgm.ogg", GS_TRUE);
	gsLoadSE(Click_SE,					"Assets/Sound/SE/Other/click.wav", 1, GS_FALSE);
	gsLoadSE(Change_SE,					"Assets/Sound/SE/Other/change.wav", 1, GS_FALSE);
	//データロード
	m_Data.DataLoad(					"Data/config_data.txt");
	//メッシュ読み込み
	gsLoadSkinMesh(Mesh_TitlePlayer,	"Assets/Character/Player/title_player.mshb");
	gsLoadMesh(Mesh_Door,				"Assets/Character/Door/door.mshb");
	//テクスチャ
	gsLoadTexture(Title_Slayer_Texture, "Assets/Texture/UI/Title/slayer.png");
	gsLoadTexture(Text_Texture,			"Assets/Texture/UI/Title/title_text.png");
	gsLoadTexture(Texture_Skybox,		"Assets/Skybox/skybox.dds");

	gsLoadOctree(Octree,				"Assets/Octree/octree.oct");
	gsLoadOctree(OctreeCollider,		"Assets/Collider/collider.oct");
	gsLoadLightmap(0,					"Assets/Light/lightmap.txt");
	gsLoadReflectionProbe(0,			"Assets/Ref/reflection_probe.txt");
	gsLoadAuxLight(0,					"Assets/Light/aux_light.txt");

	//プレイヤー
	m_Mesh = AnimatedMesh{ Mesh_TitlePlayer,TitlePlayerAnim::MotionTitle,true };
	// 初期位置の設定
	m_Transform.translate(TitlePlayerPos);
	m_Transform.rotate(GSvector3::up(), 0.f);
	// ワールド変換行列を設定
	m_Mesh.Transform(m_Transform.localToWorldMatrix());

	//フィールドクラスの追加
	m_World.AddField(new Field{ Octree,OctreeCollider,Texture_Skybox });

	//カメラクラスの追加
	m_World.AddCamera(new TitleCamera{
		&m_World,SetCameraPos,SetCameraAt });

	//ドア追加
	m_World.GetField()->Add(new Door{ &m_World,DoorPos,Mesh_Door,Mesh_Door });

	//ライトクラスの追加
	m_World.AddLight(new Light{ &m_World });

	//音量設定
	gsSetVolumeBGM(m_Data.GetBGMValue());
	gsSetMasterVolumeSE(m_Data.GetSEValue());
	//BGMの再生
	gsPlayBGM(Title_BGM);

	m_TextField = TextField::GameStart;
}

void TitleScene::Update(float delta_time) {
	m_Mesh.Update(delta_time);
	// ワールド変換行列を設定
	m_Mesh.Transform(m_Transform.localToWorldMatrix());
	
	switch (m_TextField)
	{
	case TitleScene::GameStart:
		StartUpdate(delta_time);
		break;
	case TitleScene::Option:
		OptionUpdate(delta_time);
		break;
	case TitleScene::GameEnd:
		EndUpdate(delta_time);
		break;
	default:
		break;
	}
}

void TitleScene::Draw()const {
	m_World.Draw();
	m_Mesh.Draw();

	//タイトルテキスト描画
	GSvector2 TitleTextPos{ ScreenWidth / 2.0f - TitleTextPosSet.x,ScreenHeight / 2.0f - TitleTextPosSet.y };
	GSrect TitleTextRect{ 0.f,0.f,TitleRectScale.x,TitleRectScale.y };
	GScolor color{ 0.f,0.f,0.f,0.f };
	//ゲームタイトル描画
	gsDrawSprite2D(Title_Slayer_Texture, &TitleTextPos, NULL, NULL, NULL, NULL, NULL);

	TitleTextPos = { ScreenWidth / 2.f + TitleRectScale.x,ScreenHeight / 2.f + TitleRectScale.y };

	for (int i = 0; i < TitleTextFieldNum; ++i) {
		if (i == m_TextField)color = { 0.f,0.f,1.f,1.0f };
		else color = { 1.f,1.f,1.f,1.0f };
		//テキスト描画
		gsDrawSprite2D(Text_Texture, &TitleTextPos, &TitleTextRect, NULL, &color, NULL, NULL);
		TitleTextRect.top += TitleRectScale.y;
		TitleTextRect.bottom += TitleRectScale.y;
		TitleTextPos.y += TitleTextBlankScale;
	}

}

bool TitleScene::IsEnd() const {
	return m_IsEnd;
}

bool TitleScene::StackClear() const{
	return m_IsClear;
}

void TitleScene::ResetFrag(){
	m_IsEnd = false;
	m_IsClear = false;
	m_IsGameEnd = false;
}

int TitleScene::Next() const {
	return m_NextScene;
}

void TitleScene::End() {
	gsDeleteSkinMesh(Mesh_TitlePlayer);
	gsDeleteTexture(Sprite_Title);
	gsDeleteTexture(Text_Texture);
	gsDeleteTexture(Sprite_Title);
	gsDeleteBGM(Title_BGM);
}

bool TitleScene::IsGameEnd() const{
	return m_IsGameEnd;
}

void TitleScene::StartUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::GameEnd;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::Option;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsClear = true;
		m_NextScene = (int)SceneManager::EachScene::CharacterEdit;
		m_IsEnd = true;
		return;
	}
}

void TitleScene::OptionUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::GameEnd;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::GameStart;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_NextScene = (int)SceneManager::EachScene::Option;
		m_IsEnd = true;
	}
}

void TitleScene::EndUpdate(float delta_time){
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveDown)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::GameStart;
		return;
	}
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SelectMoveUp)) {
		gsPlaySE(Change_SE);
		m_TextField = TextField::Option;
		return;
	}
	//ゲーム終了
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsGameEnd = true;
	}
}
