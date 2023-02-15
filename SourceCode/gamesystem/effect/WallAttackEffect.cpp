#include "WallAttackEffect.h"
#include"ModelManager.h"
#include "VariableCommon.h"
using namespace DirectX;
//読み込み
WallAttackEffect::WallAttackEffect() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
}
//初期化
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
//更新
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
//描画
void WallAttackEffect::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_Effect[i]) {
			particleobj[i]->Draw();
		}
	}
}
//エフェクトのセット
void WallAttackEffect::EffectSet(const XMFLOAT3& pos,int HitDir) {
	int l_Division = 10;
	//エフェクトの発生
	for (int i = 0; i < particleobj.size(); i++) {
		//
		if (!m_Effect[i] && !m_DeleteEffect) {
			m_Pos[i] = pos;
			m_BoundPower[i] = {
					(float)(rand() % 8 + 4) / l_Division,
					(float)(rand() % 15 - 5) / l_Division,
					0.0f,
			};
			if (HitDir == 0) {
				m_BoundPower[i].x *= -1;
			}
			m_Scale[i] = {
					(float)(rand() % 2 + 2) / l_Division,
					(float)(rand() % 2 + 2) / l_Division,
					(float)(rand() % 2 + 2) / l_Division,
			};
			m_Effect[i] = true;
		}

	}
}
//エフェクトの動き
void WallAttackEffect::EffectMove() {
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_Effect[i]) {
			m_BoundPower[i].y -= m_Gravity[i];
			m_Pos[i] = { m_Pos[i].x + m_BoundPower[i].x,
						m_Pos[i].y + m_BoundPower[i].y,
						m_Pos[i].z + m_BoundPower[i].z };
			m_Scale[i] = { m_Scale[i].x - m_AddScale[i],m_Scale[i].y - m_AddScale[i], m_Scale[i].z - m_AddScale[i] };
			if (m_Scale[i].x <= m_ResetFew) {
				m_Scale[i] = m_ResetThirdFew;
				m_Effect[i] = false;
				m_DeleteEffect = true;
			}
		}
	}
}