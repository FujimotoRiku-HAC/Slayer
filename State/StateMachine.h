#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "State.h"

template <class entity_type>
class StateMachine {
public:
	//�R���X�g���N�^
	StateMachine(){}

	virtual ~StateMachine(){
		Clear();
	}

	void Start() {
		if (m_GlobalState) m_GlobalState->Enter();

		if (m_CurrentState)m_CurrentState->Enter();
	}

	//�X�V
	void Update(float delta_time)const {
		//�O���[�o���X�e�[�g�������
		if (m_GlobalState) m_GlobalState->Execute(delta_time);
		//���݂̃X�e�[�g�Ɠ���
		if (m_CurrentState) m_CurrentState->Execute(delta_time);
	}

	//�`��
	void Draw()const {
		if (m_GlobalState)m_GlobalState->Draw();
		if (m_CurrentState)m_CurrentState->Draw();
	}

	void Clear() {
		std::ranges::for_each(m_StateList,
			[](auto& state) {delete state.second; });
		m_StateList.clear();
	}

	void End() {
		if (m_GlobalState)m_GlobalState->Exit();
		if(m_CurrentState)m_CurrentState->Exit();
	}

	//���b�Z�[�W�̂����
	void HandleMessage(const std::string& message)const {
		if (m_CurrentState && m_CurrentState->OnMessage(message)) {
			return true;
		}
		if (m_GlobalState && m_GlobalState->OnMessage(message)) {
			return true;
		}
		return false;
	}

	//���������Ɏg��
	void SetCurrentState(int s) {
		m_CurrentState = m_StateList[s];
		m_CurrentID = s;
		Start();
	}
	void SetGlobalState(int s) {
		m_GlobalState = m_StateList[s];
		m_CurrentID = s;
		Start();
	}
	void SetPreviousState(int s) {
		m_PreviousState = s;
	}

	void AddState(int newState, State<entity_type>* state) {
		m_StateList[newState] = state;
	}

	//�X�e�[�g�ύX
	void Change_State(int newState,bool restate = false) {
		if (m_StateList.find(newState) == m_StateList.end())return;
		if (m_CurrentState) {
			m_PrevID = m_CurrentID;
			//�ȑO�̃X�e�[�g���L�^����
			m_PreviousState = m_CurrentState;
			//�X�e�[�g�̏I�����Ă�
			m_CurrentState->Exit();
		}
		//�X�e�[�g�ύX
		m_CurrentID = newState;
		//���̃X�e�[�g
		m_CurrentState = m_StateList[newState];
		//�J�n���\�b�h���Ă�
		m_CurrentState->Enter();
	}

	//�ȑO�̃X�e�[�g�ɕύX
	void RevertToPreviousState() {
		Change_State(m_PrevID);
	}
	//�X�e�[�g�ƃp�����[�^�������Ă��邩
	bool IsInState(int st)const {
		return m_CurrentID == st;
	}
public:
	State<entity_type>* CurrentState()const { return m_CurrentID; }
	State<entity_type>* GlobalState()const { return m_GlobalState; }
	State<entity_type>* PreviousState()const { return m_PrevID; }
private:
	//
	std::unordered_map<int, State<entity_type>*> m_StateList;
	//���݂̃X�e�[�g
	State<entity_type>* m_CurrentState{ nullptr };
	//���O�̃X�e�[�g�̋L�^
	State<entity_type>* m_PreviousState{ nullptr };
	//�X�V���邽�тɌĂ΂��
	State<entity_type>* m_GlobalState{ nullptr };

	int m_CurrentID{ -1 };
	int m_PrevID{ -1 };
};

#endif