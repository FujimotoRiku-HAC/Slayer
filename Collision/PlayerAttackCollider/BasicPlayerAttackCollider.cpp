#include "BasicPlayerAttackCollider.h"

BasicPlayerAttackCollider::BasicPlayerAttackCollider(IWorld* world, const BoundingSphere& collider, const std::string& name, const std::string& tag, const std::string& owner_tag, const int damage,const int stan_damage, const float lifespan, const float delay){
	//���[���h�ݒ�
	m_World = world;
	//�^�O���ݒ�
	m_Tag = tag;
	//�e�̃^�O���ݒ�
	m_OwnerTag = owner_tag;
	//���O�ݒ�
	m_Name = name;
	//�_���[�W��
	m_Damage = damage;
	//�X�^���_���[�W��
	m_StanValue = stan_damage;
	//�����ݒ�
	m_LifespanTimer = lifespan;
	//�x������
	m_DelayTimer = delay;
	//�e�̏�����
	m_Collider = { BoundingSphere(collider.m_Radius) };
	//���W������
	m_Transform.position(collider.m_Center);
	//�Փ˔��薳��
	m_EnableCollider = false;
}

void BasicPlayerAttackCollider::Update(float delta_time){
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

void BasicPlayerAttackCollider::Draw() const{}

void BasicPlayerAttackCollider::React(Actor& other){
	//�����Ɠ����^�O�܂��́A�I�[�i�[�Ɠ����^�O�͏Փ˂��Ȃ�
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
	Die();
}
