#include "World.h"
#include "Field/Field.h"
#include "Actor/Actor.h"

//デストラクタ
World::~World() {
	Clear();
}

//更新
void World::Update(float delta_time) {
	//フィールド更新
	m_Field->Update(delta_time);
	//アクター更新
	m_Actors.Update(delta_time * m_ScaleTimer);
	//ナンバー更新
	m_Numbers.Update(delta_time);
	//アクターの衝突
	m_Actors.Collide();
	//アクターの遅延更新
	m_Actors.LateUpdate(delta_time);
	//アクター消去
	m_Actors.Remove();
	//ナンバー更新
	m_Numbers.Remove();
	//カメラの更新
	m_Camera->Update(delta_time);
	//ライトの更新
	m_Light->Update(delta_time);
	//エフェクトの更新処理
	gsUpdateEffect(delta_time);
}

//描画
void World::Draw() const {
	//カメラの設定
	m_Camera->Draw();
	//エフェクト用のカメラを設定
	gsSetEffectCamera();
	//ライトの設定
	m_Light->Draw();
	//シャドウマップ描画
	gsDrawShadowMap(World::ShadowMapCallback, (void*)this);
	//フィールド描画
	m_Field->Draw();
	//アクター描画
	m_Actors.Draw();
	//半透明アクターの描画
	m_Actors.DrawTransparent();
	//エフェクトの描画
	gsDrawEffect();
	//GUI描画
	m_Actors.DrawGui();
	//ナンバー描画
	m_Numbers.Draw();
}

//消去
void World::Clear() {
	//アクター消去
	m_Actors.Clear();
	//ナンバー消去
	m_Numbers.Clear();
	//カメラ消去
	delete m_Camera;
	m_Camera = nullptr;
	//ライト消去
	delete m_Light;
	m_Light = nullptr;
	//フィールド消去
	delete m_Field;
	m_Field = nullptr;
}

//メッセージ送信
void World::OnMessage(const std::string& message, void* param) {
	m_Actors.OnMessage(message, param);
}

//カメラの追加
void World::AddCamera(Actor* camera) {
	delete m_Camera;
	m_Camera = camera;
}

//ライトの追加
void World::AddLight(Actor* light) {
	delete m_Light;
	m_Light = light;
}

//フィールド追加
void World::AddField(Field* field) {
	delete m_Field;
	m_Field = field;
}

//アクター追加
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

//シャドウマップの描画用の関数
void World::ShadowMapCallback(void* param, const GSmatrix4*, const GSmatrix4*) {
	World* self = (World*)param;
	//シャドウマップはアクターのみ
	self->m_Actors.Draw();
}

//アクター数を返す
int World::CountActor() const {
	return m_Actors.Count();
}

//指定したタグ名を持つアクター数を返す
int World::CountActorWithTag(const std::string& tag) const {
	return m_Actors.CountWithTag(tag);
}

bool World::IsClear() const{
	return m_ClearFrag;
}

bool World::IsGameOver() const{
	return m_GameOverFrag;
}

//アクター検索
Actor* World::FindActor(const std::string& name) const {
	return m_Actors.Find(name);
}

//指定したタグ名を持つアクターの検索
std::vector<Actor*>World::FindActorWithTag(const std::string& tag) const {
	return m_Actors.FindWithTag(tag);
}

//カメラの取得
Actor* World::GetCamera() {
	return m_Camera;
}

//ライトの取得
Actor* World::GetLight() {
	return m_Light;
}

//フィールド取得
Field* World::GetField() {
	return m_Field;
}