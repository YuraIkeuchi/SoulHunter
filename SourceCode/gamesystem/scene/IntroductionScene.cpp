#include "IntroductionScene.h"

//‰Šú‰»
void IntroductionScene::Initialize(DirectXCommon* dxCommon) {
	//‹¤’Ê‚Ì‰Šú‰»
	BaseInitialize(dxCommon);
	actor = new IntroductionSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//XV
void IntroductionScene::Update(DirectXCommon* dxCommon) {
	actor->Update(dxCommon, camera, lightGroup);
}
//•`‰æ
void IntroductionScene::Draw(DirectXCommon* dxCommon) {
	actor->Draw(dxCommon);
}
//‰ð•ú
void IntroductionScene::Finalize() {
	actor->Finalize();
}
