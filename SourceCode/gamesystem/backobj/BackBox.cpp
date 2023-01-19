#include "BackBox.h"
BackBox::BackBox() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::BackBox);
}

//初期化
bool BackBox::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(m_Model);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Scale = { 8.0f,8.0f,8.0f };
	object3d_->SetScale(m_Scale);
	m_Object.reset(object3d_);

	return true;
}

//セット
void BackBox::SetObj() {
	/*object3d->SetPosition(m_pos);
	object3d->SetRotation(m_rot);
	object3d->SetScale(m_scale);*/
}

//特別な描画
void BackBox::specialDraw() {

}

void BackBox::Draw(DirectXCommon* dxCommon) {
	specialDraw();
	//オブジェクトの描画
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		Obj_Draw();
	}
}