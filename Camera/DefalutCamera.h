#ifndef DEFALUT_CAMERA_H_
#define DEFALUT_CAMERA_H_

#include "Actor/Actor.h"

// �O�l�̃J�����N���X
class DefalutCamera : public Actor {
public:

    // �R���X�g���N�^
    DefalutCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // �X�V
    virtual void Update(float delta_time) override;
    // �`��
    virtual void Draw() const override;
    //���b�Z�[�W��M
    virtual void HandleMessage(const std::string& message, void* param)override;

public:

    //�J�����V�F�C�N
    void Shake();
    //�J�����V�F�C�N����
    void ShakeOff();

private:

    //�J�����X�V
    void DefaultUpdate(float delta_time);
    //���b�N�I�����̍X�V
    void LockOnUpdate(float delta_time);
    //�h�A�I�[�v����
    void DoorLockOnUpdate(float delta_time);
    //�J�����h�炷
    void ShakeCamera(float delta_time);
    //�G�t�F�N�g�\��
    void SetCameraEffect();

private:

    enum class State {
        Default,
        EnemyLockOn,
        DoorLockOn,
        Reset
    };

private:
    State m_State = State::Default; //���
    GSuint m_SpeedLineHandle;       //�G�t�F�N�g�n���h��
    int m_EnemyNum = 0;             //�G�̐�
    float m_ShakeTime{ 0.0f };      //�h�炷����
    float m_Yaw{ 0.0f };            //���E
    float m_Pitch{ 0.0f };          //�s�b�`
    bool m_IsEffect{ false };       //�G�t�F�N�g���g����
    bool m_Open = false;            //�J������
    bool m_IsShake = false;         //�h�炷��
    bool m_IsDoorDie = false;       //�h�A�����S������
};

#endif