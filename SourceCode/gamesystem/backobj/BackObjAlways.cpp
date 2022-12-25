#include "BackObjAlways.h"
#include "ModelManager.h"
#include "ImageManager.h"
//初期化
void BackObjAlways::Initialize() {

	//ステージ地面
	modelground = ModelManager::GetInstance()->GetModel(ModelManager::StageBackRock);
	IKEObject3d* objground_[BackRock_Max];
	for (int i = 0; i < BackRock_Max; i++) {
		objground_[i] = new IKEObject3d();
		objground_[i] = IKEObject3d::Create();
		objground_[i]->SetModel(modelground);
		objground_[i]->SetTiling(15.0f);
		objground_[i]->SetColor({ 0.5f,0.5f,0.5f,1.0f });
		objground_[i]->SetScale({ 0.2f,0.2f,0.1f });
		//objground_[i]->SetLightEffect(false);
		//objground_[i]->SetFog(true);
		objground[i].reset(objground_[i]);
	}
}

//更新
void BackObjAlways::Update() {
	for (int i = 0; i < BackRock_Max; i++) {
		objground[i]->Update();
	}
}

//描画
const void BackObjAlways::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < BackRock_Max; i++) {
		objground[i]->Draw();
	}
}

void BackObjAlways::InitRock(int StageNumber) {
	//後々エディタにする
	if (StageNumber != BossMap) {
		objground[0]->SetPosition({ 50.0f, -80.0f, 25.0f });
		objground[1]->SetPosition({ 50.0f, -150.0f, 25.0f });
		objground[2]->SetPosition({ 50.0f, -250.0f, 25.0f });
		objground[3]->SetPosition({ 120.0f, -40.0f, 25.0f });
		objground[4]->SetPosition({ 130.0f, -150.0f, 25.0f });
		objground[5]->SetPosition({ 130.0f, -250.0f, 25.0f });
		objground[6]->SetPosition({ 200.0f, -200.0f, 25.0f });
		objground[7]->SetPosition({ 200.0f, -100.0f, 25.0f });
		objground[8]->SetPosition({ 285.0f, -150.0f, 25.0f });
		objground[9]->SetPosition({ 285.0f, -100.0f, 25.0f });
		objground[10]->SetPosition({ 285.0f, -250.0f, 25.0f });
	}
	else {
		objground[0]->SetPosition({ 135.0f, -20.0f, 25.0f });
		objground[1]->SetPosition({ 135.0f, -80.0f, 25.0f });
		objground[2]->SetPosition({ 285.0f, -130.0f, 25.0f });
		objground[3]->SetPosition({ 135.0f, -130.0f, 25.0f });
		for (int i = 4; i < BackRock_Max; i++) {
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
			objground[i]->SetPosition({ 5000.0f, -250.0f, 25.0f });
		}
	}
}