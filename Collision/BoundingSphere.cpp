#include "BoundingSphere.h"

const float RadiusRect{ 16.0f };

BoundingSphere::BoundingSphere(float radius, const GSvector3& center) : 
	m_Radius{ radius }, m_Center{ center }{}

//���s�ړ�
BoundingSphere BoundingSphere::Translate(const GSvector3& position)const {
	return BoundingSphere{ m_Radius,m_Center + position };
}

//���W�ϊ�
BoundingSphere BoundingSphere::Transform(const GSmatrix4& matrix)const {
	return BoundingSphere{ m_Radius * matrix.getScale().y,matrix.transform(m_Center) };
}

//�������Ă��邩
bool BoundingSphere::Intersects(const BoundingSphere& other) const{
	return gsCollisionSphereAndSphere(
		&m_Center, m_Radius, &other.m_Center, other.m_Radius) == GS_TRUE;
}


void BoundingSphere::Draw()const {
	//�R���C�_�\�ݒ�
	glPushMatrix();
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	glutWireSphere(m_Radius, RadiusRect, RadiusRect);
	glPopMatrix();
}