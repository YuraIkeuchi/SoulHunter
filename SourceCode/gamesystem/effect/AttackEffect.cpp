#include "AttackEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
using namespace DirectX;
//�ǂݍ���
AttackEffect::AttackEffect() {
	IKETexture* AttackEffecttexture_;
	AttackEffecttexture_ = IKETexture::Create(ImageManager::AttackEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	AttackEffecttexture_->TextureCreate();
	AttackEffecttexture_->SetScale(m_Scale);
	AttackEffecttexture.reset(AttackEffecttexture_);
	helper = make_unique< Helper>();
}
//������
void AttackEffect::Initialize() {
}
//�X�V
void AttackEffect::Update() {
	if (m_AttackAlive) {
		EffectMove();
		AttackEffecttexture->Update();
	}
	AttackEffecttexture->SetColor(m_Color);
	AttackEffecttexture->SetPosition(m_Position);
	AttackEffecttexture->SetScale(m_Scale);
}
//�`��
void AttackEffect::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	if (m_AttackAlive) {
		AttackEffecttexture->Draw();
	}
}
//�G�t�F�N�g�̓���
void AttackEffect::SetEffect(const XMFLOAT3& pos,int Dir) {
	//�U���̃G�t�F�N�g�̔��������u��
	if (!m_AttackAlive) {
		m_Position = pos;
		m_Color = m_BirthColor;
		m_Scale = m_BirthScale;
		m_AttackAlive = true;
	
		AttackEffecttexture->SetPosition(m_Position);
		AttackEffecttexture->SetColor(m_Color);
		AttackEffecttexture->SetScale(m_Scale);
		if (Dir == 0) {
			m_AddPower = 0.3f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,180.0f });
		}
		else {
			m_AddPower = -0.3f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,0.0f });
		}
	}
}
//�G�t�F�N�g�̓���
void AttackEffect::EffectMove() {
	float l_AddScale = 0.2f;//���Z�����傫��
	float l_SubColor = 0.1f;//���Z�����F
	//�������Ă���̓���
	if (m_AttackAlive) {
		m_Position.x += m_AddPower;
		helper->Float3AddFloat(m_Scale, l_AddScale);
		if (helper->CheckMax(m_Color.w,m_ColorMin,-l_SubColor)) {
			m_Color.w = m_ColorMin;
			m_Scale = m_ResetThirdFew;
			m_AttackAlive = false;
		}
	}
}