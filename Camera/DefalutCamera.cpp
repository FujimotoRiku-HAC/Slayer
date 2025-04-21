#include "DefalutCamera.h"
#include "Field/Field.h"
#include "Math/Line.h"
#include "Character/Player/Player.h"
#include "Common/InputManager.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Door/Door.h"

DefalutCamera::DefalutCamera(IWorld* world,
	const GSvector3& position, const GSvector3& at) {
	//���[���h�ݒ�
	m_World = world;
	//�^�O�ݒ�
	m_Tag = st_CameraTag;
	//���O�ݒ�
	m_Name = st_Camera;
	//�����ʒu�ݒ�
	m_Transform.position(position);
	//�������_
	m_Transform.lookAt(at);
	//�ŏ��̏��
	m_State = State::Default;
}

void DefalutCamera::Update(float delta_time) {
	//�J�����̗v�f�̎��
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
	//�J�����G�t�F�N�g�\��
	SetCameraEffect();
	//�J�����V�F�C�N
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

	//���͐ݒ�
	m_Pitch -= InputManager::Instance().RightAxis().y;
	m_Yaw -= InputManager::Instance().RightAxis().x * 2;
	m_Pitch = CLAMP(m_Pitch, RangeX, RangeY);

	//�h�A�J������h�A�����b�N�I��
	if (m_Open && !m_IsDoorDie) {
		m_World->GetField()->HandleMessage(st_Message_IsOpen, nullptr);
		m_State = State::DoorLockOn;
		m_IsDoorDie = true;
		return;
	}

	//���b�N�I��
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::ResetCamera)) {
		std::vector<Actor*>enemys = m_World->FindActorWithTag(st_Enemy);
		if (enemys.empty())return;
		static_cast<Enemy*>(enemys.at(0))->DrawTarget();
		m_State = State::EnemyLockOn;
		return;
	}

	//�������݃��Z�b�g
	if (InputManager::Instance().IsBottonShortPress(InputManager::InputType::ResetCamera)) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
	}

	//�����_�̈ʒu�����߂�(�v���C���[�̓���)
	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	//���_�̈ʒu�����߂�
	GSvector3 position = at + GSquaternion::euler(m_Pitch, m_Yaw, 0.f) * PlayerOffset;

	//�t�B�[���h�Ɠ���������
	Line line{ at,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//�X���[�X�̕�Ԃ�����
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//���_�̈ʒu
	m_Transform.position(position);
	//�����X�ݒ�
	m_Transform.lookAt(at);
}

void DefalutCamera::LockOnUpdate(float delta_time){
	//�v���C���[�̌���
	Actor* player = m_World->FindActor(st_Player);
	if (player == nullptr)return;

	//�h�A�����b�N�I��
	if (m_Open && !m_IsDoorDie) {
		m_World->OnMessage(st_Message_IsOpen, nullptr);
		m_State = State::DoorLockOn;
		return;
	}

	//�G�̐�������
	std::vector<Actor*>enemys = m_World->FindActorWithTag(st_Enemy);

	//�G�����Ȃ�������߂�
	if (enemys.empty()) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_State = State::Default;
		return;
	}

	//�T�C�Y�𒴂�����0
	if (static_cast<int>(enemys.size()) <= m_EnemyNum) {
		m_EnemyNum = 0;
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
	}

	auto enemy = static_cast<Enemy*>(enemys.at(m_EnemyNum));

	//�J�������Z�b�g
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::ResetCamera)) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_EnemyNum = -1;
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
		m_EnemyNum = 0;
		m_State = State::Default;
		return;
	}

	//�^�Q�ύX
	if (InputManager::Instance().IsBottonDown(InputManager::InputType::SkillSelect)) {
		m_EnemyNum++;
		if (m_EnemyNum >= static_cast<int>(enemys.size())) {
			m_EnemyNum = 0;
		}
		static_cast<Enemy*>(enemys.at(m_EnemyNum))->DrawTarget();
		m_World->FindActor(st_Player)->HandleMessage(st_Message_Target, &m_EnemyNum);
	}

	//�����𒲂ׂ�
	GSvector3 enemyToPlayer = player->Transform().position() - enemy->Transform().position();
	//���K������
	enemyToPlayer.normalize();

	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	GSvector3 position = at + enemyToPlayer * Radius;

	Line line{ player->Transform().position() + ReferencePointOffset,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//�X���[�X�_���v�ɂ�銊�炩�ȕ��
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//���_�̈ʒu��ݒ�
	m_Transform.position(position);
	//�����_��ݒ�i�����_�̕����Ɍ�����ς���j
	m_Transform.lookAt(at);
}

void DefalutCamera::DoorLockOnUpdate(float delta_time){
	Actor* player = m_World->FindActor(st_Player);
	Actor* door = m_World->GetField()->FindActor(st_Door);

	//�J���I�������ʏ�ɖ߂�
	if (!m_Open) {
		m_Yaw = player->Transform().eulerAngles().y;
		m_Pitch = 0.f;
		m_State = State::Default;
		return;
	}
	if (player == nullptr || door == nullptr)return;

	//�����𒲂ׂ�
	GSvector3 doorToPlayer = player->Transform().position() - door->Transform().position();
	//���K������
	doorToPlayer.normalize();

	GSvector3 at = player->Transform().position() + ReferencePointOffset;
	GSvector3 position = at + doorToPlayer * Radius;

	//�t�B�[���h�ɓ��������Ƃ��̏���
	Line line{ player->Transform().position() + ReferencePointOffset,position };
	GSvector3 intersects;
	if (m_World->GetField()->Collide(line, &intersects)) {
		position = intersects;
	}

	//�X���[�X�_���v�ɂ�銊�炩�ȕ��
	position = GSvector3::smoothDamp(m_Transform.position(), position, m_Velocity,
		SmoothTime, MaxSpeed, delta_time);

	//���_�̈ʒu��ݒ�
	m_Transform.position(position);
	//�����_��ݒ�i�����_�̕����Ɍ�����ς���j
	m_Transform.lookAt(at);
}

void DefalutCamera::ShakeCamera(float delta_time) {
	if (!m_IsShake)return;
	//�����_���ŗh�炷
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
		// �G�t�F�N�g�̊J�n
		m_SpeedLineHandle = gsPlayEffect(Effect_CounterLines, nullptr);
		//�J���[�w��
		gsSetEffectColor(m_SpeedLineHandle, &CameraEffectColor);
		m_IsEffect = true;
		return;
	}
	if (!static_cast<Player*>(m_World->FindActor(st_Player))->IsJustAttack()) {
		// �G�t�F�N�g�̏I��
		gsStopEffect(m_SpeedLineHandle);
	}

	// �G�t�F�N�g�̈ʒu����ʂ̒��S�ɗ���悤�ɂ���
	const GSvector3 pos = m_Transform.position() + m_Transform.forward();
	gsSetEffectPosition(m_SpeedLineHandle, &pos);
}
