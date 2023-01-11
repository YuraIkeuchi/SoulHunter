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
		m_scale[i] = { 0.0f,0.0f,0.0f };
		particletex_[i]->SetScale(m_scale[i]);
		particletex[i].reset(particletex_[i]);
		m_pos[i] = { 0.0f,0.0f,0.0f };
		m_AddPower[i] = { 0.0f,0.0f,0.0f };
		m_Angle[i] = 0.0f;
		m_ScaleChange[i] = false;
		m_speed[i] = { 0.0f,0.0f };
		m_Alive[i] = false;
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
	else if (ParticleType == BossEnd) {
		BossEndParticle(StartPos, Timer, TargetTimer);
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
}
//描画
void ParticleTex::Draw() {
	IKETexture::PreDraw(1);
	for (int i = 0; i < particletex.size(); i++) {
		if (m_Alive[i]) {
			particletex[i]->Draw();
		}
	}
}
//IMGuiの描画
void ParticleTex::ImGuiDraw() {
	/*ImGui::Begin("particle");
	ImGui::SetWindowPos(ImVec2(0, 500));
	ImGui::SetWindowSize(ImVec2(280, 240));
	for (int i = 0; i < particletex.size(); i++) {
		ImGui::Text("m_PosX[%d]:%f", i,m_pos[i].x);
		ImGui::Text("m_PosY[%d]:%f", i,m_pos[i].y);
		ImGui::Text("m_PosZ[%d]:%f", i,m_pos[i].z);
	}
	ImGui::End();*/
}
//普通のパーティクル
void ParticleTex::NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.02f,0.02f };
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z};
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
	for (int i = 0; i < particletex.size(); i++) {
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
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_speed[i] = { 0.1f,0.02f };
				m_Number[i] = rand() % 2;
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z};
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
	for (int i = 0; i < particletex.size(); i++) {
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
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.3f,0.3f };
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z};
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
	for (int i = 0; i < particletex.size(); i++) {
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
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.04f,0.04f };
				m_Number[i] = rand() % 2;
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z};
				m_AddPower[i].y = 0.05f;
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
	for (int i = 0; i < particletex.size(); i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.003f;
			m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			m_pos[i].y += m_AddPower[i].y;
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
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.03f,0.03f };
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z};
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
	for (int i = 0; i < particletex.size(); i++) {
		if (m_Alive[i]) {
			m_AddScale = 0.005f;
			m_AddPower[i].y += 0.001f;
			if (m_AddPower[i].y <= 0.01f) {
				m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
			}
			m_pos[i].y += float((sin(m_Angle[i])) * m_speed[i].y) + m_AddPower[i].y;
			m_color[i].w -= 0.001f;
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
//ボスをたおした時のパーティクル
void ParticleTex::BossEndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	m_StartPos = StartPos;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_Alive[i]) {
				m_color[i] = m_StartColor;
				m_AddPower[i].z = (float)(rand() % 10 - 5);
				m_Angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.3f,0.3f };
				m_pos[i] = { m_StartPos.x,m_StartPos.y,m_StartPos.z + m_AddPower[i].z };
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
	for (int i = 0; i < particletex.size(); i++) {
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
