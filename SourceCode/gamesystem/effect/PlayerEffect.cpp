#include "PlayerEffect.h"
#include"Collision.h"
#include"Easing.h"
#include"ImageManager.h"
using namespace DirectX;
//読み込み
PlayerEffect::PlayerEffect() {

}
//初期化
void PlayerEffect::Initialize() {
	//エフェクトの初期化
	IKETexture* DushEffecttexture_ = IKETexture::Create(ImageManager::DushEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	DushEffecttexture_->TextureCreate();
	//DushEffecttexture->SetRotation({ 90,0,0 });
	DushEffecttexture_->SetScale(m_DushEffectscale);
	DushEffecttexture.reset(DushEffecttexture_);

	IKETexture* damagetex_[DamageEffect_Max];
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		damagetex_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		damagetex_[i]->TextureCreate();
		//DushEffecttexture->SetRotation({ 90,0,0 });
		//m_Scale = { 5.0f,5.0f,5.0f };
		//damagetex_[i]->SetScale(m_Scale);
		damagetex[i].reset(damagetex_[i]);
		m_DamageAlive[i] = false;
	}

	IKETexture* SpecialEffecttexture_ = IKETexture::Create(ImageManager::SpecialEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	SpecialEffecttexture_->TextureCreate();
	SpecialEffecttexture_->SetScale(m_SpecialEffectscale);
	SpecialEffecttexture.reset(SpecialEffecttexture_);


	IKETexture* HitEffectTexture_;
	HitEffectTexture_ = IKETexture::Create(ImageManager::HitEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	HitEffectTexture_->TextureCreate();
	HitEffectTexture_->SetScale(m_HitScale);
	HitEffectTexture.reset(HitEffectTexture_);
}
//更新
void PlayerEffect::Update() {
	//エフェクトの発生
	//ダッシュ
	if (m_DushAlive) {
		m_DushEffectscale.x += 0.05f;
		m_DushEffectscale.y += 0.05f;
		m_DushEffectscale.z += 0.05f;
		if (m_DushEffectscale.x >= 0.5f) {
			//player->SetDush(false);
			m_DushEffectscale = { 0.0f,0.0f,0.0f };
		}

		if (!player->GetDush()) {
			m_DushAlive = false;
		}
	}
	
	//ダッシュ
	DushEffectSet();
	if (m_DushAlive) {
		DushEffecttexture->Update();
	}
	DushEffecttexture->SetPosition(m_DushEffectpos);
	DushEffecttexture->SetScale(m_DushEffectscale);

	//ダメージ
	DamageEffectSet();
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Update();
		}
		damagetex[i]->SetPosition(m_DamageEffectpos[i]);
		damagetex[i]->SetScale(m_DamageEffectscale[i]);
	}

	//必殺技
	SpecialEffectSet();
	if (m_SpecialAlive) {
		m_SpecialEffectscale.x += 0.2f;
		m_SpecialEffectscale.y += 0.2f;
		m_SpecialEffectscale.z += 0.2f;
		m_SpecialRadius += 0.5f;
		if (m_SpecialEffectscale.x >= 10.0f) {
			m_SpecialAlive = false;
			player->SetSpecialEffect(false);
			m_SpecialEffectscale = { 0.0f,0.0f,0.0f };
			m_SpecialRadius = 0.0f;
		}
	}
	//ヒットエフェクト
	SetHitEffect();
	if (m_HitEffect) {
		HitEffectTexture->Update();
	}
	HitEffectTexture->SetPosition(m_HitPos);
	HitEffectTexture->SetScale(m_HitScale);
	HitEffectTexture->SetColor(m_HitColor);
	if (m_SpecialAlive) {
		SpecialEffecttexture->Update();
	}
	SpecialEffecttexture->SetPosition(m_SpecialEffectpos);
	SpecialEffecttexture->SetScale(m_SpecialEffectscale);
}
//描画
const void PlayerEffect::Draw() {
	IKETexture::PreDraw(1);
	if (m_DushAlive) {
		DushEffecttexture->Draw();
	}

	if (m_SpecialAlive) {
		SpecialEffecttexture->Draw();
	}

	for (std::size_t i = 0; i < damagetex.size(); i++) {
		if (m_DamageAlive[i]) {
			damagetex[i]->Draw();
		}
	}

	IKETexture::PreDraw(0);
	if (m_HitEffect) {
		HitEffectTexture->Draw();
	}
}
//ダッシュのエフェクト
void PlayerEffect::DushEffectSet() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	bool Dush = player->GetDush();

	if (!m_DushAlive && Dush) {
		this->m_DushEffectpos.x = m_PlayerPos.x;
		this->m_DushEffectpos.y = m_PlayerPos.y;
		this->m_DushEffectpos.z = m_PlayerPos.z;
		m_DushAlive = true;
		DushEffecttexture->SetPosition(m_DushEffectpos);
	}
}
//必殺技のエフェクト
void PlayerEffect::SpecialEffectSet() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	bool l_Special = player->GetSpecialEffect();

	if (!m_SpecialAlive && l_Special) {
		this->m_SpecialEffectpos.x = m_PlayerPos.x;
		this->m_SpecialEffectpos.y = m_PlayerPos.y;
		this->m_SpecialEffectpos.z = m_PlayerPos.z - 10.0f;
		m_SpecialAlive = true;
		SpecialEffecttexture->SetPosition(m_SpecialEffectpos);
	}
}
//ダメージ食らった時のエフェクト
void PlayerEffect::DamageEffectSet() {
	//エフェクトの発生
	bool playerEffect = player->GetEffect();
	for (std::size_t i = 0; i < damagetex.size(); i++) {
		//エフェクトの発生
		if (playerEffect == true && m_DamageAlive[i] == false) {
			m_DamageEffectscale[i] = {0.3f,0.3f,0.3f};
			damagetex[i]->SetColor({1.0f,0.9f,0.8f,1.0f});
			m_BoundPower[i].x = (float)(rand() % 10 + 5) / 10;
			m_BoundPower[i].y = (float)(rand() % 20 - 10) / 10;
			m_BoundPower[i].z = 0.0f;
			if (i % 2 == 0) {
				m_BoundPower[i].x *= -1.0f;
			}
			m_DamageEffectpos[i] = player->GetPosition();
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
				m_DeleteHitEffect = false;
				player->SetEffect(false);
			}
		}
	}
}
//ヒットエフェクト
void PlayerEffect::SetHitEffect() {
	//エフェクトの発生
	bool playerEffect = player->GetEffect();
	//エフェクト出現
	if (m_HitEffect == false && playerEffect && !m_DeleteHitEffect) {
		m_HitScale = { 0.1f,0.1f,0.1f };
		m_HitPos = player->GetPosition();
		m_HitColor = { 2.0f,2.0f,2.0f,2.0f };
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
