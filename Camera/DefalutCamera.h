#ifndef DEFALUT_CAMERA_H_
#define DEFALUT_CAMERA_H_

#include "Actor/Actor.h"

// 三人称カメラクラス
class DefalutCamera : public Actor {
public:

    // コンストラクタ
    DefalutCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // 更新
    virtual void Update(float delta_time) override;
    // 描画
    virtual void Draw() const override;
    //メッセージ受信
    virtual void HandleMessage(const std::string& message, void* param)override;

public:

    //カメラシェイク
    void Shake();
    //カメラシェイク解除
    void ShakeOff();

private:

    //カメラ更新
    void DefaultUpdate(float delta_time);
    //ロックオン時の更新
    void LockOnUpdate(float delta_time);
    //ドアオープン時
    void DoorLockOnUpdate(float delta_time);
    //カメラ揺らす
    void ShakeCamera(float delta_time);
    //エフェクト表示
    void SetCameraEffect();

private:

    enum class State {
        Default,
        EnemyLockOn,
        DoorLockOn,
        Reset
    };

private:
    State m_State = State::Default; //状態
    GSuint m_SpeedLineHandle;       //エフェクトハンドル
    int m_EnemyNum = 0;             //敵の数
    float m_ShakeTime{ 0.0f };      //揺らす時間
    float m_Yaw{ 0.0f };            //ヨウ
    float m_Pitch{ 0.0f };          //ピッチ
    bool m_IsEffect{ false };       //エフェクトを使うか
    bool m_Open = false;            //開いたか
    bool m_IsShake = false;         //揺らすか
    bool m_IsDoorDie = false;       //ドアが死亡したか
};

#endif