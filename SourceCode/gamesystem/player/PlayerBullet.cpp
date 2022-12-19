#include "PlayerBullet.h"
#include "imgui.h"
//�ǂݍ���
PlayerBullet::PlayerBullet() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::Particle);
	IKEObject3d* m_Object_;
	m_Object_ = new IKEObject3d();
	m_Object_ = IKEObject3d::Create();
	//obje3dci]->CreateGraphicsPipeline(L"Resources/shaders/BasicVS.hlsl", L"Resources/shaders/BasicPS.hlsl");
	m_Object_->SetModel(m_Model);

	m_Object.reset(m_Object_);
}
//������
bool PlayerBullet::Initialize() {
	m_Scale = { 1.0f, 1.0f, 1.0f };
	m_Color = { 1.0f,0.5f,0.0f,1.0f };
	m_Object->SetPosition(m_Position);
	m_Object->SetScale(m_Scale);
	//ParticleObj* particleobj_ = new ParticleObj();
	//particleobj_->Initialize();
	//particleobj.reset(particleobj_);

	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
	return true;
}
//�X�V
void PlayerBullet::Update() {
	m_OldPos = m_Position;
	//block->PlayerBulletMapCollideCommon(m_Position, m_Radius, m_Alive, m_OldPos);
	Shot();
	//�X�V�ƃZ�b�g
	if (m_Alive) {
		Obj_SetParam();
	}
	//�p�[�e�B�N���̍X�V
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->SetParticleBreak(true);
	for (int i = 0; i < 2; i++) {
		particletex->Update(m_Position, m_ParticleCount, 2, 0);
	}
}
//�|�[�Y��
void PlayerBullet::Pause() {
	if (m_Alive) {
		m_Object->Update();
	}
}
//�`��
void PlayerBullet::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("playerbullet");
	ImGui::Text("m_PosX::%f", m_Position.x);
	ImGui::Text("m_PosY::%f", m_Position.y);
	ImGui::End();*/
	if (m_Alive) {
		Obj_Draw();
	}
	particletex->Draw();
}
//���ۂɒe������
void PlayerBullet::Shot() {
	//�e���o��������p�[�e�B�N������������
	if (m_Alive) {
		m_ParticleCount++;
		if (m_ParticleCount > 2) {
			m_ParticleCount = 0;
		}
		m_Position.x += m_AddSpeed;
	}
	else {
		m_ParticleCount = 0;
	}
}