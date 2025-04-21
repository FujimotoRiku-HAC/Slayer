#ifndef STATE_H_
#define STATE_H_

template <typename entity_type>

class State {
public:

	//�R���X�g���N�^
	State(entity_type* owner):
		m_Owner{owner}{}
	//�f�X�g���N�^
	virtual ~State(){}
	//�J�n
	virtual void Enter()=0;
	//���s��
	virtual void Execute(float delta_time) = 0;
	//�`��
	virtual void Draw()const = 0;
	//�I���
	virtual void Exit()=0;
	//���b�Z�[�W
	virtual void OnMessage(const std::string& message, void* param) = 0;

protected: 
	entity_type* m_Owner;
};

#endif // !STATE_H_
