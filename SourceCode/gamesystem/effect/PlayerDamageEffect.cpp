#include "PlayerDamageEffect.h"
#include"Easing.h"
#include"ImageManager.h"
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
}
//更新
void PlayerDamageEffect::Update(const XMFLOAT3& pos, bool& Effect) {
	//エフェクトの発生
	//ダメージ
	DamageEffectSet(pos,Effect);
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Update();
		}
		damagetex[i]->SetPosition(m_DamageEffectpos[i]);
		damagetex[i]->SetScale(m_DamageEffectscale[i]);
	}

	//ヒットエフェクト
	SetHitEffect(pos,Effect);
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
void PlayerDamageEffect::DamageEffectSet(const XMFLOAT3& pos, bool& Effect) {
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		//エフェクトの発生
		if (m_DamageAlive[i] == false && Effect && !m_DeleteEffect) {
			m_DamageEffectscale[i] = { 0.3f,0.3f,0.3f };
			damagetex[i]->SetColor({ 1.0f,0.9f,0.8f,1.0f });
			m_BoundPower[i].x = (float)(rand() % 10 + 5) / 10;
			m_BoundPower[i].y = (float)(rand() % 20 - 10) / 10;
			m_BoundPower[i].z = 0.0f;
			if (i % 2 == 0) {
				m_BoundPower[i].x *= -1.0f;
			}
			m_DamageEffectpos[i] = pos;
			m_DamageAlive[i] = true;
		}
		if (m_DamageAlive[i] == true) {
			//m_BoundPower[i].y += 0.01f;
			if (i % 2 == 0) {
				if (m_BoundPower[i].x < 0.0f) {
					m_BoundPower[i].x += 0.02f;
				}
				else {
					m_BoundPower[i].x = 0.0f;
				}
			}
			else {
				if (m_BoundPower[i].x > 0.0f) {
					m_BoundPower[i].x -= 0.02f;
				}
				else {
					m_BoundPower[i].x = 0.0f;
				}
			}

			if (m_BoundPower[i].y < 0.2f) {
				m_BoundPower[i].y += 0.025f;
			}

			m_DamageEffectpos[i].x += m_BoundPower[i].x;
			m_DamageEffectpos[i].y += m_BoundPower[i].y;
			m_DamageEffectpos[i].z += m_BoundPower[i].z;
			m_DamageEffectscale[i].x -= 0.005f;
			m_DamageEffectscale[i].y -= 0.005f;
			m_DamageEffectscale[i].z -= 0.005f;
			if (m_DamageEffectscale[i].x <= 0.0f) {
				m_DamageEffectscale[i] = { 0.0f,0.0f,0.0f };
				m_DamageAlive[i] = false;
				m_DeleteEffect = false;
				Effect = false;
			}
		}
	}
}
//ヒットエフェクト
void PlayerDamageEffect::SetHitEffect(const XMFLOAT3& pos, bool& Effect) {
	//エフェクト出現
	if (m_HitEffect == false && Effect && !m_DeleteHitEffect) {
		m_HitScale = { 0.1f,0.1f,0.1f };
		m_HitPos = pos;
		m_HitColor = { 1.0f,1.0f,1.0f,1.0f };
		m_HitEffect = true;
	}

	//エフェクト動く
	if (m_HitEffect) {
		m_HitScale.x += 0.1f;
		m_HitScale.y += 0.1f;
		m_HitScale.z += 0.1f;
		m_HitColor.w -= 0.1f;

		if (m_HitColor.w < 0.0f) {
			m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
			m_HitScale = { 0.0f,0.0f,0.0f };
			m_HitEffect = false;
			m_DeleteHitEffect = true;
		}
	}
}
