#ifndef ISCENE_H_
#define ISCENE_H_

//�V�[�����ۃC���^�[�t�F�[�X
class IScene {
public:
	//���z�f�X�g���N�^
	virtual ~IScene() = default;
	//�J�n
	virtual void Start() = 0;
	//�X�V
	virtual void Update(float delta_time) = 0;
	//�`��
	virtual void Draw() const = 0;
	//�I�����Ă��邩
	virtual bool IsEnd() const = 0;
	//�V�[���̍폜
	virtual bool StackClear()const = 0;
	//
	virtual void ResetFrag() = 0;
	//���̃V�[�������c��
	virtual int Next() const = 0;
	//�I��
	virtual void End() = 0;
	//�Q�[���I��
	virtual bool IsGameEnd()const = 0;
};

#endif
