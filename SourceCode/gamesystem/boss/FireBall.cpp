#include "FireBall.h"
#include "ImageManager.h"
#include "Collision.h"
#include "ParticleEmitter.h"
#include "VariableCommon.h"
//�ǂݍ���
FireBall::FireBall() {
	IKETexture* firetex_;
	firetex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	firetex_->TextureCreate();
	firetex_->SetPosition({ 0.0f,90.0f,0.0f });
	firetex.reset(firetex_);
}
//������
bool FireBall::Initialize() {
	m_Scale = { 0.4f, 0.4f, 0.4f };
	m_Color = { 1.0f,0.5f,0.0f,1.0f };
	return true;
}
//�X�V
void FireBall::Update() {
	XMFLOAT2 l_MinPos = { -140.0f,-155.0f };
	XMFLOAT2 l_MaxPos = { 250.0f,-100.0f };
	m_OldPos = m_Position;
	Shot();
	BirthParticle();
	//�X�V�ƃZ�b�g
	if (m_Alive) {
		firetex->Update();
		//Obj_SetParam();
	}
	if ((m_Position.x <= l_MinPos.x || m_Position.x >= l_MaxPos.x) || (l_MinPos.y <= -155.0f || m_Position.y >= l_MaxPos.y)) {
		m_Alive = false;
	}
	firetex->SetColor(m_Color);
	firetex->SetPosition(m_Position);
	firetex->SetScale(m_Scale);
}
//�|�[�Y��
void FireBall::Pause() {
	if (m_Alive) {
		firetex->Update();
	}
}
//�`��
void FireBall::Draw(DirectXCommon* dxCommon) {
	IKETexture::PreDraw(AddBlendType);
	if (m_Alive) {
	firetex->Draw();
	}
}
//���ۂɒe������
void FireBall::Shot() {
	//�e���o��������p�[�e�B�N������������
	if (m_Alive) {
		m_ParticleCount++;
	
		m_Position.x += m_AddSpeed;
		m_Position.y += m_AddPowerY;
	}
	else {
		m_ParticleCount = 0;
	}
}
//�����蔻��
bool FireBall::Collide(XMFLOAT3 pos) {
	float l_radius = 1.5f;
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_radius, pos.x, pos.y, l_radius)
		 && (m_Alive)) {
		m_Alive = false;
		return true;
	}
	else {
		return false;
	}

	return true;
}
//�p�[�e�B�N��
void FireBall::BirthParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,0.5f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,0.5f };
	float s_scale = 3.0f;
	float e_scale = 0.0f;

	if (m_Alive) {
		ParticleEmitter::GetInstance()->FireEffect(30, { m_Position.x,m_Position.y + 8.0f,m_Position.z }, s_scale, e_scale, s_color, e_color);
	}
}
