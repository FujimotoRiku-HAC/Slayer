#ifndef FIELD_H_
#define FIELD_H_

#include "FieldActorManager.h"

class Ray;
class Line;
class BoundingSphere;

//�t�B�[���h�N���X
class Field {
public:

	//�R���X�g���N�^
	Field(GSuint octree, GSuint collider, GSuint skybox);
	//�f�X�g���N�^
	~Field();
	//�A�N�^�[����
	Actor* FindActor(const std::string& name) const;

public:

	//�X�V
	void Update(float delta_time);
	//�`��
	void Draw() const;
	//�A�N�^�[�`��
	void DrawActors()const;
	//�t�B�[���h�p�A�N�^�[�̒ǉ�
	void Add(Actor* actor);
	//�t�B�[���h�p�A�N�^�[�̏���
	void Clear();
	//���b�Z�[�W����
	void HandleMessage(const std::string& message, void* param);

public:

	//�����Ƃ̏Փ˔���
	bool Collide(const Line& line,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr,
		Actor** actor = nullptr)const;

	//���C�Ƃ̏Փ˔���
	bool Collide(const Ray& ray, float max_distance,
		GSvector3* intersect = nullptr, GSplane* plane = nullptr,
		Actor** actor = nullptr)const;

	//���̂Ƃ̏Փ˔���
	bool Collide(const BoundingSphere& sphere, GSvector3* center = nullptr,
		Actor** actor = nullptr)const;

	//�R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

private:
	//�`��p�I�N�g���[
	GSuint m_Octree;
	//�Փ˔���p�I�N�g���[
	GSuint m_Collider;
	//�X�J�C�{�b�N�X
	GSuint m_Skybox;
	//�A�N�^�[
	FieldActorManager m_Actors;
};

#endif
