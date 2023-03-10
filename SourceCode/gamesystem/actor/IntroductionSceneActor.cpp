#include "IntroductionSceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "imgui.h"
IntroductionObj* IntroductionSceneActor::Introductionobj = nullptr;
bool IntroductionSceneActor::m_IntroNew = false;
//初期化
void IntroductionSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
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
	introplayer = make_unique<IntroPlayer >();
	introplayer->Initialize();

	//プレイヤーが必要
	camerawork->SetIntroPlayer(introplayer.get());

	//ライト
	lightgroup->SetDirLightActive(0, true);
	lightgroup->SetDirLightActive(1, true);
	lightgroup->SetDirLightActive(2, true);
	lightgroup->SetPointLightActive(0, false);
	lightgroup->SetPointLightActive(1, false);

	//ポストエフェクトのファイル指定
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");

	//オーディオ
	Audio::GetInstance()->LoadSound(2, "Resources/Sound/BGM/8bo8k-1eq6w.wav");
	Audio::GetInstance()->LoopWave(2, VolumManager::GetInstance()->GetBGMVolum());
}
//更新
void IntroductionSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightgroup->Update();
	//丸影
	lightgroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ introplayer->GetPosition().x, introplayer->GetPosition().y, introplayer->GetPosition().z }));
	lightgroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightgroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	Introductionobj->Update(m_Timer);
	//カメラの位置調整
	camerawork->Update(camera);
	camerawork->SetIntroTimer(m_Timer);
	//プレイヤーの更新
	introplayer->Update();
	introplayer->IntroMove(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}

	//演出
	Movie();

	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		Audio::GetInstance()->StopWave(2);
		SceneManager::GetInstance()->ChangeScene("LOAD");
	}

	IntroSprite->SetColor(m_TextColor);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	postEffect->SetSepia(m_Sepia);
}
//描画
void IntroductionSceneActor::Draw(DirectXCommon* dxCommon) {

	//ポストエフェクトをかけるか
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		GameDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw();
		camerawork->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		ImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		GameDraw(dxCommon);
		FrontDraw();
		dxCommon->PostDraw();
	}
}
//背景
void IntroductionSceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	Introductionobj->BackDraw();

	IKEObject3d::PostDraw();
	introplayer->Draw(dxCommon);
}
//前面描画
void IntroductionSceneActor::FrontDraw() {
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
void IntroductionSceneActor::GameDraw(DirectXCommon* dxCommon)
{
	//スプライトの描画
	ModelDraw(dxCommon);
}
//ImGui描画
void IntroductionSceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
}
//解放
void IntroductionSceneActor::Finalize() {
}
//演出
void IntroductionSceneActor::Movie() {
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