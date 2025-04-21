#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

//���E���N���X
class BoundingSphere {
public:

	//�R���X�g���N�^
	BoundingSphere(float redius = 0.0f, const GSvector3& center = GSvector3{ 0.0f,0.0f,0.0f });
	//���s�ړ�
	BoundingSphere Translate(const GSvector3& position)const;
	//���W�ϊ�
	BoundingSphere Transform(const GSmatrix4& matrix)const;
	//�d�Ȃ��Ă��邩
	bool Intersects(const BoundingSphere& other) const;
	//�f�o�b�O�\��
	void Draw() const;

public:
	//���a
	float m_Radius{ 0.0f };
	//���S���W
	GSvector3 m_Center{ 0.0f,0.0f,0.0f };
};

#endif