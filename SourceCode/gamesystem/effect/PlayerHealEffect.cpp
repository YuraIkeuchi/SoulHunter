#include "PlayerHealEffect.h"
#include "ImageManager.h"
#include "imgui.h"
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
	healeffecttex->SetColor({ 0.8f,1.0f,0.1f,0.5f });
	healeffecttex->SetPosition(m_HealPos);
	healeffecttex->SetRotation(m_HealRot);
	healeffecttex->SetScale(m_HealScale);
	healeffecttex->SetColor(m_HealColor);
}
//描画
void PlayerHealEffect::Draw() {
	IKETexture::PreDraw(0);
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
	//エフェクトの動き
	if (m_HealStart) {
		m_HealRot.z += 10.0f;
		if (m_HealEffectNumber == Appear) {
			m_HealScale.x += 0.2f;
			m_HealScale.y += 0.2f;
			m_HealScale.z += 0.2f;
			m_HealColor.w += 0.05f;
			if (m_HealColor.w > 1.0f) {
				m_HealEffectNumber = Disappear;
			}
		}
		else {
			m_HealColor.w -= 0.05f;
			if (m_HealColor.w < 0.0f) {
				m_HealScale = { 0.0f,0.0f,0.0f };
				m_HealColor.w = 0.0f;
				m_HealEffectNumber = Appear;
				m_HealStart = false;
				m_DeleteEffect = true;
			}
		}
	}
}
