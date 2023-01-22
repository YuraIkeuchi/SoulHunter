#include "BackObjAlways.h"
#include "ModelManager.h"
#include "imgui.h"
#include "VariableCommon.h"
BackObjAlways::BackObjAlways() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::StageBackRock);
}
//初期化
bool BackObjAlways::Initialize() {
	m_Color = { 0.5f,0.5f,0.5f,1.0f };
	m_Scale = { 0.2f,0.2f,0.1f };
	//ステージ地面
	IKEObject3d* Object_;
	Object_ = new IKEObject3d();
	Object_ = IKEObject3d::Create();
	Object_->SetModel(m_Model);
	Object_->SetTiling(15.0f);
	m_Object.reset(Object_);

	return true;
}

//更新
void BackObjAlways::Update() {
	Obj_SetParam();
}

//描画
void BackObjAlways::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}
