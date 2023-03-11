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
	DushEffecttexture_->SetScale(m_Scale);
	DushEffecttexture.reset(DushEffecttexture_);

	helper = unique_ptr< Helper>();
}
//�X�V
void PlayerDushEffect::Update() {
	//�G�t�F�N�g�̔���
	//�_�b�V��
	DushEffectMove();
	if (m_DushAlive) {
		DushEffecttexture->Update();
	}
	DushEffecttexture->SetPosition(m_Position);
	DushEffecttexture->SetScale(m_Scale);
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
		m_Position = pos;
		m_DushAlive = true;
	}
}
//�G�t�F�N�g�̓���
void PlayerDushEffect::DushEffectMove() {
	float l_AddScale = 0.05f;
	float l_targetScale = 0.5f;
	//�_�b�V��
	if (m_DushAlive) {
		helper->Float3AddFloat(m_Scale, l_AddScale);
		if (helper->CheckMin(m_Scale.x, l_targetScale,m_ResetFew)) {
			m_Scale = m_ResetThirdFew;
			m_DeleteEffect = true;
			m_DushAlive = false;
		}
	}
}
