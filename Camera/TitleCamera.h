#ifndef TITLE_CAMERA_H_
#define TITLE_CAMERA_H_

#include "Actor/Actor.h"

// �O�l�̃J�����N���X
class TitleCamera : public Actor {
public:

    // �R���X�g���N�^
    TitleCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // �`��
    virtual void Draw() const override;
};
#endif