#include "TitleScene.h"
#include "Field/Field.h"
#include "Light/Light.h"
#include "Camera/TitleCamera.h"
#include "Character/Player/PlayerAnim.h"
#include "SceneManager.h"
#include "Character/Door/Door.h"

#include <GSstandard_shader.h>

void TitleScene::Start() {
	//������
	ResetFrag();

	//������J�����O�L��
	gsEnable(GS_FRUSTUM_CULLING);
	// �f�t�H���g�V�F�[�_�[�̏������i���b�V���t�@�C����ǂݍ��ޑO�ɗL���ɂ���j
	gsInitDefaultShader();
	//�V���h�E�}�b�v�쐬
	gsCreateShadowMap(2, ShadowMapSize, GS_TRUE);
	//�V���h�E�}�b�v��K�p���鋗��
	gsSetShadowMapDistance(ShadowMapDis);
	//�J�X�P�[�h�V���h�E�}�b�v�̕������鋗��(�f�t�H���g��0.5)
	gsSetShadowMapCascadeLamda(ShadowMapCascade);
	//�V���h�E�̔Z����ݒ�
	gsSetShadowMapAttenuation(ShadowMapAttenuation);

	//�f�[�^�̓ǂݍ���
	gsLoadBGM(Title_BGM,				"Assets/Sound/BGM/title_bgm.ogg", GS_TRUE);
	gsLoadSE(Click_SE,					"Assets/Sound/SE/Other/click.wav", 1, GS_FALSE);
	gsLoadSE(Change_SE,					"Assets/Sound/SE/Other/change.wav", 1, GS_FALSE);
	//�f�[�^���[�h
	m_Data.DataLoad(					"Data/config_data.txt");
	//���b�V���ǂݍ���
	gsLoadSkinMesh(Mesh_TitlePlayer,	"Assets/Character/Player/title_player.mshb");
	gsLoadMesh(Mesh_Door,				"Assets/Character/Door/door.mshb");
	//�e�N�X�`��
	gsLoadTexture(Title_Slayer_Texture, "Assets/Texture/UI/Title/slayer.png");
	gsLoadTexture(Text_Texture,			"Assets/Texture/UI/Title/title_text.png");
	gsLoadTexture(Texture_Skybox,		"Assets/Skybox/skybox.dds");

	gsLoadOctree(Octree,				"Assets/Octree/octree.oct");
	gsLoadOctree(OctreeCollider,		"Assets/Collider/collider.oct");
	gsLoadLightmap(0,					"Assets/Light/lightmap.txt");
	gsLoadReflectionProbe(0,			"Assets/Ref/reflection_probe.txt");
	gsLoadAuxLight(0,					"Assets/Light/aux_light.txt");

	//�v���C���[
	m_Mesh = AnimatedMesh{ Mesh_TitlePlayer,TitlePlayerAnim::MotionTitle,true };
	// �����ʒu�̐ݒ�
	m_Transform.translate(TitlePlayerPos);
	m_Transform.rotate(GSvector3::up(), 0.f);
	// ���[���h�ϊ��s���ݒ�
	m_Mesh.Transform(m_Transform.localToWorldMatrix());

	//�t�B�[���h�N���X�̒ǉ�
	m_World.AddField(new Field{ Octree,OctreeCollider,Texture_Skybox });

	//�J�����N���X�̒ǉ�
	m_World.AddCamera(new TitleCamera{
		&m_World,SetCameraPos,SetCameraAt });

	//�h�A�ǉ�
	m_World.GetField()->Add(new Door{ &m_World,DoorPos,Mesh_Door,Mesh_Door });

	//���C�g�N���X�̒ǉ�
	m_World.AddLight(new Light{ &m_World });

	//���ʐݒ�
	gsSetVolumeBGM(m_Data.GetBGMValue());
	gsSetMasterVolumeSE(m_Data.GetSEValue());
	//BGM�̍Đ�
	gsPlayBGM(Title_BGM);

	m_TextField = TextField::GameStart;
}

void TitleScene::Update(float delta_time) {
	m_Mesh.Update(delta_time);
	// ���[���h�ϊ��s���ݒ�
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

	//�^�C�g���e�L�X�g�`��
	GSvector2 TitleTextPos{ ScreenWidth / 2.0f - TitleTextPosSet.x,ScreenHeight / 2.0f - TitleTextPosSet.y };
	GSrect TitleTextRect{ 0.f,0.f,TitleRectScale.x,TitleRectScale.y };
	GScolor color{ 0.f,0.f,0.f,0.f };
	//�Q�[���^�C�g���`��
	gsDrawSprite2D(Title_Slayer_Texture, &TitleTextPos, NULL, NULL, NULL, NULL, NULL);

	TitleTextPos = { ScreenWidth / 2.f + TitleRectScale.x,ScreenHeight / 2.f + TitleRectScale.y };

	for (int i = 0; i < TitleTextFieldNum; ++i) {
		if (i == m_TextField)color = { 0.f,0.f,1.f,1.0f };
		else color = { 1.f,1.f,1.f,1.0f };
		//�e�L�X�g�`��
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
	//�Q�[���I��
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::Decision)) {
		gsPlaySE(Click_SE);
		m_IsGameEnd = true;
	}
}
