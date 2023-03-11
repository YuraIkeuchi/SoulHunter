#include "WallAttackEffect.h"
#include"ModelManager.h"
#include "VariableCommon.h"
#include <random>
using namespace DirectX;
//�ǂݍ���
WallAttackEffect::WallAttackEffect() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
	helper = make_unique< Helper>();
}
//������
void WallAttackEffect::Initialize() {
	IKEObject3d* particleobj_[Effect_Max];
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj_[i] = new IKEObject3d();
		particleobj_[i] = IKEObject3d::Create();
		particleobj_[i]->SetModel(model);
		particleobj_[i]->SetLightEffect(false);
		particleobj_[i]->SetColor({ 1.5f,1.5f,1.5f,1.5f });
		particleobj[i].reset(particleobj_[i]);
		m_Effect[i] = false;
		m_Scale[i] = m_ResetThirdFew;
		m_AddScale[i] = 0.01f;
		m_Gravity[i] = 0.05f;
	}
}
//�X�V
void WallAttackEffect::Update() {
	EffectMove();
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj[i]->SetPosition(m_Pos[i]);
		particleobj[i]->SetScale(m_Scale[i]);
		if (m_Effect[i]) {
			particleobj[i]->Update();
		}
	}
}
//�`��
void WallAttackEffect::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_Effect[i]) {
			particleobj[i]->Draw();
		}
	}
}
//�G�t�F�N�g�̃Z�b�g
void WallAttackEffect::EffectSet(const XMFLOAT3& pos,int HitDir) {
	int l_Division = 10;
	//�G�t�F�N�g�̔���
	for (int i = 0; i < particleobj.size(); i++) {
		//
		if (!m_Effect[i] && !m_DeleteEffect) {
			//��������(���Z�͂Ƒ傫��)
			mt19937 mt{ std::random_device{}() };
			uniform_int_distribution<int> l_powerdistX(8, 12);
			uniform_int_distribution<int> l_powerdistY(-5, 10);
			uniform_int_distribution<int> l_scaledist(2, 4);
			m_Pos[i] = pos;
			m_BoundPower[i] = {
					float(l_powerdistX(mt)) / l_Division,
					float(l_powerdistY(mt)) / l_Division,
					0.0f,
			};
			if (HitDir == 0) {
				m_BoundPower[i].x *= -1;
			}
			m_Scale[i] = {
					float(l_scaledist(mt)) / l_Division,
					float(l_scaledist(mt)) / l_Division,
					float(l_scaledist(mt)) / l_Division,
			};
			m_Effect[i] = true;
		}

	}
}
//�G�t�F�N�g�̓���
void WallAttackEffect::EffectMove() {
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_Effect[i]) {
			m_BoundPower[i].y -= m_Gravity[i];
			//���W��傫���ɉ��Z����
			helper->Float3AddFloat3(m_Pos[i], m_BoundPower[i]);
			helper->Float3SubFloat(m_Scale[i], m_AddScale[i]);
			//�G�t�F�N�g������
			if (helper->CheckMax(m_Scale[i].x,m_ResetFew,m_ResetFew)) {
				m_Scale[i] = m_ResetThirdFew;
				m_Effect[i] = false;
				m_DeleteEffect = true;
			}
		}
	}
}