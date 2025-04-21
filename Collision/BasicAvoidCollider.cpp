#include "BasicAvoidCollider.h"

BasicAvoidCollider::BasicAvoidCollider(IWorld* world, const BoundingSphere& collider,float lifetime){
	//���[���h�ݒ�
	m_World = world;
	//�^�O���ݒ�
	m_Tag = st_AvoidTag;
	//�e�̃^�O���ݒ�
	m_OwnerTag = st_Enemy;
	//���O�ݒ�
	m_Name = st_Avoid;
	//����
	m_LifespanTimer = lifetime;
	//�e�̏�����
	m_Collider = { BoundingSphere(collider.m_Radius) };
	//���W������
	m_Transform.position(collider.m_Center);
	//�Փ˔��薳��
	m_EnableCollider = false;
}

void BasicAvoidCollider::Update(float delta_time){
	//�x�����Ԃ��߂�����Փ˔����L���ɂ���
	if (m_DelayTimer <= 0.f) {
		m_EnableCollider = true;
		//�������s�����玀�S
		if (m_LifespanTimer <= 0.f) {
			Die();
		}
		//�����̍X�V
		m_LifespanTimer -= delta_time;
	}
	//�x�����Ԃ̍X�V
	m_DelayTimer -= delta_time;
}

void BasicAvoidCollider::Draw() const{}

void BasicAvoidCollider::React(Actor& other){
	//�����Ɠ����^�O�܂��́A�I�[�i�[�Ɠ����^�O�͏Փ˔��肵�Ȃ�
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
}
