#include "BirdEnemyEffect.h"
#include"Easing.h"
#include"ImageManager.h"
using namespace DirectX;
//読み込み
BirdEnemyEffect::BirdEnemyEffect() {
	IKETexture* JumpDamageEffect_[JumpEffect_Max];
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		JumpDamageEffect_[i] = IKETexture::Create(ImageManager::WingEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		JumpDamageEffect_[i]->TextureCreate();
		//DushEffecttexture->SetRotation({ 90,0,0 });
		JumpDamageEffect_[i]->SetScale(m_JumpDamageScale[i]);
		JumpDamageEffect[i].reset(JumpDamageEffect_[i]);
	}
}
//初期化
void BirdEnemyEffect::Initialize() {
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		m_Effect[i] = false;
		m_Birth[i] = false;
		m_Timer[i] = 0;
		m_EffectNumber[i] = No;
		m_pos[i] = {0.0f,0.0f,0.0f};
		m_rot[i] = { 0.0f,0.0f,0.0f };
		m_AddPower[i] = { 0.0f,0.0f,0.0f };
		m_JumpDamageScale[i] = { 0.0f,0.0f,0.0f };
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
	//bool BirdEnemyEffect = Jump->GetEffect();
	/*ImGui::Begin("BirdEnemyEffect");
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		ImGui::Text("m_Effect::%d", m_Birth[i]);
	}
	ImGui::End();*/
	IKETexture::PreDraw(0);
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		if (m_Effect[i]) {
			JumpDamageEffect[i]->Draw();
		}
	}
}
//エフェクトの動き
void BirdEnemyEffect::SetEffect(const XMFLOAT3& pos) {
	//エフェクトの発生
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		//ここで飛ばす方向を決める
		if (m_EffectNumber[i] == No && !m_Birth[i]) {
			m_AddPower[i].x = (float)(rand() % 20 - 10) / 10;
			m_AddPower[i].y = (float)(rand() % 5 + 1) / 10;
			m_AddPower[i].z = 0.0f;
			m_AddRot[i] = (float)(rand() % 20 - 10);
			m_JumpDamageScale[i] = { 0.2f,0.2f,0.2f };
			m_Gravity[i] = (float)(rand() % 3 + 1) / 10;
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
			m_JumpDamageScale[i].x -= 0.005f;
			m_JumpDamageScale[i].y -= 0.005f;
			m_JumpDamageScale[i].z -= 0.005f;
			if (m_JumpDamageScale[i].x <= 0.0f) {
				m_JumpDamageScale[i] = { 0.0f,0.0f,0.0f };
				m_Effect[i] = false;
				m_EffectNumber[i] = No;
			}
		}
	}
}
