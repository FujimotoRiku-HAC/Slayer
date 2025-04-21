#ifndef NUMBER_MANAGER_H_
#define NUMBER_MANAGER_H_

class Number;

class NumberManager {
public:
	//�f�t�H���g�R���X�g���N�^
	NumberManager() = default;
	//�f�X�g���N�^
	~NumberManager();
	//�ǉ�
	void Add(Number* number);
	//�X�V
	void Update(float delta_time);
	//�A�N�^�[�̕`��
	void Draw()const;
	//���S���Ă���A�N�^�[�̍폜
	void Remove();
	//����
	void Clear();
	// �R�s�[�֎~
	NumberManager(const NumberManager& other) = delete;
	NumberManager& operator = (const NumberManager& other) = delete;

private:
	// �A�N�^�[���X�g
	std::list<Number*> m_Numbers;
};

#endif