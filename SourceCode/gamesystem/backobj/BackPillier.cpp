#include "BackPillier.h"
#include <Easing.h>
BackRock::BackRock() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::BackRock);
}

//‰Šú‰»
void BackRock::Initialize() {
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(model);
	m_pos = { 110.0f,-90.0,0.0f };
	object3d_->SetPosition(m_pos);
	m_scale = { 7.0f,30.0f,7.0f };
	object3d_->SetScale(m_scale);
	object3d.reset(object3d_);

}

//”z’u
void BackRock::SetObj() {
	object3d->SetPosition(m_pos);
	object3d->SetRotation(m_rot);
	object3d->SetScale(m_scale);
}

//“Á•Ê‚È•`‰æ
void BackRock::specialDraw() {

}

