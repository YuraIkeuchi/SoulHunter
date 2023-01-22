#include "PlayerDushEffect.h"
#include"ImageManager.h"
//読み込み
PlayerDushEffect::PlayerDushEffect() {

}
//初期化
void PlayerDushEffect::Initialize() {
	//エフェクトの初期化
	IKETexture* DushEffecttexture_ = IKETexture::Create(ImageManager::DushEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	DushEffecttexture_->TextureCreate();
	//DushEffecttexture->SetRotation({ 90,0,0 });
	DushEffecttexture_->SetScale(m_DushEffectscale);
	DushEffecttexture.reset(DushEffecttexture_);
}
//更新
void PlayerDushEffect::Update() {
	//エフェクトの発生

	//ダッシュ
	DushEffectMove();
	if (m_DushAlive) {
		DushEffecttexture->Update();
	}
	DushEffecttexture->SetPosition(m_DushEffectpos);
	DushEffecttexture->SetScale(m_DushEffectscale);
}
//描画
const void PlayerDushEffect::Draw() {
	IKETexture::PreDraw(1);
	if (m_DushAlive) {
		DushEffecttexture->Draw();
	}
}
//ダッシュのエフェクト
void PlayerDushEffect::DushEffectSet(const XMFLOAT3& pos) {
	if (!m_DushAlive  && !m_DeleteEffect) {
		m_DushEffectpos = pos;
		m_DushAlive = true;
	}
}

void PlayerDushEffect::DushEffectMove() {
	//ダッシュ
	if (m_DushAlive) {
		m_DushEffectscale.x += 0.05f;
		m_DushEffectscale.y += 0.05f;
		m_DushEffectscale.z += 0.05f;
		if (m_DushEffectscale.x >= 0.5f) {
			m_DushEffectscale = { 0.0f,0.0f,0.0f };
			m_DeleteEffect = true;
			m_DushAlive = false;
		}
	}
}
