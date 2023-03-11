#include "PlayerDamageEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
#include <random>
using namespace DirectX;
//読み込み
PlayerDamageEffect::PlayerDamageEffect() {
}
//初期化
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
//更新
void PlayerDamageEffect::Update() {
	//エフェクトの発生
	//ダメージ
	DamageEffectMove();
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Update();
		}
		damagetex[i]->SetPosition(m_DamageEffectpos[i]);
		damagetex[i]->SetScale(m_DamageEffectscale[i]);
	}

	//ヒットエフェクト
	HitEffectMove();
	if (m_HitEffect) {
		HitEffectTexture->Update();
	}
	HitEffectTexture->SetPosition(m_HitPos);
	HitEffectTexture->SetScale(m_HitScale);
	HitEffectTexture->SetColor(m_HitColor);
}
//描画
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
//ダメージ食らった時のエフェクト
void PlayerDamageEffect::DamageEffectSet(const XMFLOAT3& pos) {
	int l_Division = 10;//割り算のためのもの
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		//エフェクトの発生
		if (m_DamageAlive[i] == false && !m_DeleteEffect) {
			m_DamageEffectscale[i] = m_BirthDamageScale;
			damagetex[i]->SetColor(m_BirthColor);
			//乱数生成
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
//エフェクトの動き
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
//ヒットエフェクト
void PlayerDamageEffect::HitEffectSet(const XMFLOAT3& pos) {
	//エフェクト出現
	if (m_HitEffect == false  && !m_DeleteHitEffect) {
		m_HitScale = m_BirthHitScale;
		m_HitPos = pos;
		m_HitColor = m_BirthHitColor;
		m_HitEffect = true;
	}

}
//ヒットエフェクト動く
void PlayerDamageEffect::HitEffectMove() {
	float l_AddColor = 0.1f;
	//エフェクト動く
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