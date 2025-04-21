#ifndef STATE_H_
#define STATE_H_

template <typename entity_type>

class State {
public:

	//コンストラクタ
	State(entity_type* owner):
		m_Owner{owner}{}
	//デストラクタ
	virtual ~State(){}
	//開始
	virtual void Enter()=0;
	//実行中
	virtual void Execute(float delta_time) = 0;
	//描画
	virtual void Draw()const = 0;
	//終わり
	virtual void Exit()=0;
	//メッセージ
	virtual void OnMessage(const std::string& message, void* param) = 0;

protected: 
	entity_type* m_Owner;
};

#endif // !STATE_H_
