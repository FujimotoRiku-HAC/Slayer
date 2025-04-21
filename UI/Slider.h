#ifndef SLIDER_H_
#define SLIDER_H_

class Slider {
public:

	//�R���X�g���N�^
	Slider(const GSvector2& pos, const GSvector2& scale, float min, float max,
		const GScolor& color = GScolor{ 0.0f,0.0f,0.0f,1.0f });
	Slider(const GSvector3& pos, const GSvector2& scale, float min, float max,
		const GScolor& color = GScolor{ 0.0f,0.0f,0.0f,1.0f });
	//�f�X�g���N�^
	~Slider();
	//�`��
	void Draw()const;
	//�ݒ�
	void SetValue(float value);
	//�ʒu����
	void SetPos(GSvector3& pos);
	
public:

	//�l�̎擾
	float GetValue()const;

private:
	//�ʒu
	GSvector2 m_Position;
	//�J���[
	GScolor m_Color{ 1.0f,1.0f,1.0f,1.0 };
	//�X�P�[��
	GSvector2 m_Scale{ 5.0f,1.0f };
	//�ő�X�P�[��
	GSvector2 m_MaxScale{ m_Scale };
	//�ŏ��l
	float m_Min{ 0.0f };
	//�ő�l
	float m_Max{ 1.0f };
	//�l
	float m_Value;

};

#endif