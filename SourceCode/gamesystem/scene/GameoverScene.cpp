#include "GameoverScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "SceneManager.h"
#include "GameoverScene.h"
#include "imgui.h"
#include "ImageManager.h"
//初期化
void GameoverScene::Initialize(DirectXCommon* dxCommon) {
	BaseInitialize(dxCommon);
	IKESprite* sprite_;
	sprite_ = IKESprite::Create(ImageManager::Title, { 0.0f,0.0f });
	sprite.reset(sprite_);
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);
	/*shrinkchange = new ShrinkChange();
	shrinkchange->SetEndChange(true);
	expandchange = new ExpandChange();*/
}
//更新
void GameoverScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	//押したら画面が黒くなる
	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}
	//画面が暗くなりタイトルに戻る
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	scenechange->Update();
	scenechange->SubBlack(0.05f);
	//shrinkchange->Update();
	//expandchange->Update();*/
}
//描画
void GameoverScene::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("GameOver");
	ImGui::End();*/
	dxCommon->PreDraw();
	IKESprite::PreDraw();
	//背景用
	sprite->Draw();
	scenechange->Draw();
	//expandchange->Draw();
	//shrinkchange->Draw();
	dxCommon->PostDraw();
	//
}
//解放
void GameoverScene::Finalize() {
}

