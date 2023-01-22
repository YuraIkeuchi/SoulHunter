#include "IntroductionScene.h"
#include "Audio.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "imgui.h"
IntroductionObj* IntroductionScene::Introductionobj = nullptr;
bool IntroductionScene ::m_IntroNew = false;
//������
void IntroductionScene::Initialize(DirectXCommon* dxCommon) {
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
	player = new Player();
	player->Initialize();
	player->StateInitialize();
	
	//�v���C���[���K�v
	camerawork->SetPlayer(player);
	
	//���C�g
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	//�|�X�g�G�t�F�N�g�̃t�@�C���w��
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/SepiaPS.hlsl");
}
//�X�V
void IntroductionScene::Update(DirectXCommon* dxCommon) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightGroup->Update();
	//�ۉe
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ player->GetPosition().x, player->GetPosition().y, player->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	Introductionobj->Update(m_Timer);
	//�J�����̈ʒu����
	camerawork->Update(camera);
	camerawork->SetIntroTimer(m_Timer);
	//�v���C���[�̍X�V
	player->IntroductionUpdate(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}
	
	
	//���o
	Movie();

	//���̂܂܃V�[���`�F���W
	if (scenechange->AddBlack(0.05f)) {
		SceneManager::GetInstance()->ChangeScene("LOAD");
	}

	IntroSprite->SetColor(m_TextColor);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	ChangePostEffect(PostType);
	postEffect->SetSepia(m_Sepia);
}
//�`��
void IntroductionScene::Draw(DirectXCommon* dxCommon) {

	//�|�X�g�G�t�F�N�g�������邩
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
//�w�i
void IntroductionScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	Introductionobj->BackDraw();

	IKEObject3d::PostDraw();
	player->IntroductionDraw(dxCommon);
}
//�O�ʕ`��
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
//��̕`��ɃX�v���C�g�Ȃǂ�������
void IntroductionScene::GameDraw(DirectXCommon* dxCommon)
{
	//ImGuiDraw();
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����

#pragma endregion
	//�X�v���C�g�̕`��
	ModelDraw(dxCommon);
	//FBX�̕`��
	//object1->Draw(dxCommon->GetCmdList());
}
//ImGui�`��
void IntroductionScene::ImGuiDraw(DirectXCommon* dxCommon) {
	////FPSManager::GetInstance()->ImGuiDraw();
	//ImGui::Begin("Introduce");
	//ImGui::Text("Timer:%d",m_Timer);
	//ImGui::End();
}
//���
void IntroductionScene::Finalize() {
	//�R���̃��f���̃f���[�g
	//delete sprite;
	delete postEffect;
	delete save;
}
//�|�X�g�G�t�F�N�g��Imgui
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
//�|�X�g�G�t�F�N�g�̎��
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
//���o
void IntroductionScene::Movie() {
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