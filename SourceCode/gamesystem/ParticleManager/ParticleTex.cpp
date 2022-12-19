#include "ParticleTex.h"
#include "ImageManager.h"
#include "imgui.h"
//読み込み
ParticleTex::ParticleTex() {

}
//初期科
void ParticleTex::Initialize() {
	IKETexture* particletex_[ParticleTex_Max];
	for (int i = 0; i < particletex.size(); i++) {
		particletex_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		particletex_[i]->TextureCreate();
		particletex_[i]->SetPosition({ 0.0f,90.0f,0.0f });
		//DushEffecttexture->SetRotation({ 90,0,0 });
		m_scale[i] = { 0.0f,0.0f,0.0f };
		m_Alive[i] = false;
		particletex_[i]->SetScale(m_scale[i]);
		particletex[i].reset(particletex_[i]);
	}
}
//更新
void ParticleTex::Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ParticleType) {
	//パーティクルの種類によって違う
	if (ParticleType == Normal) {
		NormalParticle(StartPos, Timer, TargetTimer);
	}
	else if (ParticleType == Up) {
		UpParticle(StartPos, Timer, TargetTimer);
	}
	else if (ParticleType == End) {
		EndParticle(StartPos, Timer, TargetTimer);
	}
	else if (ParticleType == Chest) {
		ChestParticle(StartPos, Timer, TargetTimer);
	}
	else if (ParticleType == Save) {
		SaveParticle(StartPos, Timer, TargetTimer);
	}

	for (int i = 0; i < particletex.size(); i++) {
		particletex[i]->SetPosition(m_pos[i]);
		particletex[i]->SetScale(m_scale[i]);
		particletex[i]->SetColor(m_color[i]);
		if (m_Alive[i]) {
			particletex[i]->Update();
		}
		if (m_ParticleBillboard) {
			particletex[i]->SetIsBillboard(true);
		}
	}
	//else if (ParticleType == Wide) {

	//	WideParticle(StartPos, Timer, TargetTimer);
	//	for (int i = 0; i < m_WideParticleCount; i++) {
	//		object[i]->SetPosition(m_pos[i]);
	//		object[i]->SetScale(m_scale[i]);
	//		object[i]->SetColor(m_color);
	//		if (m_Alive[i]) {
	//			object[i]->Update();
	//		}
	//	}
	//}

}
//描画
void ParticleTex::Draw() {
	IKETexture::PreDraw(1);
	for (int i = m_DrawCount; i < particletex.size(); i++) {
		if (m_Alive[i]) {
			particletex[i]->Draw();
		}
	}
}
//IMGuiの描画
void ParticleTex::ImGuiDraw() {
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
//普通のパーティクル
void ParticleTex::NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	m_DrawCount = 0;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < m_NormalParticleCount; i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				/*m_AddPower[i].x = (float)(rand() % 3 - 1);
				m_AddPower[i].y = (float)(rand() % 2 - 1);*/
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.02f,0.02f };
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
	for (int i = 0; i < m_NormalParticleCount; i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.005f;
			m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			m_pos[i].y += float((sin(m_Angle[i])) * m_speed[i].y);
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += m_AddScale;
				m_scale[i].y += m_AddScale;
				m_scale[i].z += m_AddScale;

				if (m_scale[i].x >= m_StartScale + 0.1f) {
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
//上方向に上がるパーティクル(主にタイトル)
void ParticleTex::UpParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	m_DrawCount = 1;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < m_NormalParticleCount; i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				/*m_AddPower[i].x = (float)(rand() % 3 - 1);
				m_AddPower[i].y = (float)(rand() % 2 - 1);*/

				m_speed[i] = { 0.1f,0.02f };
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
	for (int i = 0; i < m_NormalParticleCount; i++) {
		if (m_Alive[i]) {
			m_Timer[i]++;
			if (m_Timer[i] % 30 == 0) {
				m_Angle[i] = (float)(rand() % 360);
			}

			m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			m_AddPower[i].y = (float)(rand() % 1 + 1);
			m_AddPower[i].y = m_AddPower[i].y / 10;
			m_pos[i].y += m_AddPower[i].y;
			m_AddScale = 0.002f;
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += m_AddScale;
				m_scale[i].y += m_AddScale;
				m_scale[i].z += m_AddScale;

				if (m_scale[i].x >= m_StartScale + 0.5) {
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
//敵をたおした時のパーティクル
void ParticleTex::EndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	m_DrawCount = 0;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < m_NormalParticleCount; i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				/*m_AddPower[i].x = (float)(rand() % 3 - 1);
				m_AddPower[i].y = (float)(rand() % 2 - 1);*/
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.3f,0.3f };
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
	for (int i = 0; i < m_NormalParticleCount; i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.01f;
			m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			m_pos[i].y += float((sin(m_Angle[i])) * m_speed[i].y);

			if (m_speed[i].x > 0.0f) {
				m_speed[i].x -= 0.01f;
				m_speed[i].y -= 0.01f;
			}
			else {
				m_speed[i].x = 0.0f;
				m_speed[i].y = 0.0f;
			}
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += m_AddScale;
				m_scale[i].y += m_AddScale;
				m_scale[i].z += m_AddScale;

				if (m_scale[i].x >= m_StartScale + 0.1f) {
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
//宝箱のパーティクル
void ParticleTex::ChestParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	m_DrawCount = 0;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < m_NormalParticleCount; i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				/*m_AddPower[i].x = (float)(rand() % 3 - 1);
				m_AddPower[i].y = (float)(rand() % 2 - 1);*/
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.04f,0.04f };
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
	for (int i = 0; i < m_NormalParticleCount; i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.003f;
			m_AddPower[i].y = 0.05f;
			m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			m_pos[i].y += m_AddPower[i].y;
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += m_AddScale;
				m_scale[i].y += m_AddScale;
				m_scale[i].z += m_AddScale;

				if (m_scale[i].x >= m_StartScale + 0.1f) {
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
//セーブのパーティクル
void ParticleTex::SaveParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	m_DrawCount = 0;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < m_NormalParticleCount; i++) {
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
	for (int i = 0; i < m_NormalParticleCount; i++) {
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
