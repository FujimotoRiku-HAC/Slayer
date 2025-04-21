#ifndef TITLE_CAMERA_H_
#define TITLE_CAMERA_H_

#include "Actor/Actor.h"

// 三人称カメラクラス
class TitleCamera : public Actor {
public:

    // コンストラクタ
    TitleCamera(IWorld* world, const GSvector3& position, const GSvector3& at);
    // 描画
    virtual void Draw() const override;
};
#endif