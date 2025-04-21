#include "World.h"
#include "Field/Field.h"
#include "Actor/Actor.h"

//�f�X�g���N�^
World::~World() {
	Clear();
}

//�X�V
void World::Update(float delta_time) {
	//�t�B�[���h�X�V
	m_Field->Update(delta_time);
	//�A�N�^�[�X�V
	m_Actors.Update(delta_time * m_ScaleTimer);
	//�i���o�[�X�V
	m_Numbers.Update(delta_time);
	//�A�N�^�[�̏Փ�
	m_Actors.Collide();
	//�A�N�^�[�̒x���X�V
	m_Actors.LateUpdate(delta_time);
	//�A�N�^�[����
	m_Actors.Remove();
	//�i���o�[�X�V
	m_Numbers.Remove();
	//�J�����̍X�V
	m_Camera->Update(delta_time);
	//���C�g�̍X�V
	m_Light->Update(delta_time);
	//�G�t�F�N�g�̍X�V����
	gsUpdateEffect(delta_time);
}

//�`��
void World::Draw() const {
	//�J�����̐ݒ�
	m_Camera->Draw();
	//�G�t�F�N�g�p�̃J������ݒ�
	gsSetEffectCamera();
	//���C�g�̐ݒ�
	m_Light->Draw();
	//�V���h�E�}�b�v�`��
	gsDrawShadowMap(World::ShadowMapCallback, (void*)this);
	//�t�B�[���h�`��
	m_Field->Draw();
	//�A�N�^�[�`��
	m_Actors.Draw();
	//�������A�N�^�[�̕`��
	m_Actors.DrawTransparent();
	//�G�t�F�N�g�̕`��
	gsDrawEffect();
	//GUI�`��
	m_Actors.DrawGui();
	//�i���o�[�`��
	m_Numbers.Draw();
}

//����
void World::Clear() {
	//�A�N�^�[����
	m_Actors.Clear();
	//�i���o�[����
	m_Numbers.Clear();
	//�J��������
	delete m_Camera;
	m_Camera = nullptr;
	//���C�g����
	delete m_Light;
	m_Light = nullptr;
	//�t�B�[���h����
	delete m_Field;
	m_Field = nullptr;
}

//���b�Z�[�W���M
void World::OnMessage(const std::string& message, void* param) {
	m_Actors.OnMessage(message, param);
}

//�J�����̒ǉ�
void World::AddCamera(Actor* camera) {
	delete m_Camera;
	m_Camera = camera;
}

//���C�g�̒ǉ�
void World::AddLight(Actor* light) {
	delete m_Light;
	m_Light = light;
}

//�t�B�[���h�ǉ�
void World::AddField(Field* field) {
	delete m_Field;
	m_Field = field;
}

//�A�N�^�[�ǉ�
void World::AddActor(Actor* actor) {
	m_Actors.Add(actor);
}

void World::AddNumber(Number* number){
	m_Numbers.Add(number);
}

void World::SetClearFrag() {
	m_ClearFrag = true;
}

void World::SetGameOverFrag() {
	m_GameOverFrag = true;
}

void World::PlaySlowTimer(float time){
	m_ScaleTimer = time;
}

void World::DefaultTime(){
	m_ScaleTimer = 1.f;
}

//�V���h�E�}�b�v�̕`��p�̊֐�
void World::ShadowMapCallback(void* param, const GSmatrix4*, const GSmatrix4*) {
	World* self = (World*)param;
	//�V���h�E�}�b�v�̓A�N�^�[�̂�
	self->m_Actors.Draw();
}

//�A�N�^�[����Ԃ�
int World::CountActor() const {
	return m_Actors.Count();
}

//�w�肵���^�O�������A�N�^�[����Ԃ�
int World::CountActorWithTag(const std::string& tag) const {
	return m_Actors.CountWithTag(tag);
}

bool World::IsClear() const{
	return m_ClearFrag;
}

bool World::IsGameOver() const{
	return m_GameOverFrag;
}

//�A�N�^�[����
Actor* World::FindActor(const std::string& name) const {
	return m_Actors.Find(name);
}

//�w�肵���^�O�������A�N�^�[�̌���
std::vector<Actor*>World::FindActorWithTag(const std::string& tag) const {
	return m_Actors.FindWithTag(tag);
}

//�J�����̎擾
Actor* World::GetCamera() {
	return m_Camera;
}

//���C�g�̎擾
Actor* World::GetLight() {
	return m_Light;
}

//�t�B�[���h�擾
Field* World::GetField() {
	return m_Field;
}