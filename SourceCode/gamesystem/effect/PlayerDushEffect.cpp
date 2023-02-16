#include "PlayerDushEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
//�ǂݍ���
PlayerDushEffect::PlayerDushEffect() {
}
//������
void PlayerDushEffect::Initialize() {
	//�G�t�F�N�g�̏�����
	IKETexture* DushEffecttexture_ = IKETexture::Create(ImageManager::DushEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	DushEffecttexture_->TextureCreate();
	DushEffecttexture_->SetScale(m_DushEffectscale);
	DushEffecttexture.reset(DushEffecttexture_);
}
//�X�V
void PlayerDushEffect::Update() {
	//�G�t�F�N�g�̔���
	//�_�b�V��
	DushEffectMove();
	if (m_DushAlive) {
		DushEffecttexture->Update();
	}
	DushEffecttexture->SetPosition(m_DushEffectpos);
	DushEffecttexture->SetScale(m_DushEffectscale);
}
//�`��
const void PlayerDushEffect::Draw() {
	IKETexture::PreDraw(AddBlendType);
	if (m_DushAlive) {
		DushEffecttexture->Draw();
	}
}
//�_�b�V���̃G�t�F�N�g
void PlayerDushEffect::DushEffectSet(const XMFLOAT3& pos) {
	if (!m_DushAlive  && !m_DeleteEffect) {
		m_DushEffectpos = pos;
		m_DushAlive = true;
	}
}
//�G�t�F�N�g�̓���
void PlayerDushEffect::DushEffectMove() {
	float l_AddScale = 0.05f;
	//�_�b�V��
	if (m_DushAlive) {
		m_DushEffectscale.x += l_AddScale;
		m_DushEffectscale.y += l_AddScale;
		m_DushEffectscale.z += l_AddScale;
		if (m_DushEffectscale.x >= 0.5f) {
			m_DushEffectscale = m_ResetThirdFew;
			m_DeleteEffect = true;
			m_DushAlive = false;
		}
	}
}
