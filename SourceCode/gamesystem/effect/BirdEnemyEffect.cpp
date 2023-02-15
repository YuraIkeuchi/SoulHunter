#include "BirdEnemyEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
using namespace DirectX;
//読み込み
BirdEnemyEffect::BirdEnemyEffect() {
	IKETexture* JumpDamageEffect_[JumpEffect_Max];
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		JumpDamageEffect_[i] = IKETexture::Create(ImageManager::WingEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		JumpDamageEffect_[i]->TextureCreate();
		JumpDamageEffect_[i]->SetScale(m_JumpDamageScale[i]);
		JumpDamageEffect[i].reset(JumpDamageEffect_[i]);
	}
}
//初期化
void BirdEnemyEffect::Initialize() {
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		m_Effect[i] = false;
		m_Birth[i] = false;
		m_Timer[i] = m_ResetNumber;
		m_EffectNumber[i] = No;
		m_pos[i] = m_ResetThirdFew;
		m_rot[i] = m_ResetThirdFew;
		m_AddPower[i] = m_ResetThirdFew;
		m_JumpDamageScale[i] = m_ResetThirdFew;
	}
}
//解放
void BirdEnemyEffect::Finalize() {

}
//更新
void BirdEnemyEffect::Update(const XMFLOAT3& pos) {
	SetEffect(pos);
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		if (m_Effect[i]) {
			//object3d->Update();
			JumpDamageEffect[i]->Update();
		}
		JumpDamageEffect[i]->SetColor({ 1.0f,1.0f,1.0f,0.5f });
		JumpDamageEffect[i]->SetPosition(m_pos[i]);
		JumpDamageEffect[i]->SetRotation(m_rot[i]);
		JumpDamageEffect[i]->SetScale(m_JumpDamageScale[i]);
	}
}
//描画
void BirdEnemyEffect::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		if (m_Effect[i]) {
			JumpDamageEffect[i]->Draw();
		}
	}
}
//エフェクトの動き
void BirdEnemyEffect::SetEffect(const XMFLOAT3& pos) {
	float l_SubScale = 0.005f;
	int l_Division = 10;
	//エフェクトの発生
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		//ここで飛ばす方向を決める
		if (m_EffectNumber[i] == No && !m_Birth[i]) {
			m_AddPower[i].x = (float)(rand() % 20 - 10) / l_Division;
			m_AddPower[i].y = (float)(rand() % 5 + 1) / l_Division;
			m_AddPower[i].z = 0.0f;
			m_AddRot[i] = (float)(rand() % 20 - 10);
			m_JumpDamageScale[i] = { 0.2f,0.2f,0.2f };
			m_Gravity[i] = (float)(rand() % 3 + 1) / l_Division;
			m_EffectNumber[i] = Birth;
			m_Birth[i] = true;
		}
		//エフェクトが動く
		if (m_EffectNumber[i] == Birth) {
			m_Timer[i]++;

			if (m_Timer[i] >= i * 2) {
				m_pos[i] = { pos.x + m_AddPower[i].x,pos.y + m_AddPower[i].y,pos.z };
				m_Effect[i] = true;
				m_EffectNumber[i] = Fall;
			}
		}
		else if(m_EffectNumber[i] == Fall){
			//エフェクトが落ちていく
			m_rot[i].z += m_AddRot[i];
			m_pos[i].y -= m_Gravity[i];
			m_JumpDamageScale[i].x -= l_SubScale;
			m_JumpDamageScale[i].y -= l_SubScale;
			m_JumpDamageScale[i].z -= l_SubScale;
			if (m_JumpDamageScale[i].x <= m_ResetFew) {
				m_JumpDamageScale[i] = m_ResetThirdFew;
				m_Effect[i] = false;
				m_EffectNumber[i] = No;
			}
		}
	}
}
