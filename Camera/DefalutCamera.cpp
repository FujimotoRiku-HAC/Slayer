#include "DefalutCamera.h"
#include "Field/Field.h"
#include "Math/Line.h"
#include "Character/Player/Player.h"
#include "Common/InputManager.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Door/Door.h"

DefalutCamera::DefalutCamera(IWorld* world,
	const GSvector3& position, const GSvector3& at) {
	//ワールド設定
	m_World = world;
	//タグ設定
	m_Tag = st_CameraTag;
	//名前設定
	m_Name = st_Camera;
	//初期位置設定
	m_Transform.position(position);
	//初期視点
	m_Transform.lookAt(at);
	//最初の状態
	m_State = State::Default;
}

void DefalutCamera::Update(float delta_time) {
	//カメラの要素の種類
	switch (m_State)
	{
	case DefalutCamera::State::Default:
		DefaultUpdate(delta_time);
		break;
	case DefalutCamera::State::EnemyLockOn:
		LockOnUpdate(delta_time);
		break;
	case DefalutCamera::State::DoorLockOn:
		DoorLockOnUpdate(delta_time);
		break;
	case DefalutCamera::State::Reset:
		break;
	default:
		break;
	}
	//カメラエフェクト表示
	SetCameraEffect();
	//カメラシェイク
	ShakeCamera(delta_time);
}

void DefalutCamera::Draw()const {
	GSvector3 eye = m_Transform.position();
	GSvector3 at = eye + m_Transform.forward();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
	   eye.x , eye.y, eye.z,
		at.x ,  at.y,  at.z,
		0.f,   1.f,  0.f
	);
}

void DefalutCamera::HandleMessage(const std::string& message, void* param){
	if (message == st_Message_OpenDoor) m_Open = true;
	if (message == st_Message_Die) m_Open = false;
}

void DefalutCamera::Shake(){
	m_IsShake = true;
	m_ShakeTime = ShakeTime;
}

void DefalutCamera::ShakeOff(){
	m_IsShake = false;
}

void DefalutCamera::DefaultUpdate(float delta_time){
	Actor* player = m_World->FindActor(st_Player);
	if (player == nullptr)return;

	//入力設定
	m_Pitch -= InputManager::Instance().RightAxis().y;
	m_Yaw -= InputManager::Instance().RightAxis().x * 2;
	m_Pitch = CLAMP(m_Pitch, RangeX, RangeY);

	//ドア開いたらドアをロックオン
	if (m_Open && !m_IsDoorDie) {
		m_World->GetField()->HandleMessage(st_Message_IsOpen, nullptr);
		m_State = State::DoorLockOn;
		m_IsDoorDie = true;
		return;
	}

	//ロックオン
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::ResetCamera)) {
		std::vector<Actor*>enemys = m_World->FindActorWithTag(st_Enemy);
		if (enemys.empty())return;
		static_cast<Enemy*>(enemys.at(0))->DrawTarget();
		m_State = State::EnemyLockOn;
		return;
	}

	//押し込みリセット
	if (InputManager::Instance().IsBottonShortPress(InputManager::InputType::ResetCamera)) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
	}

	//注視点の位置を求める(プレイヤーの頭部)
	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	//視点の位置を求める
	GSvector3 position = at + GSquaternion::euler(m_Pitch, m_Yaw, 0.f) * PlayerOffset;

	//フィールドと当たったら
	Line line{ at,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//スムースの補間をする
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//視点の位置
	m_Transform.position(position);
	//注視店設定
	m_Transform.lookAt(at);
}

void DefalutCamera::LockOnUpdate(float delta_time){
	//プレイヤーの検索
	Actor* player = m_World->FindActor(st_Player);
	if (player == nullptr)return;

	//ドアをロックオン
	if (m_Open && !m_IsDoorDie) {
		m_World->OnMessage(st_Message_IsOpen, nullptr);
		m_State = State::DoorLockOn;
		return;
	}

	//敵の数を見る
	std::vector<Actor*>enemys = m_World->FindActorWithTag(st_Enemy);

	//敵がいなかったら戻す
	if (enemys.empty()) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_State = State::Default;
		return;
	}

	//サイズを超えたら0
	if (static_cast<int>(enemys.size()) <= m_EnemyNum) {
		m_EnemyNum = 0;
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
	}

	auto enemy = static_cast<Enemy*>(enemys.at(m_EnemyNum));

	//カメラリセット
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::ResetCamera)) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_EnemyNum = -1;
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
		m_EnemyNum = 0;
		m_State = State::Default;
		return;
	}

	//タゲ変更
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SkillSelect)) {
		m_EnemyNum++;
		if (m_EnemyNum >= static_cast<int>(enemys.size())) {
			m_EnemyNum = 0;
		}
		static_cast<Enemy*>(enemys.at(m_EnemyNum))->DrawTarget();
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
	}

	//長さを調べる
	GSvector3 enemyToPlayer = player->Transform().position() - enemy->Transform().position();
	//正規化する
	enemyToPlayer.normalize();

	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	GSvector3 position = at + enemyToPlayer * Radius;

	Line line{ player->Transform().position() + ReferencePointOffset,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//スムースダンプによる滑らかな補間
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//視点の位置を設定
	m_Transform.position(position);
	//注視点を設定（注視点の方向に向きを変える）
	m_Transform.lookAt(at);
}

void DefalutCamera::DoorLockOnUpdate(float delta_time){
	Actor* player = m_World->FindActor(st_Player);
	Actor* door = m_World->GetField()->FindActor(st_Door);

	//開き終わったら通常に戻る
	if (!m_Open) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_State = State::Default;
		return;
	}
	if (player == nullptr || door == nullptr)return;

	//長さを調べる
	GSvector3 doorToPlayer = player->Transform().position() - door->Transform().position();
	//正規化する
	doorToPlayer.normalize();

	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	GSvector3 position = at + doorToPlayer * Radius;

	//フィールドに当たったときの処理
	Line line{ player->Transform().position() + ReferencePointOffset,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//スムースダンプによる滑らかな補間
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//視点の位置を設定
	m_Transform.position(position);
	//注視点を設定（注視点の方向に向きを変える）
	m_Transform.lookAt(at);
}

void DefalutCamera::ShakeCamera(float delta_time) {
	if (!m_IsShake)return;
	//ランダムで揺らす
	float a = gsRandf(-RandomShakeRange, RandomShakeRange);
	float b = gsRandf(-RandomShakeRange, RandomShakeRange);
	m_ShakeTime -= delta_time;

	GSvector3 position = m_Transform.position();

	position.x += a;
	position.y += b;

	m_Transform.position(position);

	if (m_ShakeTime <= 0.f) {
		m_IsShake = false;
	}
}

void DefalutCamera::SetCameraEffect(){
	if (static_cast<Player*>(m_World->FindActor(st_Player))->IsJustAttack() && !m_IsEffect) {
		// エフェクトの開始
		m_SpeedLineHandle = gsPlayEffect(Effect_CounterLines, nullptr);
		//カラー指定
		gsSetEffectColor(m_SpeedLineHandle, &CameraEffectColor);
		m_IsEffect = true;
		return;
	}
	if (!static_cast<Player*>(m_World->FindActor(st_Player))->IsJustAttack()) {
		// エフェクトの終了
		gsStopEffect(m_SpeedLineHandle);
	}

	// エフェクトの位置を画面の中心に来るようにする
	const GSvector3 pos = m_Transform.position() + m_Transform.forward();
	gsSetEffectPosition(m_SpeedLineHandle, &pos);
}
