#include "ParticleSoul.h"
#include "ImageManager.h"
#include "imgui.h"
//読み込み
ParticleSoul::ParticleSoul() {
	IKETexture* particlesoul_[ParticleSoul_Max];
	for (int i = 0; i < particlesoul.size(); i++) {
		particlesoul_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		particlesoul_[i]->TextureCreate();
		particlesoul_[i]->SetPosition({ 0.0f,90.0f,0.0f });
		//DushEffecttexture->SetRotation({ 90,0,0 });
		m_scale[i] = { 0.0f,0.0f,0.0f };
		m_Alive[i] = false;
		particlesoul_[i]->SetScale(m_scale[i]);
		particlesoul[i].reset(particlesoul_[i]);
	}
}
//初期化
void ParticleSoul::Initialize() {
	for (int i = 0; i < particlesoul.size(); i++) {
		m_Alive[i] = false;
		m_scale[i] = { 0.0f,0.0f,0.0f };
	}
}
//更新
void ParticleSoul::Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ParticleType) {

	if (ParticleType == Normal) {
		NormalParticle(StartPos, Timer, TargetTimer);
	}
	
	for (int i = 0; i < ParticleSoul_Max; i++) {
		particlesoul[i]->SetPosition(m_pos[i]);
		particlesoul[i]->SetScale(m_scale[i]);
		particlesoul[i]->SetColor(m_StartColor);
		if (m_Alive[i]) {
			particlesoul[i]->Update();
		}
	}
}
//描画
void ParticleSoul::Draw() {
	IKETexture::PreDraw(1);
	for (int i = 0; i < particlesoul.size(); i++) {
		if (m_Alive[i]) {
			particlesoul[i]->Draw();
		}
	}
}
//ImGuiの描画
void ParticleSoul::ImGuiDraw() {
	//ImGui::Begin("color");
	//ImGui::SetWindowPos(ImVec2(0, 500));
	//ImGui::SetWindowSize(ImVec2(280, 240));
	//ImGui::SliderFloat("m_power[0].y", &m_power[0], 100, -100);
	//ImGui::SliderFloat("m_scale[0].y", &m_scale[0].x, 100, -100);
	//ImGui::SliderFloat("color.r", &m_color.x, 1, 0);
	//ImGui::SliderFloat("color.g", &m_color.y, 1, 0);
	//ImGui::SliderFloat("color.b", &m_color.z, 1, 0);
	//ImGui::SliderFloat("color.a", &m_color.w, 1, 0);
	//ImGui::Text("m_EndCount:%d", m_EndCount);
	////ImGui::SliderInt("ParticleCount", &m_ParticleCount, 100, 1, "%d");
	//ImGui::End();
}

//パーティクル
void ParticleSoul::NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particlesoul.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				/*m_AddPower[i].x = (float)(rand() % 3 - 1);
				m_AddPower[i].y = (float)(rand() % 2 - 1);*/
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.03f,0.03f };
				m_Number[i] = rand() % 2;
				/*	m_AddPower[i].x = m_AddPower[i].x / 10;
					m_AddPower[i].y = m_AddPower[i].y / 20;*/
				m_pos[i].x = m_StartPos.x;
				m_pos[i].y = m_StartPos.y;
				m_pos[i].z = m_StartPos.z;
				m_AddPower[i].y = 0.0f;
				m_scale[i] = { m_StartScale,m_StartScale,m_StartScale };
				m_Alive[i] = true;
				m_ScaleChange[i] = false;
				if (m_ParticleBreak) {
					break;
				}
			}
		}
	}
	//実際に動く
	for (int i = 0; i < particlesoul.size(); i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.005f;
			m_AddPower[i].y += 0.001f;
			if (m_AddPower[i].y <= 0.01f) {
				m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			}
			m_pos[i].y += float((sin(m_Angle[i])) * m_speed[i].y) + m_AddPower[i].y;
			m_color[i].w -= 0.001f;
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += m_AddScale;
				m_scale[i].y += m_AddScale;
				m_scale[i].z += m_AddScale;

				if (m_scale[i].x >= m_StartScale + 0.2f) {
					m_ScaleChange[i] = true;
				}
			}
			else {
				m_scale[i].x -= m_AddScale;
				m_scale[i].y -= m_AddScale;
				m_scale[i].z -= m_AddScale;

				if (m_scale[i].x <= 0.0f) {
					m_Alive[i] = false;
				}
			}
		}
	}
}
