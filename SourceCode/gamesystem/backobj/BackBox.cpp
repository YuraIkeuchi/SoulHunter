#include "BackBox.h"
#include <Easing.h>
BackBox::BackBox() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::BackBox);
}

//初期化
void BackBox::Initialize() {
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(model);
	m_pos = { 110.0f,-90.0,0.0f };
	object3d_->SetPosition(m_pos);
	m_scale = { 8.0f,8.0f,8.0f };
	object3d_->SetScale(m_scale);
	object3d.reset(object3d_);

}

//セット
void BackBox::SetObj() {
	object3d->SetPosition(m_pos);
	object3d->SetRotation(m_rot);
	object3d->SetScale(m_scale);
}

//特別な描画
void BackBox::specialDraw() {

}

