#include "PlayerHealEffect.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
//読み込み
PlayerHealEffect::PlayerHealEffect() {

}
//初期科
void PlayerHealEffect::Initialize() {
	IKETexture* healeffecttex_;
	healeffecttex_ = IKETexture::Create(ImageManager::HealEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	healeffecttex_->TextureCreate();
	healeffecttex.reset(healeffecttex_);
	m_HealEffectNumber = Appear;
}
//更新
void PlayerHealEffect::Update() {
	EffectMove();
	if (m_HealStart) {
		healeffecttex->Update();
	}
	healeffecttex->SetPosition(m_HealPos);
	healeffecttex->SetRotation(m_HealRot);
	healeffecttex->SetScale(m_HealScale);
	healeffecttex->SetColor(m_HealColor);
}
//描画
void PlayerHealEffect::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	if (m_HealStart) {
		healeffecttex->Draw();
	}
}

//開腹した瞬間のエフェクト
void PlayerHealEffect::SetEffect(const XMFLOAT3& StartPos) {
	if (!m_HealStart && !m_DeleteEffect) {
		m_HealPos = StartPos;
		m_HealStart = true;
	}
	
}

void PlayerHealEffect::EffectMove() {
	float l_AddScale = 0.2f;
	float l_AddRotZ = 10.0f;
	float l_AddColor = 0.05f;
	//エフェクトの動き
	if (m_HealStart) {
		m_HealRot.z += l_AddRotZ;
		if (m_HealEffectNumber == Appear) {
			m_HealScale.x += l_AddScale;
			m_HealScale.y += l_AddScale;
			m_HealScale.z += l_AddScale;
			m_HealColor.w += l_AddColor;
			if (m_HealColor.w > m_ColorMax) {
				m_HealEffectNumber = Disappear;
			}
		}
		else {
			m_HealColor.w -= l_AddColor;
			m_HealColor.w = max(m_HealColor.w, m_ColorMin);
			if (m_HealColor.w < m_ColorMin) {
				m_HealScale = m_ResetThirdFew;
				m_HealEffectNumber = Appear;
				m_HealStart = false;
				m_DeleteEffect = true;
			}
		}
	}
}
