#include "IntroductionScene.h"
#include "Audio.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "imgui.h"
IntroductionObj* IntroductionScene::Introductionobj = nullptr;
bool IntroductionScene ::m_IntroNew = false;
//初期化
void IntroductionScene::Initialize(DirectXCommon* dxCommon) {
	//カメラワーク
	camerawork = new CameraWork();
	camerawork->SetCameraType(1);
	//共通の初期化
	BaseInitialize(dxCommon);
	//Json
	if (!m_IntroNew) {
		Introductionobj = new IntroductionObj();
		Introductionobj->Initialize();
		m_IntroNew = true;
	}
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
	
	//プレイヤーが必要
	camerawork->SetPlayer(player);
	
	//ライト
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");
}
//更新
void IntroductionScene::Update(DirectXCommon* dxCommon) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightGroup->Update();
	//丸影
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	Introductionobj->Update(m_Timer);
	//カメラの位置調整
	camerawork->Update(camera);
	camerawork->SetIntroTimer(m_Timer);
	//プレイヤーの更新
	player->IntroductionUpdate(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}
	
	
	//演出
	Movie();

	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("LOAD");
	}

	IntroSprite->SetColor(m_TextColor);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	ChangePostEffect(PostType);
	postEffect->SetSepia(m_Sepia);
}
//描画
void IntroductionScene::Draw(DirectXCommon* dxCommon) {

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
void IntroductionScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	Introductionobj->BackDraw();

	IKEObject3d::PostDraw();
	player->IntroductionDraw(dxCommon);
}
//前面描画
void IntroductionScene::FrontDraw() {
	IKEObject3d::PreDraw();
	Introductionobj->FrontDraw();
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
void IntroductionScene::GameDraw(DirectXCommon* dxCommon)
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
void IntroductionScene::ImGuiDraw(DirectXCommon* dxCommon) {
	////FPSManager::GetInstance()->ImGuiDraw();
	//ImGui::Begin("Introduce");
	//ImGui::Text("Timer:%d",m_Timer);
	//ImGui::End();
}
//解放
void IntroductionScene::Finalize() {
	//３ｄのモデルのデリート
	//delete sprite;
	delete postEffect;
	delete save;
}
//ポストエフェクトのImgui
void IntroductionScene::PostImGuiDraw(DirectXCommon* dxCommon) {
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
void IntroductionScene::ChangePostEffect(int PostType) {
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
void IntroductionScene::Movie() {
	//一定時間立つと画面が暗くなる
	if (m_Timer == 420) {
		PlayPostEffect = true;
	}

	//セピアカラーになる
	if (PlayPostEffect) {
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.005f;
		}
		else {
			m_Frame = 1.0f;
		}

		m_Sepia = Ease(In, Cubic, m_Frame, m_Sepia, 0.1f);

		if (m_Frame == 1.0f) {
			if (m_TextColor.w < 1.0f) {
				m_TextColor.w += 0.01f;
			}
			else {
				m_TextColor.w = 1.0f;
			}
		}
	}

	//一定時間でシーンが変わる
	if (m_TextColor.w == 1.0f) {
		m_ChangeTimer++;

		if (m_ChangeTimer == 200) {
			scenechange->SetAddStartChange(true);
		}
	}
}