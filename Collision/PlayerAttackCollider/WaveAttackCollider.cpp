#include "WaveAttackCollider.h"
#include "Character/Player/Player.h"
#include "Math/Line.h"
#include "Field/Field.h"

const float LifeSpan{ 60.0f * 5.0f };
const float Speed{ 1.5f };

WaveAttackCollider::WaveAttackCollider(IWorld* world,const BoundingSphere& collider, const GSvector3& velocity, int damage,int stan_damage, std::string name) {
	//���[���h�ݒ�
	m_World = world;
	//�^�O�ݒ�
	m_Tag = st_PlayerAttackTag;
	//���O�ݒ�
	m_Name = name;
	//�f�B���C
	m_DelayTimer = 0.f;
	//�_���[�W��
	m_Damage = damage;
	//�X�^���|�C���g
	m_StanValue = stan_damage;
	//����
	m_LifespanTimer = LifeSpan;
	//�R���C�_�\�̑傫���ݒ�
	m_Collider = BoundingSphere{ collider.m_Radius };
	//�����ʒu
	m_Transform.position(collider.m_Center);
	//�ړ��ʐݒ�
	m_Velocity = velocity;
	//��]������
	m_Transform.rotation(GSquaternion::lookRotation(velocity));
	//�G�t�F�N�g
	m_EffectHandle = gsPlayEffect(Effect_Arrow, &collider.m_Center);
}

void WaveAttackCollider::Update(float delta_time){
	if (m_LifespanTimer <= 0.f) {
		gsStopEffect(m_EffectHandle);
		Die();
		return;
	}
	//���������Z
	m_LifespanTimer -= delta_time;

	//�t�B�[���h�Ƃ̏Փ˔���
	Line line;
	line.start = m_Transform.position();
	line.end = m_Transform.position() + m_Velocity * delta_time;
	GSvector3 intersect;
	//�t�B�[���h�ɓ��������玀�S
	if (m_World->GetField()->Collide(line, &intersect)) {
		m_Transform.position(intersect);
		gsStopEffect(m_EffectHandle);
		Die();
		return;
	}

	m_Transform.translate(m_Velocity * delta_time, GStransform::Space::World);
	// �G�t�F�N�g�Ɏ��g�̃��[���h�ϊ��s���ݒ�
	GSmatrix4 world = m_Transform.localToWorldMatrix();
	gsSetEffectMatrix(m_EffectHandle, &world); // ���[���h�ϊ��s���ݒ�
}

void WaveAttackCollider::Draw() const{}


void WaveAttackCollider::React(Actor& other) {
	gsStopEffect(m_EffectHandle);
	if (other.Tag() == Tag() || other.Tag() == m_OwnerTag)return;
	Die();
}
