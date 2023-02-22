#include "ClearScene.h"
#include "SceneManager.h"
#include <Easing.h>
#include "ImageManager.h"
#include "VariableCommon.h"
#include "Audio.h"
ClearObj* ClearScene::clearobj = nullptr;
bool ClearScene::m_ClearNew = false;
//������
void ClearScene::Initialize(DirectXCommon* dxCommon) {
	//�J�������[�N
	camerawork = new CameraWork();
	camerawork->SetCameraType(5);
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//Json
	if (!m_ClearNew) {
		clearobj = new ClearObj();
		clearobj->Initialize();
		m_ClearNew = true;
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

	IKESprite* ClearSprite_;
	ClearSprite_ = IKESprite::Create(ImageManager::ClearText, { 0.0f,0.0f });
	ClearSprite.reset(ClearSprite_);
	ClearSprite->SetPosition(m_ClearPos);

	//�V�[���`�F���W
	scenechange = new SceneChange();
	scenechange->SetSubStartChange(true);

	//�v���C���[
	clearplayer = new ClearPlayer();
	clearplayer->Initialize();
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetPointLightActive(1, false);
	//���C�g
	m_LightPos = { 5.0f,5.0f,-80.0f };

	//�v���C���[���K�v
	camerawork->SetClearPlayer(clearplayer);
	//�I�[�f�B�I
	Audio::GetInstance()->LoadSound(3, "Resources/Sound/BGM/jto3s-8fzcz.wav");
	Audio::GetInstance()->LoopWave(3, VolumManager::GetInstance()->GetBGMVolum());
}
//�X�V
void ClearScene::Update(DirectXCommon* dxCommon) {
	m_Timer++;
	Input* input = Input::GetInstance();
	lightGroup->Update();
	//�ۉe
	lightGroup->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0], circleShadowDir[1], circleShadowDir[2], 0 }));
	lightGroup->SetCircleShadowCasterPos(0, XMFLOAT3({ clearplayer->GetPosition().x, clearplayer->GetPosition().y, clearplayer->GetPosition().z }));
	lightGroup->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	clearobj->Update(m_Timer);
	//�J�����̈ʒu����
	camerawork->Update(camera);
	//camerawork->SetClearTimer(m_Timer);

	if (input->TriggerButton(input->Button_A) && !scenechange->GetSubStartChange()) {
		scenechange->SetAddStartChange(true);
	}

	//���o
	Movie();
	clearplayer->ClearMove(m_Timer);
	clearplayer->Update();
	//���̂܂܃V�[���`�F���W
	if (scenechange->AddBlack(0.05f)) {
		Audio::GetInstance()->StopWave(3);
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	ClearSprite->SetPosition(m_ClearPos);
	scenechange->Update();
	scenechange->SubBlack(0.05f);
	postEffect->SetSepia(m_Sepia);
}
//�`��
void ClearScene::Draw(DirectXCommon* dxCommon) {
	//�|�X�g�G�t�F�N�g�������邩
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
//�w�i
void ClearScene::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	clearobj->BackDraw();
	IKEObject3d::PostDraw();
	clearplayer->Draw(dxCommon);
}
//�O�ʕ`��
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
//��̕`��ɃX�v���C�g�Ȃǂ�������
void ClearScene::GameDraw(DirectXCommon* dxCommon)
{
	//�X�v���C�g�̕`��
	ModelDraw(dxCommon);
}
//ImGui�`��
void ClearScene::ImGuiDraw(DirectXCommon* dxCommon) {
}
//���
void ClearScene::Finalize() {
	delete postEffect;
	delete save;
}
//�|�X�g�G�t�F�N�g��Imgui
void ClearScene::PostImGuiDraw(DirectXCommon* dxCommon) {

}
//�|�X�g�G�t�F�N�g�̎��
void ClearScene::ChangePostEffect(int PostType) {

}
//���o
void ClearScene::Movie() {
	//��莞�ԗ��Ɖ�ʂ��Â��Ȃ�
	if (m_Timer == 100) {
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

		m_ClearPos.y -= 1.0f;
	}

	if (m_Timer == 1550) {
		scenechange->SetAddStartChange(true);
	}
}