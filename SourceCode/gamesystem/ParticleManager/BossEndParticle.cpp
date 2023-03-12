#include "BossEndParticle.h"
#include "ModelManager.h"
#include <random>
#include "VariableCommon.h"
//読み込み
BossEndParticle::BossEndParticle() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
}
//初期科
void BossEndParticle::Initialize() {
	IKEObject3d* particleobj_[BossEndParticle_Max];
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj_[i] = new IKEObject3d();
		particleobj_[i] = IKEObject3d::Create();
		m_Gravity[i] = 0.05f;
		particleobj_[i]->SetModel(model);
		particleobj[i].reset(particleobj_[i]);
		m_RockAlive[i] = false;
		m_Rockscale[i] = { 0.0f,0.0f,0.0f };
	}

	helper = make_unique< Helper>();
}
//岩の方の更新
void BossEndParticle::ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	DownRockParticle(StartPos, Timer, TargetTimer);
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj[i]->SetPosition(m_RockPos[i]);
		particleobj[i]->SetScale(m_Rockscale[i]);
		if (m_RockAlive[i]) {
			particleobj[i]->Update();
		}
	}
}
//描画
void BossEndParticle::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_RockAlive[i]) {
			particleobj[i]->Draw();
		}
	}
}

void BossEndParticle::ImGuiDraw() {
}
void BossEndParticle::DownRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.005f;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_RockAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_dist(-3, 3);
				m_Rockscale[i] = { 0.5f,0.5f,0.5f };
				m_RockRandPos[i].x = float(l_dist(mt));
				m_RockPos[i].x = StartPos.x + m_RockRandPos[i].x;
				m_RockPos[i].y = StartPos.y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = 0.0f;
				m_RockAddPower[i].x = float(l_dist(mt)) / 10;
				m_RockAlive[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < particleobj.size(); i++) {
		if (m_RockAlive[i]) {
			m_RockPos[i].z = StartPos.z;
			m_RockAddPower[i].y -= m_Gravity[i];
			m_RockPos[i].y += m_RockAddPower[i].y;
			m_RockPos[i].x += m_RockAddPower[i].x;
			helper->Float3SubFloat(m_Rockscale[i], l_AddScale);
			if (helper->CheckMax(m_Rockscale[i].x,m_ResetFew,m_ResetFew)) {
				m_RockAlive[i] = false;
			}
		}
	}
}