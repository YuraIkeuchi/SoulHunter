#include "BossEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
#include <random>
//読み込み
BossEffect::BossEffect() {
	IKETexture* ParticleEffect_[Effect_Max];
	for (int i = 0; i < ParticleEffect.size(); i++) {
		ParticleEffect_[i] = IKETexture::Create(ImageManager::DamageEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		ParticleEffect_[i]->TextureCreate();
		m_Scale[i] = { 0.0f,0.0f,0.0f };

		ParticleEffect_[i]->SetScale(m_Scale[i]);
		ParticleEffect[i].reset(ParticleEffect_[i]);
	}

	IKETexture* HitEffectTexture_;
	HitEffectTexture_ = IKETexture::Create(ImageManager::HitEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	HitEffectTexture_->TextureCreate();
	HitEffectTexture_->SetScale(m_HitScale);
	HitEffectTexture.reset(HitEffectTexture_);

	helper = make_unique< Helper>();
}
//初期化
void BossEffect::Initialize() {
	for (int i = 0; i < ParticleEffect.size(); i++) {
		m_Effect[i] = false;
		m_BoundPower[i] = m_ResetThirdFew;
		m_Color[i] = m_ResetFourthFew;
		m_Pos[i] = m_ResetThirdFew;
		m_Scale[i] = m_ResetThirdFew;
	}
}
//更新
void BossEffect::Update(const XMFLOAT3& pos, bool& Effect, int HitDir) {
	SetEffect(pos, Effect, HitDir);
	SetHitEffect(pos, Effect);
	for (int i = 0; i < ParticleEffect.size(); i++) {
		if (m_Effect[i]) {
			ParticleEffect[i]->Update();
		
		}
		ParticleEffect[i]->SetPosition(m_Pos[i]);
		ParticleEffect[i]->SetColor(m_Color[i]);
		ParticleEffect[i]->SetScale(m_Scale[i]);
	}
	HitEffectTexture->Update();
	HitEffectTexture->SetPosition(m_HitPos);
	HitEffectTexture->SetScale(m_HitScale);
	HitEffectTexture->SetColor(m_HitColor);
}
//描画
void BossEffect::Draw() {
	IKETexture::PreDraw(AddBlendType);
	for (int i = 0; i < ParticleEffect.size(); i++) {
		if (m_Effect[i] && (m_Scale[i].x >= 0.0f && m_Scale[i].x <= 0.5f)) {
			ParticleEffect[i]->Draw();
		}
	}

	IKETexture::PreDraw(AlphaBlendType);
	if (m_HitEffect) {
		HitEffectTexture->Draw();
	}
}
//エフェクトの動き
void BossEffect::SetEffect(const XMFLOAT3& pos, bool& Effect, int HitDir) {
	int l_Division = 800;
	//目標の大きさ
	float l_TargetScale = 0.5f;
	//エフェクトの発生
	for (int i = 0; i < ParticleEffect.size(); i++) {
		//
		if (!m_Effect[i] && Effect && !m_DeleteEffect) {
			//乱数指定(-50から50)
			mt19937 mt{ std::random_device{}() };
			uniform_int_distribution<int> l_bounddist(-50, 50);
			//大きさの乱数
			uniform_int_distribution<int> l_scaledist(20, 40);
			m_Pos[i] = pos;
			m_BoundPower[i] = {
					(float)(l_bounddist(mt)) / l_Division,
					(float)(l_bounddist(mt)) / l_Division,
					0.0f,
			};
			m_AddScale[i] = (float)(l_scaledist(mt)) / l_Division;
			m_Scale[i] = m_ResetThirdFew;
			m_Color[i] = m_BirthColor;
			m_ScaleChange[i] = false;
			m_Effect[i] = true;
		}

		if (m_Effect[i]) {
			helper->Float3AddFloat3(m_Pos[i], m_BoundPower[i]);
			if (!m_ScaleChange[i]) {
				helper->Float3AddFloat(m_Scale[i], m_AddScale[i]);
				if (m_Scale[i].x >= l_TargetScale) {
					m_ScaleChange[i] = true;
				}
			}
			else {
				helper->Float3SubFloat(m_Scale[i], m_AddScale[i]);
				if (helper->CheckMax(m_Scale[i].x, m_ResetFew, m_ResetFew)) {
					m_Scale[i] = m_ResetThirdFew;
					m_ScaleChange[i] = false;
					m_Effect[i] = false;
					m_DeleteEffect = true;
					Effect = false;
				}
			}
		}
	}
}
//ヒットエフェクト
void BossEffect::SetHitEffect(const XMFLOAT3& pos, bool& Effect) {
	float l_AddScale = 0.05f;
	float l_AddColor = 0.05f;
	//エフェクト出現
	if (m_HitEffect == false && Effect && !m_DeleteHitEffect) {
		m_HitScale = { 0.1f,0.1f,0.1f };
		m_HitPos = { pos.x, pos.y, pos.z - 5.0f, };
		m_HitColor = { 1.0f,1.0f,1.0f,1.0f };
		m_HitEffect = true;
	}

	//エフェクト動く
	if (m_HitEffect) {
		helper->Float3AddFloat(m_HitScale, l_AddScale);
		if (helper->CheckMax(m_HitColor.w, m_ColorMin, -l_AddColor)) {
			m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
			m_HitScale = { 0.0f,0.0f,0.0f };
			m_HitEffect = false;
			m_DeleteHitEffect = true;
		}
	}
}