#include "AttackEffect.h"
#include"Easing.h"
#include"ImageManager.h"
using namespace DirectX;
//�ǂݍ���
AttackEffect::AttackEffect() {

	IKETexture* AttackEffecttexture_;
	AttackEffecttexture_ = IKETexture::Create(ImageManager::AttackEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	AttackEffecttexture_->TextureCreate();
	//DushEffecttexture->SetRotation({ 90,0,0 });
	AttackEffecttexture_->SetScale(m_Scale);
	AttackEffecttexture.reset(AttackEffecttexture_);
}
//������
void AttackEffect::Initialize() {
	
}
//�X�V
void AttackEffect::Update() {

	if (m_AttackAlive) {
		EffectMove();
		//object3d->Update();
		AttackEffecttexture->Update();
	}
	AttackEffecttexture->SetColor(m_Color);
	AttackEffecttexture->SetPosition(m_Pos);
	//AttackEffecttexture->SetRotation(m_rot[i]);
	AttackEffecttexture->SetScale(m_Scale);
}
//�`��
void AttackEffect::Draw() {
	////bool AttackEffect = Jump->GetEffect();
	//ImGui::Begin("AttackEffect");
	//ImGui::Text("m_Pos.x::%f", m_Color.w);
	//ImGui::End();
	IKETexture::PreDraw(0);
	if (m_AttackAlive) {
		AttackEffecttexture->Draw();
	}
}
//�G�t�F�N�g�̓���
void AttackEffect::SetEffect(const XMFLOAT3& pos,int Dir) {
	//�U���̃G�t�F�N�g�̔��������u��
	if (!m_AttackAlive) {
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;
		m_Color = { 3.0f,3.0f,3.0f,1.0f };
		m_Scale = { 0.5f,0.5f,0.5f };
		m_AttackAlive = true;
	
		AttackEffecttexture->SetPosition(m_Pos);
		AttackEffecttexture->SetColor(m_Color);
		AttackEffecttexture->SetScale(m_Scale);
		if (Dir == 0) {
			m_AddPower = 0.2f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,180.0f });
		}
		else {
			m_AddPower = -0.2f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,0.0f });
		}
	}
}
//�G�t�F�N�g�̓���
void AttackEffect::EffectMove() {
	//�������Ă���̓���
	if (m_AttackAlive) {
		m_Pos.x += m_AddPower;
		m_Scale.x += 0.2f;
		m_Scale.y += 0.2f;
		m_Scale.z += 0.2f;
		m_Color.w -= 0.1f;
		if (m_Color.w < 0.0f) {
			m_Color.w = 0.0f;
			m_Scale = { 0.0f,0.0f,0.0f };
			m_AttackAlive = false;
		}
	}
}