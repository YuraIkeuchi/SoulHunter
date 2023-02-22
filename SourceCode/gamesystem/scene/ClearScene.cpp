#include "ClearScene.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "Audio.h"
ClearObj* ClearScene::clearobj = nullptr;
bool ClearScene::m_ClearNew = false;
//初期化
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//カメラワーク
	camerawork = new CameraWork();
	camerawork->SetCameraType(5);
	//共通の初期化
	BaseInitialize(dxCommon);
	//Json
	if (!m_ClearNew) {
		clearobj = new ClearObj();
		clearobj->Initialize();
		m_ClearNew = true;
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

	IKESprite* ClearSprite_;
	ClearSprite_ = IKESprite::Create(ImageManager::ClearText, { 0.0f,0.0f });
	ClearSprite.reset(ClearSprite_);
	ClearSprite->SetPosition(m_ClearPos);

	//シーンチェンジ
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);

	//プレイヤー
	clearplayer = new ClearPlayer();
	clearplayer->Initialize();
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	//ライト
	m_LightPos = { 5.0f,5.0f,-80.0f };

	//プレイヤーが必要
	camerawork->SetClearPlayer(clearplayer);
	//オーディオ
	Audio::GetInstance()->LoadSound(3, "Resources/Sound/BGM/jto3s-8fzcz.wav");
	Audio::GetInstance()->LoopWave(3, VolumManager::GetInstance()->GetBGMVolum());
}
//更新
void ClearScene::Update(DirectXCommon* dxCommon) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightGroup->Update();
	//丸影
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ clearplayer->GetPosition().x, clearplayer->GetPosition().y, clearplayer->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	clearobj->Update(m_Timer);
	//カメラの位置調整
	camerawork->Update(camera);
	//camerawork->SetClearTimer(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}

	//演出
	Movie();
	clearplayer->ClearMove(m_Timer);
	clearplayer->Update();
	//そのままシーンチェンジ
	if (scenechange->AddBlack(0.05f)) {
		Audio::GetInstance()->StopWave(3);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	ClearSprite->SetPosition(m_ClearPos);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
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
		ImGuiDraw(dxCommon);
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
void ClearScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	clearobj->BackDraw();
	IKEObject3d::PostDraw();
	clearplayer->Draw(dxCommon);
}
//前面描画
void ClearScene::FrontDraw() {
	IKEObject3d::PreDraw();
	clearobj->FrontDraw();
	IKEObject3d::PostDraw();
	IKESprite::PreDraw();
	ClearSprite->Draw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	scenechange->Draw();
	IKESprite::PostDraw();
}
//上の描画にスプライトなども混ぜた
void ClearScene::GameDraw(DirectXCommon* dxCommon)
{
	//スプライトの描画
	ModelDraw(dxCommon);
}
//ImGui描画
void ClearScene::ImGuiDraw(DirectXCommon* dxCommon) {
}
//解放
void ClearScene::Finalize() {
	delete postEffect;
	delete save;
}
//ポストエフェクトのImgui
void ClearScene::PostImGuiDraw(DirectXCommon* dxCommon) {

}
//ポストエフェクトの種類
void ClearScene::ChangePostEffect(int PostType) {

}
//演出
void ClearScene::Movie() {
	//一定時間立つと画面が暗くなる
	if (m_Timer == 100) {
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

		m_ClearPos.y -= 1.0f;
	}

	if (m_Timer == 1550) {
		scenechange->SetAddStartChange(true);
	}
}