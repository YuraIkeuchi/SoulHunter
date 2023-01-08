#include "WallAttackEffect.h"
#include"Easing.h"
#include"ModelManager.h"
#include "imgui.h"
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
		particleobj[i].reset(particleobj_[i]);
		m_Effect[i] = false;
		m_Scale[i] = { 0.0f,0.0f,0.0f };
		m_AddScale[i] = 0.01f;
		m_Gravity[i] = 0.05f;
	}
}
//更新
void WallAttackEffect::Update(const XMFLOAT3& pos,int HitDir) {
	SetEffect(pos, HitDir);
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
	ImGui::Begin("Walll");
	ImGui::Text("Alive:%d", m_Effect[0]);
	ImGui::End();
	IKEObject3d::PreDraw();
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_Effect[i]) {
			particleobj[i]->Draw();
		}
	}
}
//エフェクトの動き
void WallAttackEffect::SetEffect(const XMFLOAT3& pos,int HitDir) {
	//エフェクトの発生
	for (int i = 0; i < particleobj.size(); i++) {
		//
		if (!m_Effect[i] && !m_DeleteEffect) {
			m_Pos[i] = pos;
			m_BoundPower[i] = {
					(float)(rand() % 4 + 2) / 10,
					(float)(rand() % 20 - 5) / 10,
					0.0f,
			};
			if (HitDir == 0) {
				m_BoundPower[i].x *= -1;
			}
			m_Scale[i] = { 0.3f,0.3f,0.3f };
			m_Effect[i] = true;
		}

		if (m_Effect[i]) {
			m_BoundPower[i].y -= m_Gravity[i];
			m_Pos[i] = { m_Pos[i].x + m_BoundPower[i].x,
						m_Pos[i].y + m_BoundPower[i].y,
						m_Pos[i].z + m_BoundPower[i].z };
			m_Scale[i] = { m_Scale[i].x - m_AddScale[i],m_Scale[i].y - m_AddScale[i], m_Scale[i].z - m_AddScale[i] };
			if (m_Scale[i].x <= 0.0f) {
				m_Scale[i] = { 0.0f,0.0f,0.0f };
				m_Effect[i] = false;
				m_DeleteEffect = true;
			}
		}
	}
}