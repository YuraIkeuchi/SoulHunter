#include "BaseScene.h"
#include "ImageManager.h"
#include "PlayerSkill.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"


//共通の初期化
void BaseScene::BaseInitialize(DirectXCommon* dxCommon) {
	// デバイスをセット
	IKEFBXObject3d::SetDevice(dxCommon->GetDev());
	// グラフィックスパイプライン生成
	IKEFBXObject3d::CreateGraphicsPipeline();
	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	IKETexture::SetCamera(camera);
	// 3Dオブジェクトにカメラをセット
	IKEObject3d::SetCamera(camera);
	IKEFBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	IKEObject3d::SetLightGroup(lightGroup);

	ParticleEmitter::GetInstance()->AllDelete();
	//丸影のためのやつ
	lightGroup->SetDirLightActive(0, false);
	lightGroup->SetDirLightActive(1, false);
	lightGroup->SetDirLightActive(2, false);
	lightGroup->SetPointLightActive(0, true);
	lightGroup->SetPointLightActive(1, true);
	lightGroup->SetCircleShadowActive(0, true);
}
