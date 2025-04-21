#ifndef TWEEN_UNIT_H_
#define TWEEN_UNIT_H_

//
enum class EaseType{
    Linear,
    EaseInBack,
    EaseInCirc,
    EaseInCubic,
    EaseInExpo,
    EaseInQuad,
    EaseInQuart,
    EaseInQuint,
    EaseInSine,
    EaseOutBack,
    EaseOutBounce,
    EaseOutCirc,
    EaseOutCubic,
    EaseOutElastic,
    EaseOutExpo,
    EaseOutQuad,
    EaseOutQuart,
    EaseOutQuint,
    EaseOutSine,
    EaseInOutBack,
    EaseInOutCirc,
    EaseInOutCubic,
    EaseInOutExpo,
    EaseInOutQuad,
    EaseInOutQuart,
    EaseInOutQuint,
    EaseInOutSine,
    Punch,
};

class TweenUnit {
public:

	//�R���X�g���N�^
	TweenUnit(float duration);
	//���z�f�X�g���N�^
	virtual ~TweenUnit() = default;
	//�X�V
	void Update(float delta_time);
	//�I��������
	bool IsFinished() const;
    //�C�[�W���O��ʂ�ݒ�
    TweenUnit& Ease(EaseType ease_type);
    //Back,Elastic,Punch�Ő�����ݒ�
    TweenUnit& Overshoot(float ease_type);
    //�J�n�x�����Ԃ�ݒ�
    TweenUnit& Delay(float delay);
    //�������̃R�[���o�b�N��ݒ�
    TweenUnit& OnComplete(std::function<void()>complete_func);
    //���O�ݒ�
    TweenUnit& Name(const std::string& name);
    //���O�擾
    const std::string& Name()const;

	//�R�s�[�֎~
	TweenUnit(const TweenUnit& other) = delete;
	TweenUnit& operator = (const TweenUnit& other) = delete;
protected:

	//�h���N���X���Ƃ̍X�V����
	virtual void OnUpdate(float progress){}

private:

    //�l��Easing��K�p����
    static float ApplyEase(float value, EaseType ease_type, float overshoot);

private:
	float m_Duration{ 0.0f };                     //�A�j���[�V��������
	float m_Elapsed{ 0.0f };                      //�o�ߎ���
	bool m_IsFinished{ false };                   //�I��������
    EaseType m_EaseType{ EaseType::Linear };      //Easing���
    float m_Overshoot{ 1.70158f };                //Elastic,Back,Punch�Ŏg������
    float m_Delay{ 0.0f };                        //�J�n�x������
    std::function<void()>m_CompleteFunc;          //�������̃R�[���o�b�N
    std::string m_Name{};                         //���O�擾


};

#endif