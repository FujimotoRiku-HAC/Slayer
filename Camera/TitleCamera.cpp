#include "TitleCamera.h"
#include "Field/Field.h"
#include "Math/Line.h"

//コンストラクタ
TitleCamera::TitleCamera(IWorld* world, const GSvector3& position, const GSvector3& at) {
	//ワールドを設定
	m_World = world;
	//タグの設定
	m_Tag = st_CameraTag;
	//名前の設定
	m_Name = st_Camera;
	//始点の位置を設定
	m_Transform.position(position);
	//注視点を設定(注視店の方向に向きを変える)
	m_Transform.lookAt(at);
}

//描画
void TitleCamera::Draw() const {
	//視点の位置
	GSvector3 eye = m_Transform.position();
	//注視点の位置
	GSvector3 at = eye + m_Transform.forward();
	//カメラの設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eye.x, eye.y, eye.z,
		at.x, at.y, at.z,
		0.f, 1.f, 0.f
	);
}