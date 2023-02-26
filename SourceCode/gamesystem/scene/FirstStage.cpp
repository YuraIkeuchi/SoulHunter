#include "FirstStage.h"

//‰Šú‰»
void FirstStage::Initialize(DirectXCommon* dxCommon)
{
	//‹¤’Ê‚Ì‰Šú‰»
	BaseInitialize(dxCommon);
	actor = new PlaySceneActor();
	actor->Initialize(dxCommon,camera,lightGroup);
}
//XV
void FirstStage::Update(DirectXCommon* dxCommon)
{
	actor->Update(dxCommon, camera, lightGroup);
}
//•`‰æ
void FirstStage::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//‰ð•ú
void FirstStage::Finalize()
{
	actor->Finalize();
}
