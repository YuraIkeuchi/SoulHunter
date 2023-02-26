#include "ClearScene.h"

//初期化
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//共通の初期化
	BaseInitialize(dxCommon);
	actor = new ClearSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//更新
void ClearScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//描画
void ClearScene::Draw(DirectXCommon* dxCommon) {
	//ポストエフェクトをかけるか
	actor->Draw(dxCommon);
}

//解放
void ClearScene::Finalize() {
	actor->Finalize();
}
