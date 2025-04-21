#include "TweenUnit.h"

TweenUnit::TweenUnit(float duration) : m_Duration{duration}{ }

void TweenUnit::Update(float delta_time) {
    //delayが設定されていたら、それがなくなるまで何もせずに待機
    if (m_Delay > 0) {
        m_Delay -= delta_time;
        if (m_Delay > 0) {
            return;
        }
        else {
            //待機しすぎた場合は経過時間として計上
            m_Elapsed = -m_Delay;
        }
    }
	//経過時間を進める
    m_Elapsed += delta_time;
	//進捗率を計算
	float progress = m_Elapsed / m_Duration;
	//1.0以上にならないようにする
	progress = std::min(progress, 1.f);
	//進捗率にEasingを適用する
	float eased = ApplyEase(progress, m_EaseType,m_Overshoot);
	//派生クラスごとの更新処理を行う
	OnUpdate(eased);
	//終了したか
	m_IsFinished = progress >= 1.f;

    //終了していて完了時のコールバックが呼ばれたら
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