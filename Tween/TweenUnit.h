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

	//コンストラクタ
	TweenUnit(float duration);
	//仮想デストラクタ
	virtual ~TweenUnit() = default;
	//更新
	void Update(float delta_time);
	//終了したか
	bool IsFinished() const;
    //イージング種別を設定
    TweenUnit& Ease(EaseType ease_type);
    //Back,Elastic,Punchで勢いを設定
    TweenUnit& Overshoot(float ease_type);
    //開始遅延時間を設定
    TweenUnit& Delay(float delay);
    //完了時のコールバックを設定
    TweenUnit& OnComplete(std::function<void()>complete_func);
    //名前設定
    TweenUnit& Name(const std::string& name);
    //名前取得
    const std::string& Name()const;

	//コピー禁止
	TweenUnit(const TweenUnit& other) = delete;
	TweenUnit& operator = (const TweenUnit& other) = delete;
protected:

	//派生クラスごとの更新処理
	virtual void OnUpdate(float progress){}

private:

    //値にEasingを適用する
    static float ApplyEase(float value, EaseType ease_type, float overshoot);

private:
	float m_Duration{ 0.0f };                     //アニメーション時間
	float m_Elapsed{ 0.0f };                      //経過時間
	bool m_IsFinished{ false };                   //終了したか
    EaseType m_EaseType{ EaseType::Linear };      //Easing種別
    float m_Overshoot{ 1.70158f };                //Elastic,Back,Punchで使う勢い
    float m_Delay{ 0.0f };                        //開始遅延時間
    std::function<void()>m_CompleteFunc;          //完了時のコールバック
    std::string m_Name{};                         //名前取得


};

#endif