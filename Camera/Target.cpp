#include "Target.h"

Target::Target(){
	//名前取得
	m_Name = st_Target;
	//タグ取得
	m_Tag = st_TargetTag;
	//アセットロード
	gsLoadTexture(Target_Texture, "Assets/Texture/UI/PlayScene/target.png");
	//衝突判定無効
	m_EnableCollider = false;
	//描画しない
	m_IsDraw = false;
	//寿命
	m_LifeTimer = TargetLifeSpan;
}

void Target::Update(float delta_time){
	if (!m_IsDraw)return;

	if (m_LifeTimer <= 0.f)m_IsDraw = false;

	GSvector3 pos = m_Owner->Transform().position() + GSvector3{ 0.f,m_Owner->Collider().m_Radius + TargetOffset,0.f };
	gsCalculateScreen(&m_DrawPos, &pos);

	m_LifeTimer -= delta_time;
}

void Target::DrawGui() const{
	if (!m_IsDraw)return;
	GScolor color = { 1.f,1.f,1.f,0.8f };
	GSvector2 scale = { 0.1f,0.1f };
	gsDrawSprite2D(Target_Texture, &m_DrawPos, NULL, &TargetCenter, &color, &scale, NULL);
}

void Target::HandleMessage(const std::string& message, void* param){
	if (message == st_Message_Die) m_IsDraw = false;
	
}

void Target::TargetDraw(const GSvector3& pos){
	gsCalculateScreen(&m_DrawPos, &pos);
	m_IsDraw = true;
	m_LifeTimer = TargetLifeSpan;
}

void Target::TargetDraw(Actor* owner){
	m_Owner = owner;
	m_IsDraw = true;
	m_LifeTimer = TargetLifeSpan;
}
