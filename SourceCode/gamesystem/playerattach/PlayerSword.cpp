#include "PlayerSword.h"
#include "ModelManager.h"
#include "VariableCommon.h"
#include "Easing.h"
PlayerSword* PlayerSword::GetInstance()
{
	static PlayerSword instance;

	return &instance;
}

bool PlayerSword::Initialize() {
	m_FollowModel = ModelManager::GetInstance()->GetModel(ModelManager::Sword);
	IKEObject3d* m_FollowObject_ = new IKEObject3d();
	m_FollowObject_ = IKEObject3d::Create();
	m_FollowObject_->SetModel(m_FollowModel);
	m_FollowObject_->SetScale(m_Scale);
	m_FollowObject.reset(m_FollowObject_);


	SwordParticle* swordparticle_ = new SwordParticle();
	swordparticle_->Initialize();
	swordparticle.reset(swordparticle_);

	m_Scale = { 4.5f, 4.5f, 4.5f };
	m_Color = { 1.0f, 1.0f, 0.0f, 0.0f };
	return true;
}

void PlayerSword::Update() {
	SwordUpdate();
	ParticleUpdate();
}
//�`��
void PlayerSword::Draw(DirectXCommon* dxCommon) {
	
	if (m_Color.w >= 0.1f) {
		FollowObj_Draw();
	}
}
//Imgui�`��
void PlayerSword::ImGuiDraw() {
	ImGui::Begin("playersword");
	ImGui::Text("m_Color:%f", m_Color.w);
	ImGui::Text("m_PosX:%f", m_Position.x);
	ImGui::Text("m_PosY:%f", m_Position.y);
	ImGui::Text("m_RotX:%f", m_Rotation.x);
	ImGui::Text("m_RotY:%f", m_Rotation.y);
	ImGui::Text("m_Ease:%d", m_SwordEase);
	ImGui::End();
}

//���̍X�V
void PlayerSword::SwordUpdate() {
	XMVECTOR l_VectorSwordPos;
	//�s������߂�
	l_VectorSwordPos.m128_f32[0] = m_HandMat.r[3].m128_f32[0];
	l_VectorSwordPos.m128_f32[1] = m_HandMat.r[3].m128_f32[1];
	l_VectorSwordPos.m128_f32[2] = m_HandMat.r[3].m128_f32[2];
	//�ϊ�
	m_Position.x = l_VectorSwordPos.m128_f32[0];
	m_Position.y = l_VectorSwordPos.m128_f32[1];
	m_Position.z = l_VectorSwordPos.m128_f32[2];

	m_SwordMatRot = m_FollowObject->GetMatrot();
	if (m_SwordEase) {
		if (m_SwordFrame < m_FrameMax) {
			m_SwordFrame += 0.1f;
		}
		else {
			m_SwordFrame = 0.0f;
			m_SwordEase = false;
			m_SwordType = NoSword;
		}
		m_Color.w = Ease(In, Cubic, m_SwordFrame, m_Color.w, m_SwordAfterAlpha);
	}


	m_FollowObject->SetRotation(m_Rotation);
	m_FollowObject->SetScale(m_Scale);
	m_FollowObject->SetColor(m_Color);
	FollowObj_SetParam(m_HandMat);
}
//�p�[�e�B�N���X�V
void PlayerSword::ParticleUpdate() {

	//���̃p�[�e�B�N���̏ꏊ�����߂�
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };
	m_SwordParticleCount = 1;
	swordparticle->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	for (int i = 0; i < m_SwordParticleNum; i++) {
		swordparticle->SetParticle(m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	}
	swordparticle->Update(m_SwordParticlePos, m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
}

void PlayerSword::ParticleDraw() {
	swordparticle->Draw();
}

void PlayerSword::SwordBirth() {
	//���̏���
	m_SwordEase = true;
	m_SwordFrame = 0.0f;
	m_SwordType = ArgSword;
	m_SwordAfterAlpha = 1.0f;
}

void PlayerSword::SwordFinish() {
	m_SwordEase = true;
	m_SwordFrame = 0.0f;
	m_SwordType = DeleteSword;
	m_SwordAfterAlpha = 0.0f;
	m_SwordParticleCount = 0;
}