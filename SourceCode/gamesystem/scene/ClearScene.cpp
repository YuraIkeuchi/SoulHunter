#include "ClearScene.h"
#include "Audio.h"
#include "input.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "imgui.h"
//初期化
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//カメラワーク
	camerawork = new CameraWork();
	camerawork->SetCameraType(5);
	//共通の初期化
	BaseInitialize(dxCommon);
	//Json
	clearobj = new ClearObj();
	clearobj->Initialize();

	//スプライト生成
	IKESprite* CurtainSprite_[2];
	//gaussian = new PostEffect();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite_[i] = IKESprite::Create(ImageManager::Curtain, { 0.0f,0.0f });
		CurtainSprite_[i]->SetAnchorPoint({ 0.5f,0.0f });
		CurtainSprite[i].reset(CurtainSprite_[i]);
	}

	CurtainSprite[0]->SetPosition({ 640.0f,0.0f });
	CurtainSprite[1]->SetPosition({ 640.0f,620.0f });

	IKESprite* SkipSprite_;
	SkipSprite_ = IKESprite::Create(ImageManager::SkipText, { 0.0f,0.0f });
	SkipSprite_->SetAnchorPoint({ 0.5f,0.0f });
	SkipSprite_->SetPosition({ 1000.0f,620.0f });
	SkipSprite.reset(SkipSprite_);

	IKESprite* IntroSprite_;
	IntroSprite_ = IKESprite::Create(ImageManager::IntroText, { 0.0f,0.0f });
	IntroSprite.reset(IntroSprite_);

	//シーンチェンジ
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);

	//プレイヤー
	player = new Player();
	player->Initialize();
	player->StateInitialize();
	//ライト
	m_LightPos = { 5.0f,5.0f,-80.0f };

	//プレイヤーが必要
	camerawork->SetPlayer(player);

	//ライト
	//lightGroup->SetDirLightActive(0, true);
	//lightGroup->SetDirLightActive(1, true);
	//lightGroup->SetDirLightActive(2, true);
}
//更新
void ClearScene::Update(DirectXCommon* dxCommon) {
	m_Timer++;
	//
	ParticleManager::GetInstance()->Update();
	Input* input = Input::GetInstance();
	lightGroup->Update();
	//丸影
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	///ポイントライト
	lightGroup->SetPointLightPos(0, { clearobj->GetTorchPos().x, -5.0f, clearobj->GetTorchPos().z});
	lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));
	clearobj->Update(m_Timer);
	//カメラの位置調整
	camerawork->Update(camera);
	//camerawork->SetIntroTimer(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}

	//演出
	Movie();

	player->ClearUpdate(m_Timer);
	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	IntroSprite->SetColor(m_TextColor);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	ChangePostEffect(PostType);
	postEffect->SetSepia(m_Sepia);
}
//描画
void ClearScene::Draw(DirectXCommon* dxCommon) {

	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		GameDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw();

		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		//player->ImGuiDraw();
		//particleobj->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		GameDraw(dxCommon);
		FrontDraw();
		/*player->ImGuiDraw();
		for (int i = 0; i < 2; i++) {
			enemy[i]->ImGuiDraw();
		}*/
		//particleobj->ImGuiDraw();
		dxCommon->PostDraw();
	}
}
//背景
void ClearScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	clearobj->BackDraw();
	IKEObject3d::PostDraw();
	player->ClearDraw(dxCommon);
}
//前面描画
void ClearScene::FrontDraw() {
	IKEObject3d::PreDraw();
	clearobj->FrontDraw();
	IKEObject3d::PostDraw();
	IKESprite::PreDraw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	IntroSprite->Draw();
	scenechange->Draw();
	IKESprite::PostDraw();
}
//上の描画にスプライトなども混ぜた
void ClearScene::GameDraw(DirectXCommon* dxCommon)
{
	//ImGuiDraw();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理

#pragma endregion
	//スプライトの描画
	ModelDraw(dxCommon);
	//FBXの描画
	//object1->Draw(dxCommon->GetCmdList());
}
//ImGui描画
void ClearScene::ImGuiDraw(DirectXCommon* dxCommon) {
	////FPSManager::GetInstance()->ImGuiDraw();
	ImGui::Begin("Clear");
	ImGui::Text("Timer:%d",m_Timer);
	ImGui::Text("ResetTimer:%d", m_ResetTimer);
	ImGui::End();
}
//解放
void ClearScene::Finalize() {
	//３ｄのモデルのデリート
	//delete sprite;
	delete postEffect;
	delete save;
}
//ポストエフェクトのImgui
void ClearScene::PostImGuiDraw(DirectXCommon* dxCommon) {
	{
		if (PlayPostEffect) {
			ImGui::Begin("PostType");
			ImGui::SetWindowPos(ImVec2(600, 450));
			ImGui::SetWindowSize(ImVec2(280, 150));
			ImGui::Text("m_ChangePostEffect:%d", m_ChangePostEffect);
			if (ImGui::RadioButton("Stripe", &PostType)) {

				PostType = Stripe;
				m_ChangePostEffect = true;
				//ChangePostEffect(PostType);
			}
			if (ImGui::RadioButton("Gaussian", &PostType)) {
				PostType = Blur;
				m_ChangePostEffect = true;

			}
			ImGui::End();
		}
	}
	{
		ImGui::Begin("postEffect");
		ImGui::SetWindowPos(ImVec2(700, 150));
		ImGui::SetWindowSize(ImVec2(280, 150));
		if (ImGui::RadioButton("PostEffect", &PlayPostEffect)) {
			PlayPostEffect = true;
		}
		if (ImGui::RadioButton("Default", &PlayPostEffect)) {
			PlayPostEffect = false;
		}
		ImGui::End();
	}
}
//ポストエフェクトの種類
void ClearScene::ChangePostEffect(int PostType) {
	if (m_ChangePostEffect) {

		if (PostType == Stripe) {

			postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/PostEffectTestPS.hlsl");
		}
		else if (PostType == Blur) {

			postEffect->CreateGraphicsPipeline(L"Resources/Shaders/GaussianVS.hlsl", L"Resources/Shaders/GaussianPS.hlsl");
		}

		m_ChangePostEffect = false;
	}
}
//演出
void ClearScene::Movie() {

	m_ResetTimer++;

	if (m_ResetTimer == 100) {
		clearobj->SetTorchPos({ 0.0f,-5.0f,player->GetPosition().z + 10.0f });
		m_ResetTimer = 0;
	}
	
	if (m_Timer == 2500) {
		scenechange->SetAddStartChange(true);
	}
}