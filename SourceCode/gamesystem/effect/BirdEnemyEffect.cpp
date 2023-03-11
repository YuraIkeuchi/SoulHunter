#include "BirdEnemyEffect.h"
#include"ImageManager.h"
#include "VariableCommon.h"
#include <random>
using namespace DirectX;
//�ǂݍ���
BirdEnemyEffect::BirdEnemyEffect() {
	IKETexture* JumpDamageEffect_[JumpEffect_Max];
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		JumpDamageEffect_[i] = IKETexture::Create(ImageManager::WingEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		JumpDamageEffect_[i]->TextureCreate();
		JumpDamageEffect_[i]->SetScale(m_Scale[i]);
		JumpDamageEffect[i].reset(JumpDamageEffect_[i]);
	}

	helper = make_unique< Helper>();
}
//������
void BirdEnemyEffect::Initialize() {
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		m_Effect[i] = false;
		m_Birth[i] = false;
		m_Timer[i] = m_ResetNumber;
		m_EffectNumber[i] = No;
		m_Position[i] = m_ResetThirdFew;
		m_Rotation[i] = m_ResetThirdFew;
		m_AddPower[i] = m_ResetThirdFew;
		m_Scale[i] = m_ResetThirdFew;
	}
}
//���
void BirdEnemyEffect::Finalize() {

}
//�X�V
void BirdEnemyEffect::Update(const XMFLOAT3& pos) {
	SetEffect(pos);
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		if (m_Effect[i]) {
			//object3d->Update();
			JumpDamageEffect[i]->Update();
		}
		JumpDamageEffect[i]->SetColor({ 1.0f,1.0f,1.0f,0.5f });
		JumpDamageEffect[i]->SetPosition(m_Position[i]);
		JumpDamageEffect[i]->SetRotation(m_Rotation[i]);
		JumpDamageEffect[i]->SetScale(m_Scale[i]);
	}
}
//�`��
void BirdEnemyEffect::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		if (m_Effect[i]) {
			JumpDamageEffect[i]->Draw();
		}
	}
}
//�G�t�F�N�g�̓���
void BirdEnemyEffect::SetEffect(const XMFLOAT3& pos) {
	float l_SubScale = 0.005f;
	int l_Division = 10;
	//�G�t�F�N�g�̔���
	for (int i = 0; i < JumpDamageEffect.size(); i++) {
		//�����Ŕ�΂����������߂�
		if (m_EffectNumber[i] == No && !m_Birth[i]) {
			//�����w��(���W���]�ɉ��Z���镨)
			mt19937 mt{ std::random_device{}() };
			uniform_int_distribution<int> l_dist(-10, 10);
			uniform_int_distribution<int> l_dist2(5, 6);
			uniform_int_distribution<int> l_dist3(3, 4);
			m_AddPower[i].x = (float)(l_dist(mt)) / l_Division;
			m_AddPower[i].y = (float)(l_dist2(mt)) / l_Division;
			m_AddPower[i].z = 0.0f;
			m_AddRot[i] = (float)(l_dist(mt));
			m_Scale[i] = { 0.2f,0.2f,0.2f };
			m_Gravity[i] = (float)(l_dist3(mt)) / l_Division;
			m_EffectNumber[i] = Birth;
			m_Birth[i] = true;
		}
		//�G�t�F�N�g������
		if (m_EffectNumber[i] == Birth) {
			m_Timer[i]++;

			if (m_Timer[i] >= i * 2) {
				m_Position[i] = { pos.x + m_AddPower[i].x,pos.y + m_AddPower[i].y,pos.z };
				m_Effect[i] = true;
				m_EffectNumber[i] = Fall;
			}
		}
		else if(m_EffectNumber[i] == Fall){
			//�G�t�F�N�g�������Ă���
			m_Rotation[i].z += m_AddRot[i];
			m_Position[i].y -= m_Gravity[i];
			//�傫�������炷
			helper->Float3SubFloat(m_Scale[i], l_SubScale);
			if (helper->CheckMax(m_Scale[i].x,m_ResetFew,m_ResetFew)) {
				m_Effect[i] = false;
				m_EffectNumber[i] = No;
			}
		}
	}
}
