#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "FirstStage.h"
#include "ClearScene.h"
//初期化
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	BaseInitialize(dxCommon);
	// テクスチャ読み込み
	IKESprite::LoadTexture(1, L"Resources/2d/sceneback/180_20220130123604.png");

	//背景スプライト生成
	sprite = IKESprite::Create(1, { 0.0f,0.0f });
	//スプライト生成
}
//更新
void ClearScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
	return;
	DebugText::GetInstance()->Print("ENTER to TITLE!!", 200, 100, 1.0f);
}
//描画
void ClearScene::Draw(DirectXCommon* dxCommon) {
	sprite->PreDraw();
	//背景用
	sprite->Draw();
}
//解放
void ClearScene::Finalize() {
	//３ｄのモデルのデリート
	delete sprite;
}

