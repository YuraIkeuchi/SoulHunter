#include "BossEffect.h"
#include"Easing.h"
#include"ImageManager.h"
using namespace DirectX;

//読み込み
BossEffect::BossEffect() {
	IKETexture* ParticleEffect_[Effect_Max];
	for (int i = 0; i < ParticleEffect.size(); i++) {
		ParticleEffect_[i] = IKETexture::Create(ImageManager::DamageEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		ParticleEffect_[i]->TextureCreate();
		//DushEffecttexture->SetRotation({ 90,0,0 });
		m_Scale[i] = { 0.0f,0.0f,0.0f };

		ParticleEffect_[i]->SetScale(m_Scale[i]);
		ParticleEffect[i].reset(ParticleEffect_[i]);
	}

	IKETexture* HitEffectTexture_;
	HitEffectTexture_ = IKETexture::Create(ImageManager::HitEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	HitEffectTexture_->TextureCreate();
	HitEffectTexture_->SetScale(m_HitScale);
	HitEffectTexture.reset(HitEffectTexture_);
}
//初期化
void BossEffect::Initialize() {
	for (int i = 0; i < ParticleEffect.size(); i++) {
		m_Effect[i] = false;
		m_BoundPower[i] = { 0.0f,0.0f,0.0f };
		m_Color[i] = { 0.0f,0.0f,0.0f,0.0f };
		m_Pos[i] = { 0.0f,0.0f,0.0f };
		m_Scale[i] = { 0.0f,0.0f,0.0f };
	}
}
//更新
void BossEffect::Update(const XMFLOAT3& pos, bool& Effect, int HitDir) {
	SetEffect(pos, Effect, HitDir);
	SetHitEffect(pos, Effect);
	for (int i = 0; i < ParticleEffect.size(); i++) {
		if (m_Effect[i]) {
			//object3d->Update();
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
	/*ImGui::Begin("Effect");
	ImGui::Text("ScaleX : %f", m_AddScale[0]);
	ImGui::End();*/
	IKETexture::PreDraw(1);
	for (int i = 0; i < ParticleEffect.size(); i++) {
		if (m_Effect[i] && (m_Scale[i].x >= 0.0f && m_Scale[i].x <= 0.5f)) {
			ParticleEffect[i]->Draw();
		}
	}

	IKETexture::PreDraw(0);
	if (m_HitEffect) {
		HitEffectTexture->Draw();
	}
}
//エフェクトの動き
void BossEffect::SetEffect(const XMFLOAT3& pos, bool& Effect, int HitDir) {
	//エフェクトの発生
	for (int i = 0; i < ParticleEffect.size(); i++) {
		//
		if (!m_Effect[i] && Effect && !m_DeleteEffect) {
			m_Pos[i] = pos;
			m_BoundPower[i] = {
					(float)(rand() % 100 - 50) / 400,
					(float)(rand() % 100 - 50) / 400,
					0.0f,
			};
			m_AddScale[i] = (float)(rand() % 20 + 20) / 800;
			m_Scale[i] = { 0.0f,0.0f,0.0f };
			m_Color[i] = { 1.0f,0.5f,0.0f,1.0f };
			m_ScaleChange[i] = false;
			m_Effect[i] = true;
		}

		if (m_Effect[i]) {
			m_Pos[i] = { m_Pos[i].x + m_BoundPower[i].x,
						m_Pos[i].y + m_BoundPower[i].y,
						m_Pos[i].z + m_BoundPower[i].z };
			if (!m_ScaleChange[i]) {
				m_Scale[i] = { m_Scale[i].x + m_AddScale[i],m_Scale[i].y + m_AddScale[i], m_Scale[i].z + m_AddScale[i] };

				if (m_Scale[i].x >= 0.5f) {
					m_ScaleChange[i] = true;
				}
			}
			else {
				m_Scale[i] = { m_Scale[i].x - m_AddScale[i],m_Scale[i].y - m_AddScale[i], m_Scale[i].z - m_AddScale[i] };
				if (m_Scale[i].x <= 0.0f) {
					m_Scale[i] = { 0.0f,0.0f,0.0f };
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
	//エフェクト出現
	if (m_HitEffect == false && Effect && !m_DeleteHitEffect) {
		m_HitScale = { 0.1f,0.1f,0.1f };
		m_HitPos = { pos.x, pos.y, pos.z - 5.0f, };
		m_HitColor = { 2.0f,2.0f,2.0f,2.0f };
		m_HitEffect = true;
	}

	//エフェクト動く
	if (m_HitEffect) {
		m_HitScale.x += 0.05f;
		m_HitScale.y += 0.05f;
		m_HitScale.z += 0.05f;
		m_HitColor.w -= 0.1f;

		if (m_HitColor.w < 0.0f) {
			m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
			m_HitScale = { 0.0f,0.0f,0.0f };
			m_HitEffect = false;
			m_DeleteHitEffect = true;
		}
	}
}