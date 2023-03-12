#include "SwordParticle.h"
#include "ModelManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include <random>
SwordParticle::SwordParticle() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::Particle);
}
//初期化
void SwordParticle::Initialize() {
	IKEObject3d* object_[Particle_Max];
	for (int i = 0; i < object.size(); i++) {
		object_[i] = new IKEObject3d();
		object_[i] = IKEObject3d::Create();
		object_[i]->SetModel(model);
		object_[i]->SetColor(m_StartColor);
		object_[i]->SetPosition(m_pos[i]);
		object_[i]->SetLightEffect(false);
		object[i].reset(object_[i]);
		m_pos[i] = { 0.0f,3.0f,3.0f };
	}

	helper = make_unique< Helper>();
}
//更新
void SwordParticle::Update(XMFLOAT3 StartPos, int Timer, int TargetTimer, XMMATRIX matrix) {
	NormalParticle(Timer, TargetTimer, matrix);
	for (int i = 0; i < object.size(); i++) {
		object[i]->SetPosition(m_pos[i]);
		object[i]->SetScale(m_scale[i]);
		object[i]->SetColor(m_StartColor);
		if (m_Alive[i]) {
			object[i]->AffineUpdate();
		}
	}
}
//描画
void SwordParticle::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < object.size(); i++) {
		if (m_Alive[i]) {
			object[i]->Draw();
		}
	}
}
//ImGui
void SwordParticle::ImGuiDraw() {
}
//普通のパーティクル
void SwordParticle::NormalParticle(int Timer, int TargetTimer, XMMATRIX matrix) {
	float l_AddScale = 0.01f;
	float l_TargetScale = 0.2f;
	for (int i = 0; i < object.size(); i++) {
		if (m_Alive[i]) {
			m_pos[i].x += (cos(m_angle[i]) * m_speed[i].x);
			m_pos[i].y += (sin(m_angle[i]) * m_speed[i].y);
			if (!m_ScaleChange[i]) {
				helper->Float3AddFloat(m_scale[i], l_AddScale);
				if (helper->CheckMin(m_scale[i].x, l_TargetScale, m_ResetFew)) {
					m_ScaleChange[i] = true;
				}
			}
			else {
				helper->Float3SubFloat(m_scale[i], l_AddScale);
				if (helper->CheckMax(m_scale[i].x,m_ResetFew,m_ResetFew)) {
					m_Alive[i] = false;
				}
			}
		}
	}
}
//マトリックスセット
void SwordParticle::SetMatrix(XMMATRIX matrix)
{
	for (int i = 0; i < object.size(); i++) {
		if (!m_Alive[i]) {
			object[i]->AddMatrix(matrix);
		}
	}
}
//パーティクルセット
void SwordParticle::SetParticle(int Timer, int TargetTimer, XMMATRIX matrix) {
	if (Timer >= TargetTimer) {
		for (int i = 0; i < object.size(); i++) {
			if (!m_Alive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_angledist(0, 360);
				uniform_int_distribution<int> l_partdistX(20, 40);
				uniform_int_distribution<int> l_partdistY(30, 40);
				object[i]->AddMatrix(matrix);
				//パーティクルを出す
				m_RandPos[i] = { 0,
			 (float)(l_partdistX(mt)) * -1.2f,
				 (float)(l_partdistY(mt))
				};
				m_RandPos[i] = { m_RandPos[i].x,
					m_RandPos[i].y / 10,
					 m_RandPos[i].z / 10
				};
				m_pos[i] = m_RandPos[i];
				m_angle[i] = float(l_angledist(mt));
				m_speed[i] = { 0.02f,0.02f };
				m_addPower[i].y = 0.0f;
				m_scale[i] = { 0.1f,0.1f,0.1f };
				m_Alive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
}