#include "AttackEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
using namespace DirectX;
//読み込み
AttackEffect::AttackEffect() {
	IKETexture* AttackEffecttexture_;
	AttackEffecttexture_ = IKETexture::Create(ImageManager::AttackEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	AttackEffecttexture_->TextureCreate();
	AttackEffecttexture_->SetScale(m_Scale);
	AttackEffecttexture.reset(AttackEffecttexture_);
}
//初期化
void AttackEffect::Initialize() {
}
//更新
void AttackEffect::Update() {
	if (m_AttackAlive) {
		EffectMove();
		AttackEffecttexture->Update();
	}
	AttackEffecttexture->SetColor(m_Color);
	AttackEffecttexture->SetPosition(m_Pos);
	AttackEffecttexture->SetScale(m_Scale);
}
//描画
void AttackEffect::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	if (m_AttackAlive) {
		AttackEffecttexture->Draw();
	}
}
//エフェクトの動き
void AttackEffect::SetEffect(const XMFLOAT3& pos,int Dir) {
	//攻撃のエフェクトの発生した瞬間
	if (!m_AttackAlive) {
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;
		m_Color = m_BirthColor;
		m_Scale = m_BirthScale;
		m_AttackAlive = true;
	
		AttackEffecttexture->SetPosition(m_Pos);
		AttackEffecttexture->SetColor(m_Color);
		AttackEffecttexture->SetScale(m_Scale);
		if (Dir == 0) {
			m_AddPower = 0.3f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,180.0f });
		}
		else {
			m_AddPower = -0.3f;
			AttackEffecttexture->SetRotation({ 0.0f,0.0f,0.0f });
		}
	}
}
//エフェクトの動き
void AttackEffect::EffectMove() {
	float l_AddScale = 0.2f;//加算される大きさ
	float l_SubColor = 0.1f;//減算される色
	//発生してからの動き
	if (m_AttackAlive) {
		m_Pos.x += m_AddPower;
		m_Scale.x += l_AddScale;
		m_Scale.y += l_AddScale;
		m_Scale.z += l_AddScale;
		m_Color.w -= l_SubColor;
		if (m_Color.w < m_ColorMin) {
			m_Color.w = m_ColorMin;
			m_Scale = m_ResetThirdFew;
			m_AttackAlive = false;
		}
	}
}