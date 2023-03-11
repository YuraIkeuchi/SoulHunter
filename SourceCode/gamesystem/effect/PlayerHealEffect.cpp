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
	helper = make_unique< Helper>();
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
			helper->Float3AddFloat(m_HealScale, l_AddScale);
			if (helper->CheckMin(m_HealColor.w,m_ColorMax,l_AddColor)) {
				m_HealEffectNumber = Disappear;
			}
		}
		else {
			if (helper->CheckMax(m_HealColor.w, m_ColorMin, -l_AddColor)) {
				m_HealScale = m_ResetThirdFew;
				m_HealEffectNumber = Appear;
				m_HealStart = false;
				m_DeleteEffect = true;
			}
		}
	}
}
