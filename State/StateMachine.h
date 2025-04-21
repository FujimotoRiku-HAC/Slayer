#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "State.h"

template <class entity_type>
class StateMachine {
public:
	//コンストラクタ
	StateMachine(){}

	virtual ~StateMachine(){
		Clear();
	}

	void Start() {
		if (m_GlobalState) m_GlobalState->Enter();

		if (m_CurrentState)m_CurrentState->Enter();
	}

	//更新
	void Update(float delta_time)const {
		//グローバルステートがあれば
		if (m_GlobalState) m_GlobalState->Execute(delta_time);
		//現在のステートと同じ
		if (m_CurrentState) m_CurrentState->Execute(delta_time);
	}

	//描画
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

	//メッセージのやり取り
	void HandleMessage(const std::string& message)const {
		if (m_CurrentState && m_CurrentState->OnMessage(message)) {
			return true;
		}
		if (m_GlobalState && m_GlobalState->OnMessage(message)) {
			return true;
		}
		return false;
	}

	//初期化時に使う
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

	//ステート変更
	void Change_State(int newState,bool restate = false) {
		if (m_StateList.find(newState) == m_StateList.end())return;
		if (m_CurrentState) {
			m_PrevID = m_CurrentID;
			//以前のステートを記録する
			m_PreviousState = m_CurrentState;
			//ステートの終了を呼ぶ
			m_CurrentState->Exit();
		}
		//ステート変更
		m_CurrentID = newState;
		//次のステート
		m_CurrentState = m_StateList[newState];
		//開始メソッドを呼ぶ
		m_CurrentState->Enter();
	}

	//以前のステートに変更
	void RevertToPreviousState() {
		Change_State(m_PrevID);
	}
	//ステートとパラメータがあっているか
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
	//現在のステート
	State<entity_type>* m_CurrentState{ nullptr };
	//直前のステートの記録
	State<entity_type>* m_PreviousState{ nullptr };
	//更新するたびに呼ばれる
	State<entity_type>* m_GlobalState{ nullptr };

	int m_CurrentID{ -1 };
	int m_PrevID{ -1 };
};

#endif