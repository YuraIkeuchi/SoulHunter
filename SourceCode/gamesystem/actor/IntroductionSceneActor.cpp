#include "IntroductionSceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "imgui.h"
IntroductionObj* IntroductionSceneActor::Introductionobj = nullptr;
bool IntroductionSceneActor::m_IntroNew = false;
//������
void IntroductionSceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
	//�J�������[�N
	camerawork = new CameraWork();
	camerawork->SetCameraType(1);
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//Json
	if (!m_IntroNew) {
		Introductionobj = new IntroductionObj();
		Introductionobj->Initialize();
		m_IntroNew = true;
	}
	//�X�v���C�g����
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

	//�V�[���`�F���W
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);

	//�v���C���[
	introplayer = make_unique<IntroPlayer >();
	introplayer->Initialize();

	//�v���C���[���K�v
	camerawork->SetIntroPlayer(introplayer.get());

	//���C�g
	lightgroup->SetDirLightActive(0, true);
	lightgroup->SetDirLightActive(1, true);
	lightgroup->SetDirLightActive(2, true);
	lightgroup->SetPointLightActive(0, false);
	lightgroup->SetPointLightActive(1, false);

	//�|�X�g�G�t�F�N�g�̃t�@�C���w��
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");

	//�I�[�f�B�I
	Audio::GetInstance()->LoadSound(2, "Resources/Sound/BGM/8bo8k-1eq6w.wav");
	Audio::GetInstance()->LoopWave(2, VolumManager::GetInstance()->GetBGMVolum());
}
//�X�V
void IntroductionSceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightgroup->Update();
	//�ۉe
	lightgroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightgroup->SetCircleShadowCasterPos(0, XMFLOAT3({ introplayer->GetPosition().x, introplayer->GetPosition().y, introplayer->GetPosition().z }));
	lightgroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightgroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	Introductionobj->Update(m_Timer);
	//�J�����̈ʒu����
	camerawork->Update(camera);
	camerawork->SetIntroTimer(m_Timer);
	//�v���C���[�̍X�V
	introplayer->Update();
	introplayer->IntroMove(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}

	//���o
	Movie();

	//���̂܂܃V�[���`�F���W
	if (scenechange->AddBlack(0.05f)) {
		Audio::GetInstance()->StopWave(2);
		SceneManager::GetInstance()->ChangeScene("LOAD");
	}

	IntroSprite->SetColor(m_TextColor);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	postEffect->SetSepia(m_Sepia);
}
//�`��
void IntroductionSceneActor::Draw(DirectXCommon* dxCommon) {

	//�|�X�g�G�t�F�N�g�������邩
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
//�w�i
void IntroductionSceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	Introductionobj->BackDraw();

	IKEObject3d::PostDraw();
	introplayer->Draw(dxCommon);
}
//�O�ʕ`��
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
//��̕`��ɃX�v���C�g�Ȃǂ�������
void IntroductionSceneActor::GameDraw(DirectXCommon* dxCommon)
{
	//�X�v���C�g�̕`��
	ModelDraw(dxCommon);
}
//ImGui�`��
void IntroductionSceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
}
//���
void IntroductionSceneActor::Finalize() {
}
//���o
void IntroductionSceneActor::Movie() {
	//��莞�ԗ��Ɖ�ʂ��Â��Ȃ�
	if (m_Timer == 420) {
		PlayPostEffect = true;
	}

	//�Z�s�A�J���[�ɂȂ�
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

	//��莞�ԂŃV�[�����ς��
	if (m_TextColor.w == 1.0f) {
		m_ChangeTimer++;

		if (m_ChangeTimer == 200) {

			scenechange->SetAddStartChange(true);
		}
	}
}