#include "TitleCamera.h"
#include "Field/Field.h"
#include "Math/Line.h"

//�R���X�g���N�^
TitleCamera::TitleCamera(IWorld* world, const GSvector3& position, const GSvector3& at) {
	//���[���h��ݒ�
	m_World = world;
	//�^�O�̐ݒ�
	m_Tag = st_CameraTag;
	//���O�̐ݒ�
	m_Name = st_Camera;
	//�n�_�̈ʒu��ݒ�
	m_Transform.position(position);
	//�����_��ݒ�(�����X�̕����Ɍ�����ς���)
	m_Transform.lookAt(at);
}

//�`��
void TitleCamera::Draw() const {
	//���_�̈ʒu
	GSvector3 eye = m_Transform.position();
	//�����_�̈ʒu
	GSvector3 at = eye + m_Transform.forward();
	//�J�����̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eye.x, eye.y, eye.z,
		at.x, at.y, at.z,
		0.f, 1.f, 0.f
	);
}