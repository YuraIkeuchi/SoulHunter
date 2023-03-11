#include "PlayerDamageEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
#include <random>
using namespace DirectX;
//�ǂݍ���
PlayerDamageEffect::PlayerDamageEffect() {
}
//������
void PlayerDamageEffect::Initialize() {
	IKETexture* damagetex_[DamageEffect_Max];
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		damagetex_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		damagetex_[i]->TextureCreate();
		damagetex[i].reset(damagetex_[i]);
		m_DamageAlive[i] = false;
	}

	IKETexture* HitEffectTexture_;
	HitEffectTexture_ = IKETexture::Create(ImageManager::HitEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	HitEffectTexture_->TextureCreate();
	HitEffectTexture_->SetScale(m_HitScale);
	HitEffectTexture.reset(HitEffectTexture_);

	helper = make_unique< Helper>();
}
//�X�V
void PlayerDamageEffect::Update() {
	//�G�t�F�N�g�̔���
	//�_���[�W
	DamageEffectMove();
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Update();
		}
		damagetex[i]->SetPosition(m_DamageEffectpos[i]);
		damagetex[i]->SetScale(m_DamageEffectscale[i]);
	}

	//�q�b�g�G�t�F�N�g
	HitEffectMove();
	if (m_HitEffect) {
		HitEffectTexture->Update();
	}
	HitEffectTexture->SetPosition(m_HitPos);
	HitEffectTexture->SetScale(m_HitScale);
	HitEffectTexture->SetColor(m_HitColor);
}
//�`��
const void PlayerDamageEffect::Draw() {
	IKETexture::PreDraw(AddBlendType);
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Draw();
		}
	}
	IKETexture::PreDraw(AlphaBlendType);
	if (m_HitEffect) {
		HitEffectTexture->Draw();
	}
}
//�_���[�W�H��������̃G�t�F�N�g
void PlayerDamageEffect::DamageEffectSet(const XMFLOAT3& pos) {
	int l_Division = 10;//����Z�̂��߂̂���
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		//�G�t�F�N�g�̔���
		if (m_DamageAlive[i] == false && !m_DeleteEffect) {
			m_DamageEffectscale[i] = m_BirthDamageScale;
			damagetex[i]->SetColor(m_BirthColor);
			//��������
			mt19937 mt{ std::random_device{}() };
			uniform_int_distribution<int> l_distX(10, 15);
			uniform_int_distribution<int> l_distY(-10, 10);
			m_BoundPower[i].x = float(l_distX(mt)) / l_Division;
			m_BoundPower[i].y = float(l_distY(mt)) / l_Division;
			m_BoundPower[i].z = m_ResetFew;
			if (i % 2 == 0) {
				m_BoundPower[i].x *= -1.0f;
			}
			m_DamageEffectpos[i] = pos;
			m_DamageAlive[i] = true;
		}
	}
}
//�G�t�F�N�g�̓���
void PlayerDamageEffect::DamageEffectMove() {
	float l_AddPowerX = 0.02f;
	float l_AddPowerY = 0.025f;
	float l_SubScale = 0.005f;
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			if (i % 2 == 0) {
				if (m_BoundPower[i].x < m_ResetFew) {
					m_BoundPower[i].x += l_AddPowerX;
				}
				else {
					m_BoundPower[i].x = m_ResetFew;
				}
			}
			else {
				if (m_BoundPower[i].x > m_ResetFew) {
					m_BoundPower[i].x -= l_AddPowerX;
				}
				else {
					m_BoundPower[i].x = m_ResetFew;
				}
			}

			if (m_BoundPower[i].y < 0.2f) {
				m_BoundPower[i].y += l_AddPowerY;
			}

			helper->Float3AddFloat3(m_DamageEffectpos[i], m_BoundPower[i]);
			helper->Float3SubFloat(m_DamageEffectscale[i], l_SubScale);
			if (helper->CheckMax(m_DamageEffectscale[i].x,m_ResetFew,m_ResetFew)) {
				m_DamageEffectscale[i] = m_ResetThirdFew;
				m_DamageAlive[i] = false;
				m_DeleteEffect = true;
			}
		}
	}
}
//�q�b�g�G�t�F�N�g
void PlayerDamageEffect::HitEffectSet(const XMFLOAT3& pos) {
	//�G�t�F�N�g�o��
	if (m_HitEffect == false  && !m_DeleteHitEffect) {
		m_HitScale = m_BirthHitScale;
		m_HitPos = pos;
		m_HitColor = m_BirthHitColor;
		m_HitEffect = true;
	}

}
//�q�b�g�G�t�F�N�g����
void PlayerDamageEffect::HitEffectMove() {
	float l_AddColor = 0.1f;
	//�G�t�F�N�g����
	if (m_HitEffect) {
		helper->Float3AddFloat(m_HitScale, l_AddColor);
		if (helper->CheckMax(m_HitColor.w,m_ColorMin,-l_AddColor)) {
			m_HitColor = m_ResetFourthFew;
			m_HitScale = m_ResetThirdFew;
			m_HitEffect = false;
			m_DeleteHitEffect = true;
		}
	}
}