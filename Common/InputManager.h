#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class InputManager {
public:
	enum InputType {
		Decision,			//決定
		Return,				//戻る
		Delete,				//消す
		Pose,				//ポーズボタン
		Back,				//バックボタン
		Attack,				//攻撃
		Ability,			//アビリティ
		Avoid,				//回避
		Ability1,			//アビリティ１
		Ability2,			//アビリティ２
		SelectMoveUp,		//選択バ―を上に
		SelectMoveDown,		//選択バ―を下に
		SelectMoveRight,	//選択バ―を右に
		SelectMoveLeft,		//選択バ―を左に
		ResetCamera,		//カメラリセット
		SkillSelect,		//セレクト

	};

private:

	enum {
		Trigger = 1,
		State	= 2,
		Detach  = 3,
		Short   = 4
	};

public:

	//インスタンス
	static InputManager Instance();
	//コンストラクタ
	InputManager();
	//左スティックの入力の受け取り
	GSvector2 LeftAxis();
	//右スティックの入力を受け取る
	GSvector2 RightAxis();

public:

	//押したとき
	bool IsBottonDown(InputType type);
	//押し続けているとき
	bool IsBottonState(InputType type);
	//離したとき
	bool IsBottonDetach(InputType type);
	//ボタンを押した瞬間
	bool IsBottonShortPress(InputType type);
	//長時間ボタンを押したとき
	bool IsBottonLongPress(InputType type);

private:

	//押した時間で種類を返す
	int IsBottonPressType(InputType type);

private:

	//インプット
	std::unordered_map<InputType, GSushort>m_InputLibrary;
	//ナンバー
	int m_Num = 0;
	//タイマー
	static float m_Timer;
};

#endif