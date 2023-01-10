#include "PlayerDushEffect.h"
#include"Collision.h"
#include"Easing.h"
#include"ImageManager.h"
using namespace DirectX;
//�ǂݍ���
PlayerDushEffect::PlayerDushEffect() {

}
//������
void PlayerDushEffect::Initialize() {
	//�G�t�F�N�g�̏�����
	IKETexture* DushEffecttexture_ = IKETexture::Create(ImageManager::DushEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	DushEffecttexture_->TextureCreate();
	//DushEffecttexture->SetRotation({ 90,0,0 });
	DushEffecttexture_->SetScale(m_DushEffectscale);
	DushEffecttexture.reset(DushEffecttexture_);
}
//�X�V
void PlayerDushEffect::Update(const XMFLOAT3& pos, bool& Effect) {
	//�G�t�F�N�g�̔���

	//�_�b�V��
	DushEffectSet(pos,Effect);
	if (m_DushAlive) {
		DushEffecttexture->Update();
	}
	DushEffecttexture->SetPosition(m_DushEffectpos);
	DushEffecttexture->SetScale(m_DushEffectscale);
}
//�`��
const void PlayerDushEffect::Draw() {
	IKETexture::PreDraw(1);
	if (m_DushAlive) {
		DushEffecttexture->Draw();
	}
}
//�_�b�V���̃G�t�F�N�g
void PlayerDushEffect::DushEffectSet(const XMFLOAT3& pos, bool& Effect) {
	if (!m_DushAlive && Effect && !m_DeleteEffect) {
		m_DushEffectpos = pos;
		m_DushAlive = true;
	}

	//�_�b�V��
	if (m_DushAlive) {
		m_DushEffectscale.x += 0.05f;
		m_DushEffectscale.y += 0.05f;
		m_DushEffectscale.z += 0.05f;
		if (m_DushEffectscale.x >= 0.5f) {
			m_DushEffectscale = { 0.0f,0.0f,0.0f };
			m_DeleteEffect = true;
			m_DushAlive = false;
			Effect = false;
		}
	}
}
