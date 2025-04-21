#include "TweenUnit.h"

TweenUnit::TweenUnit(float duration) : m_Duration{duration}{ }

void TweenUnit::Update(float delta_time) {
    //delay���ݒ肳��Ă�����A���ꂪ�Ȃ��Ȃ�܂ŉ��������ɑҋ@
    if (m_Delay > 0) {
        m_Delay -= delta_time;
        if (m_Delay > 0) {
            return;
        }
        else {
            //�ҋ@���������ꍇ�͌o�ߎ��ԂƂ��Čv��
            m_Elapsed = -m_Delay;
        }
    }
	//�o�ߎ��Ԃ�i�߂�
    m_Elapsed += delta_time;
	//�i�������v�Z
	float progress = m_Elapsed / m_Duration;
	//1.0�ȏ�ɂȂ�Ȃ��悤�ɂ���
	progress = std::min(progress, 1.f);
	//�i������Easing��K�p����
	float eased = ApplyEase(progress, m_EaseType,m_Overshoot);
	//�h���N���X���Ƃ̍X�V�������s��
	OnUpdate(eased);
	//�I��������
	m_IsFinished = progress >= 1.f;

    //�I�����Ă��Ċ������̃R�[���o�b�N���Ă΂ꂽ��
    if (m_IsFinished && m_CompleteFunc) {
        m_CompleteFunc();
    }
}

bool TweenUnit::IsFinished() const{
	return m_IsFinished;
}

TweenUnit& TweenUnit::Ease(EaseType ease_type) {
	m_EaseType = ease_type;
	return *this;
}

TweenUnit& TweenUnit::Overshoot(float overshoot) {
    m_Overshoot = overshoot;
    return *this;
}

TweenUnit& TweenUnit::Delay(float delay) {
    m_Delay = delay;
    return *this;
}

TweenUnit& TweenUnit::OnComplete(std::function<void()>ccomplete_func) {
    m_CompleteFunc = ccomplete_func;
    return *this;
}

const std::string& TweenUnit::Name()const {
    return m_Name;
}

TweenUnit& TweenUnit::Name(const std::string& name) {
    m_Name = name;
    return *this;
}

float TweenUnit::ApplyEase(float value, EaseType ease_type,float overshoot) {
    switch (ease_type) {
    case EaseType::Linear:         return value;
    case EaseType::EaseInBack:     return gsEasingInBack(value,overshoot);
    case EaseType::EaseInCirc:     return gsEasingInCirc(value);
    case EaseType::EaseInCubic:    return gsEasingInCubic(value);
    case EaseType::EaseInExpo:     return gsEasingInExpo(value);
    case EaseType::EaseInQuad:     return gsEasingInQuad(value);
    case EaseType::EaseInQuart:    return gsEasingInQuart(value);
    case EaseType::EaseInQuint:    return gsEasingInQuint(value);
    case EaseType::EaseInSine:     return gsEasingInSine(value);
    case EaseType::EaseOutBack:    return gsEasingOutBack(value,overshoot);
    case EaseType::EaseOutBounce:  return gsEasingOutBounce(value);
    case EaseType::EaseOutCirc:    return gsEasingOutCirc(value);
    case EaseType::EaseOutCubic:   return gsEasingOutCubic(value);
    case EaseType::EaseOutElastic: {
        if (value == 1.0f)return 1.0f;
        return 1.0f - cos(value * 10 * overshoot) * pow(1 - value, 3);
    }
    case EaseType::EaseOutExpo:    return gsEasingOutExpo(value);
    case EaseType::EaseOutQuad:    return gsEasingOutQuad(value);
    case EaseType::EaseOutQuart:   return gsEasingOutQuart(value);
    case EaseType::EaseOutQuint:   return gsEasingOutQuint(value);
    case EaseType::EaseOutSine:    return gsEasingOutSine(value);
    case EaseType::EaseInOutBack:  return gsEasingInOutBack(value,overshoot);
    case EaseType::EaseInOutCirc:  return gsEasingInOutCirc(value);
    case EaseType::EaseInOutCubic: return gsEasingInOutCubic(value);
    case EaseType::EaseInOutExpo:  return gsEasingInOutExpo(value);;
    case EaseType::EaseInOutQuad:  return gsEasingInOutQuad(value);
    case EaseType::EaseInOutQuart: return gsEasingInOutQuart(value);
    case EaseType::EaseInOutQuint: return gsEasingInOutQuint(value);
    case EaseType::EaseInOutSine:  return gsEasingInOutSine(value);
    case EaseType::Punch: {
        if (value == 0 || value == 1)return 0;
        float peek = 0.25f / overshoot;
        float a = (value - 1.0f) / (peek - 1.0f);
        a = CLAMP(a, 0.0f, 1.0f);
        float b = a * a * (3 - 2 * a);
        return sin(value * 6.2831853f * overshoot) * b;
    }
    default: return value;
    }
}