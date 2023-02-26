#include "FirstStage.h"

//初期化
void FirstStage::Initialize(DirectXCommon* dxCommon)
{
	//共通の初期化
	BaseInitialize(dxCommon);
	actor = new PlaySceneActor();
	actor->Initialize(dxCommon,camera,lightGroup);
}
//更新
void FirstStage::Update(DirectXCommon* dxCommon)
{
	actor->Update(dxCommon, camera, lightGroup);
}
//描画
void FirstStage::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//解放
void FirstStage::Finalize()
{
	actor->Finalize();
}
