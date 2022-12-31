#include "BossEndParticle.h"
#include "ImageManager.h"
#include "ModelManager.h"
//ì«Ç›çûÇ›
BossEndParticle::BossEndParticle() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
}
//èâä˙â»
void BossEndParticle::Initialize() {
	IKEObject3d* particleobj_[BossEndParticle_Max];
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj_[i] = new IKEObject3d();
		particleobj_[i] = IKEObject3d::Create();
		m_Gravity[i] = 0.05f;
		//object_[i]->CreateGraphicsPipeline(L"Resources/shaders/BasicVS.hlsl", L"Resources/shaders/BasicPS.hlsl");
		particleobj_[i]->SetModel(model);
		particleobj[i].reset(particleobj_[i]);
		m_RockAlive[i] = false;
		m_Rockscale[i] = { 0.0f,0.0f,0.0f };
	}
}
//ä‚ÇÃï˚ÇÃçXêV
void BossEndParticle::ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ThornDir) {
	DownRockParticle(StartPos, Timer, TargetTimer);
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj[i]->SetPosition(m_RockPos[i]);
		particleobj[i]->SetScale(m_Rockscale[i]);
		if (m_RockAlive[i]) {
			particleobj[i]->Update();
		}
	}
}
//ï`âÊ
void BossEndParticle::Draw() {
	/*ImGui::Begin("Particle");
	ImGui::SliderFloat("pos[0].y", &m_RockPos[0].y, 300, -300);
	ImGui::SliderFloat("pos.x", &m_RockPos[0].x, 300, -300);
	ImGui::SliderFloat("power[0].y", &m_RockAddPower[0].y, 300, -300);
	ImGui::Text("RockAlive[0] %d", m_RockAlive[0]);
	ImGui::End();*/
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
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//îÚÇŒÇ∑ï˚å¸ÇÉâÉìÉ_ÉÄÇ≈åàÇﬂÇÈ
			if (!m_RockAlive[i]) {
				m_Rockscale[i] = { 0.3f,0.3f,0.3f };
				m_RockRandPos[i].x = (float)(rand() % 6 - 3);
				m_RockPos[i].x = StartPos.x + m_RockRandPos[i].x;
				m_RockPos[i].y = StartPos.y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = 0.0f;
				m_RockAddPower[i].x = (float)(rand() % 6 - 3) / 10;
				m_RockAlive[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < particleobj.size(); i++) {
		if (m_RockAlive[i]) {
			m_RockAddPower[i].y -= m_Gravity[i];
			m_RockPos[i].y += m_RockAddPower[i].y;
			m_RockPos[i].x += m_RockAddPower[i].x;
			m_Rockscale[i].x -= 0.005f;
			m_Rockscale[i].y -= 0.005f;
			m_Rockscale[i].z -= 0.005f;
			if (m_Rockscale[i].x <= 0.0f) {
				m_RockAlive[i] = false;
			}
		}
	}
}