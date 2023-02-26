#include "IntroductionScene.h"

//初期化
void IntroductionScene::Initialize(DirectXCommon* dxCommon) {
	//共通の初期化
	BaseInitialize(dxCommon);
	actor = new IntroductionSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//更新
void IntroductionScene::Update(DirectXCommon* dxCommon) {
	actor->Update(dxCommon, camera, lightGroup);
}
//描画
void IntroductionScene::Draw(DirectXCommon* dxCommon) {
	actor->Draw(dxCommon);
}
//解放
void IntroductionScene::Finalize() {
	actor->Finalize();
}
