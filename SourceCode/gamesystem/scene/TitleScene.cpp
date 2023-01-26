#include "TitleScene.h"
#include "Audio.h"
#include "input.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
TitleObj* TitleScene::titleobj = nullptr;
bool TitleScene::m_TitleNew = false;
//������
void TitleScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�X�v���C�g����
	IKESprite* TitlePartsSprite_[3];
	//gaussian = new PostEffect();
	const int TitleCount = 3;
	for (int i = 0; i < TitlePartsSprite.size(); i++) {
		TitlePartsSprite_[i] = IKESprite::Create(ImageManager::TitleParts, { 0.0f,0.0f });
		int number_index_y = i / TitleCount;
		int number_index_x = i % TitleCount;
		TitlePartsSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * PartsWidth_Cut, static_cast<float>(number_index_y) * PartsHeight_Cut },
			{ static_cast<float>(PartsWidth_Cut), static_cast<float>(PartsHeight_Cut) });
		TitlePartsSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		TitlePartsSprite[i].reset(TitlePartsSprite_[i]);
		m_PartsSize[i] = { PartsWidth_Cut,PartsHeight_Cut };
	}

	m_PartsPos[NewGame] = { 640.0f,480.0f };
	m_PartsPos[LoadGame] = { 640.0f,640.0f };
	m_PartsPos[SelectGame] = { 640.0f,480.0f };

	IKESprite* TitleSprite_;
	TitleSprite_ = IKESprite::Create(ImageManager::Title, { 0.0f,0.0f });
	TitleSprite.reset(TitleSprite_);

	//�J�������[�N
	camerawork = new CameraWork();
	camerawork->SetCameraType(0);
	
	//Json
	if (!m_TitleNew) {
		titleobj = new TitleObj();
		titleobj->Initialize();
		m_TitleNew = true;
	}
	//���C�g
	m_LightPos = { 0.0f,0.0f,0.0f };

	//�V�[���`�F���W
	scenechange = new SceneChange();
	if (m_GameLoop) {
		scenechange->SetSubStartChange(true);
	}

	//�Z�[�u
	save = new Save();
	m_TitleSelect = NewGame;
	dxCommon->SetFullScreen(true);

	pointLightAtten[0] = 20.0f;
	pointLightAtten[1] = 20.0f;
	pointLightAtten[2] = 20.0f;
	//ParticleEmitter::GetInstance()->AllDelete();
}
//�X�V
void TitleScene::Update(DirectXCommon* dxCommon) {
	Input* input = Input::GetInstance();
	lightGroup->Update();
	titleobj->Update();
	//�J�����̈ʒu����
	camerawork->Update(camera);
	///�|�C���g���C�g
	lightGroup->SetPointLightPos(0, m_LightPos);
	lightGroup->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	lightGroup->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));
	//lightGroup->SetPointLightPower(0, XMFLOAT3(pointLightPower));
	//�j���[�Q�[�������[�h�Q�[������I������
	if (!scenechange->GetAddStartChange()) {
		if (m_TitleSelect == NewGame && input->LeftTriggerStick(input->Down)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_TitleSelect = LoadGame;
		}

		else if (m_TitleSelect == LoadGame && input->LeftTriggerStick(input->Up)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_TitleSelect = NewGame;
		}
	}

	if (input->PushKey(DIK_RETURN) || input->TriggerButton(input->Button_B) && !scenechange->GetSubStartChange() && !scenechange->GetAddStartChange()) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Buttun.wav", VolumManager::GetInstance()->GetSEVolum());
		scenechange->SetAddStartChange(true);
		if (m_TitleSelect == NewGame) {
			m_GameLoad = false;
		}
		else {
			m_GameLoad = true;
		}
	}

	//���C�g�����X�ɏ���������
	if (scenechange->GetAddStartChange()) {
		pointLightAtten[0] = Ease(In, Cubic, 0.1f, pointLightAtten[0], 0.0f);
		pointLightAtten[1] = Ease(In, Cubic, 0.1f, pointLightAtten[1], 0.0f);
		pointLightAtten[2] = Ease(In, Cubic, 0.1f, pointLightAtten[2], 0.0f);
	}

	if (scenechange->AddBlack(0.01f)) {
		if (!m_GameLoad) {
			SceneManager::GetInstance()->ChangeScene("INTRODUCTION");
		}
		else {
			SceneManager::GetInstance()->ChangeScene("LOAD");
		}
	}
	for (int i = 0; i < TitlePartsSprite.size(); i++) {
		TitlePartsSprite[i]->SetPosition(m_PartsPos[i]);
		TitlePartsSprite[i]->SetSize(m_PartsSize[i]);
		TitlePartsSprite[i]->SetColor(m_TitleColor);
	}
	TitleSprite->SetColor(m_TitleColor);
	ParticleEmitter::GetInstance()->FireEffect( 100,{0.0f,23.0f,0.0f}, 5.0f, 0.0f,{ 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });
	//�p�[�e�B�N���X�V
	ParticleEmitter::GetInstance()->Update();
	//�^�C�g���̕���������
	PartsBirth();
	//�^�C�g���̕���������
	PartsMove();
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	ChangePostEffect(PostType);
}
//�`��
void TitleScene::Draw(DirectXCommon* dxCommon) {
	
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
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		//ImGuiDraw(dxCommon);
		//PostImGuiDraw(dxCommon);
		camerawork->ImGuiDraw();
		GameDraw(dxCommon);
		FrontDraw();
		dxCommon->PostDraw();
	}
}
//�w�i
void TitleScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	titleobj->BackDraw();
	IKEObject3d::PostDraw();
}
//�O�ʕ`��
void TitleScene::FrontDraw() {
	IKEObject3d::PreDraw();
	//titleobj->FrontDraw();
	//�p�[�e�B�N���`��
	ParticleEmitter::GetInstance()->FireDrawAll();
	IKEObject3d::PostDraw();
	IKESprite::PreDraw();
	TitleSprite->Draw();
	TitlePartsSprite[2]->Draw();
	for (int i = 0; i < 2; i++) {
		TitlePartsSprite[i]->Draw();
	}
	scenechange->Draw();
	IKESprite::PostDraw();
}
//��̕`��ɃX�v���C�g�Ȃǂ�������
void TitleScene::GameDraw(DirectXCommon* dxCommon)
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
void TitleScene::ImGuiDraw(DirectXCommon* dxCommon) {
	//FPSManager::GetInstance()->ImGuiDraw();
	/*ImGui::Begin("Load");
	ImGui::SliderFloat("m_PartsPos[Newgame]:%f", &m_PartsPos[NewGame].y,-100,200);
	ImGui::End();*/
}
//���
void TitleScene::Finalize() {
	//�R���̃��f���̃f���[�g
	//delete sprite;
	delete postEffect;
	delete save;
}
//�|�X�g�G�t�F�N�g��Imgui
void TitleScene::PostImGuiDraw(DirectXCommon* dxCommon) {
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
void TitleScene::ChangePostEffect(int PostType) {
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

void TitleScene::PartsMove() {
	if (m_TitleSelect == NewGame) {
		m_Angle[NewGame] += 2.0f;
		m_Angle2[NewGame] = m_Angle[NewGame] * (3.14f / 180.0f);
		//�I�������W���㉺�ɓ���
		m_PartsPos[SelectGame] = m_PartsPos[NewGame];

		m_Angle[LoadGame] = 0.0f;
		m_PartsPos[LoadGame].y = 640.0f;
		//�I�����T�C�Y�������ς��
		m_PartsSize[NewGame] = { (sin(m_Angle2[NewGame]) * 32.0f) + (640.0f),
			(sin(m_Angle2[NewGame]) * 16.0f) + (128.0f) };
		m_PartsSize[SelectGame] = m_PartsSize[NewGame];
		m_PartsSize[LoadGame] = { 640.0f,128.0f };
	}
	else {
		m_Angle[LoadGame] += 2.0f;
		m_Angle2[LoadGame] = m_Angle[LoadGame] * (3.14f / 180.0f);
		//�I�������W���㉺�ɓ���
		m_PartsPos[SelectGame] = m_PartsPos[LoadGame];

		m_Angle[NewGame] = 0.0f;
		m_PartsPos[NewGame].y = 480.0f;

		//�I�����T�C�Y�������ς��
		m_PartsSize[LoadGame] = { (sin(m_Angle2[LoadGame]) * 32.0f) + (640.0f),
			(sin(m_Angle2[LoadGame]) * 16.0f - 16.0f) + (128.0f) };
		m_PartsSize[SelectGame] = m_PartsSize[LoadGame];
		m_PartsSize[NewGame] = { 640.0f,128.0f };
	}
}

void TitleScene::PartsBirth() {
	m_TitleTimer++;

	//��莞�ԗ�������^�C�g���̕������o�Ă���
	if (m_TitleTimer >= 50) {
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.005f;
		}
		else {
			m_Frame = m_FrameMax;
		}
	}

	m_TitleColor.w = Ease(In, Cubic, m_Frame, m_TitleColor.w, 1.0f);

}