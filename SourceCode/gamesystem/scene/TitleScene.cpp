#include "TitleScene.h"

//初期化
void TitleScene::Initialize(DirectXCommon* dxCommon) {
	//共通の初期化
	BaseInitialize(dxCommon);
	actor = new TitleSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//更新
void TitleScene::Update(DirectXCommon* dxCommon) {
	lightGroup->Update();
	actor->Update(dxCommon, camera, lightGroup);
}
//描画
void TitleScene::Draw(DirectXCommon* dxCommon) {
	//ポストエフェクトをかけるか
	actor->Draw(dxCommon);
}

//解放
void TitleScene::Finalize() {
	actor->Finalize();
}
