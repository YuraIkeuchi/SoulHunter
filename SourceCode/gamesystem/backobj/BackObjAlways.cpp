#include "BackObjAlways.h"
#include "ModelManager.h"
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
}

//更新
void BackObjAlways::Update() {
	Obj_SetParam();
}

//描画
void BackObjAlways::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}

void BackObjAlways::InitRock(int StageNumber) {
	////後々エディタにする
	//if (StageNumber != BossMap) {
	//	objground[0]->SetPosition({ 50.0f, -80.0f, 25.0f });
	//	objground[1]->SetPosition({ 50.0f, -150.0f, 25.0f });
	//	objground[2]->SetPosition({ 50.0f, -250.0f, 25.0f });
	//	objground[3]->SetPosition({ 120.0f, -40.0f, 25.0f });
	//	objground[4]->SetPosition({ 130.0f, -150.0f, 25.0f });
	//	objground[5]->SetPosition({ 130.0f, -250.0f, 25.0f });
	//	objground[6]->SetPosition({ 200.0f, -200.0f, 25.0f });
	//	objground[7]->SetPosition({ 200.0f, -100.0f, 25.0f });
	//	objground[8]->SetPosition({ 285.0f, -150.0f, 25.0f });
	//	objground[9]->SetPosition({ 285.0f, -100.0f, 25.0f });
	//	objground[10]->SetPosition({ 285.0f, -250.0f, 25.0f });
	//}
	//else {
	//	objground[0]->SetPosition({ 135.0f, -20.0f, 25.0f });
	//	objground[1]->SetPosition({ 135.0f, -80.0f, 25.0f });
	//	objground[2]->SetPosition({ 285.0f, -130.0f, 25.0f });
	//	objground[3]->SetPosition({ 135.0f, -130.0f, 25.0f });
	//	for (int i = 4; i < BackRock_Max; i++) {
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//		objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
	//	}
	//}
}