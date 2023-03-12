#include "ThornParticle.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include <random>
#include "VariableCommon.h"
//読み込み
ThornParticle::ThornParticle() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::NormalBlock);
}
//初期科
void ThornParticle::Initialize() {
	IKETexture* particletex_[ThornParticleTex_Max];
	for (int i = 0; i < particletex.size(); i++) {
		particletex_[i] = IKETexture::Create(ImageManager::SmokeTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		particletex_[i]->TextureCreate();
		particletex_[i]->SetPosition({ 0.0f,90.0f,0.0f });
		m_scale[i] = { 0.0f,0.0f,0.0f };
		m_SmokeAlive[i] = false;
		particletex_[i]->SetScale(m_scale[i]);
		particletex[i].reset(particletex_[i]);
	}

	IKEObject3d* particleobj_[ThornParticleObj_Max];
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
//煙の方の更新
void ThornParticle::TexUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ThornDir) {
	if (ThornDir == Up) {
		UpSmokeParticle(StartPos,Timer,TargetTimer);
	}
	else if (ThornDir == Down) {
		DownSmokeParticle(StartPos, Timer, TargetTimer);
	}
	else if (ThornDir == Right) {
		RightSmokeParticle(StartPos, Timer, TargetTimer);
	}
	else if (ThornDir == Left) {
		LeftSmokeParticle(StartPos, Timer, TargetTimer);
	}
	for (int i = 0; i < particletex.size(); i++) {
		particletex[i]->SetPosition(m_SmokePos[i]);
		particletex[i]->SetScale(m_scale[i]);
		particletex[i]->SetColor(m_color[i]);
		if (m_SmokeAlive[i]) {
			particletex[i]->Update();
		}
	}
}
//岩の方の更新
void ThornParticle::ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ThornDir) {
	if (ThornDir == Up) {
		UpRockParticle(StartPos, Timer, TargetTimer);
	}
	else if (ThornDir == Down) {
		DownRockParticle(StartPos, Timer, TargetTimer);
	}
	else if (ThornDir == Right) {
		RightRockParticle(StartPos, Timer, TargetTimer);
	}
	else if (ThornDir == Left) {
		LeftRockParticle(StartPos, Timer, TargetTimer);
	}
	for (int i = 0; i < particleobj.size(); i++) {
		particleobj[i]->SetPosition(m_RockPos[i]);
		particleobj[i]->SetScale(m_Rockscale[i]);
		if (m_RockAlive[i]) {
			particleobj[i]->Update();
		}
	}
}
//描画
void ThornParticle::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < particleobj.size(); i++) {
		if (m_RockAlive[i]) {
			particleobj[i]->Draw();
		}
	}
	IKETexture::PreDraw(0);
	for (int i = 0; i < particletex.size(); i++) {
		if (m_SmokeAlive[i]) {
			particletex[i]->Draw();
		}
	}
}
//ImGui
void ThornParticle::ImGuiDraw() {
}
//各方向の更新
void ThornParticle::UpSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.01f;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_SmokeAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				m_color[i] = m_StartColor;
				m_color[i].w = 0.2f;
				m_SmokeRandPos[i].x = float(l_smokedist(mt));
				m_speed[i] = { 0.1f,0.6f };
				m_SmokePos[i].x = StartPos.x + m_SmokeRandPos[i].x;
				m_SmokePos[i].y = StartPos.y;
				m_SmokePos[i].z = StartPos.z;
				m_SmokeAddPower[i].y = 0.0f;
				m_scale[i] = { 0.5f,0.5f,0.5f };
				m_SmokeAlive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
	//実際に動く
	for (int i = 0; i < particletex.size(); i++) {
		if (m_SmokeAlive[i]) {
			m_SmokePos[i].y += m_speed[i].y;
			helper->Float3SubFloat(m_scale[i], l_AddScale);
			if (helper->CheckMax(m_scale[i].x,m_ResetFew,m_ResetFew)) {
				m_SmokeAlive[i] = false;
			}
		}
	}
}
void ThornParticle::DownSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.01f;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_SmokeAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				m_color[i] = m_StartColor;
				m_color[i].w = 0.2f;
				m_SmokeRandPos[i].x = float(l_smokedist(mt));
				m_speed[i] = { 0.1f,0.6f };
				m_SmokePos[i].x = StartPos.x + m_SmokeRandPos[i].x;
				m_SmokePos[i].y = StartPos.y;
				m_SmokePos[i].z = StartPos.z;
				m_SmokeAddPower[i].y = 0.0f;
				m_scale[i] = { 0.5f,0.5f,0.5f };
				m_SmokeAlive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
	//実際に動く
	for (int i = 0; i < particletex.size(); i++) {
		if (m_SmokeAlive[i]) {
			m_SmokePos[i].y -= m_speed[i].y;
			helper->Float3SubFloat(m_scale[i], l_AddScale);
			if (helper->CheckMax(m_scale[i].x, m_ResetFew, m_ResetFew)) {
				m_SmokeAlive[i] = false;
			}
		}
	}
}
void ThornParticle::RightSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.01f;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_SmokeAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				m_color[i] = m_StartColor;
				m_color[i].w = 0.2f;
				m_SmokeRandPos[i].y = float(l_smokedist(mt));
				m_speed[i] = { 0.6f,0.1f };
				m_SmokePos[i].x = StartPos.x;
				m_SmokePos[i].y = StartPos.y + m_SmokeRandPos[i].y;
				m_SmokePos[i].z = StartPos.z;
				m_SmokeAddPower[i].y = 0.0f;
				m_scale[i] = { 0.5f,0.5f,0.5f };
				m_SmokeAlive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
	//実際に動く
	for (int i = 0; i < particletex.size(); i++) {
		if (m_SmokeAlive[i]) {
			m_SmokePos[i].x += m_speed[i].x;
			helper->Float3SubFloat(m_scale[i], l_AddScale);
			if (helper->CheckMax(m_scale[i].x, m_ResetFew, m_ResetFew)) {
				m_SmokeAlive[i] = false;
			}
		}
	}
}
void ThornParticle::LeftSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.01f;
	//フレーム数が目標を超えたら出現する
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particletex.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_SmokeAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				m_color[i] = m_StartColor;
				m_color[i].w = 0.2f;
				m_SmokeRandPos[i].y = float(l_smokedist(mt));
				m_speed[i] = { 0.6f,0.1f };
				m_SmokePos[i].x = StartPos.x;
				m_SmokePos[i].y = StartPos.y + m_SmokeRandPos[i].y;
				m_SmokePos[i].z = StartPos.z;
				m_SmokeAddPower[i].y = 0.0f;
				m_scale[i] = { 0.5f,0.5f,0.5f };
				m_SmokeAlive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
	//実際に動く
	for (int i = 0; i < particletex.size(); i++) {
		if (m_SmokeAlive[i]) {
			m_SmokePos[i].x -= m_speed[i].x;
			helper->Float3SubFloat(m_scale[i], l_AddScale);
			if (helper->CheckMax(m_scale[i].x, m_ResetFew, m_ResetFew)) {
				m_SmokeAlive[i] = false;
			}
		}
	}
}
void ThornParticle::UpRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.005f;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_RockAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				uniform_int_distribution<int> l_powerdist(5, 10);
				m_Rockscale[i] = { 0.3f,0.3f,0.3f };
				m_RockRandPos[i].x = float(l_smokedist(mt));
				m_RockPos[i].x = StartPos.x + m_RockRandPos[i].x;
				m_RockPos[i].y = StartPos.y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = float(l_powerdist(mt)) / 10;
				m_RockAddPower[i].x = float(l_smokedist(mt)) / 10;
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
			helper->Float3SubFloat(m_Rockscale[i], l_AddScale);
			if (helper->CheckMax(m_Rockscale[i].x, m_ResetFew, m_ResetFew)) {
				m_RockAlive[i] = false;
			}
		}
	}
}
void ThornParticle::DownRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.005f;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_RockAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				m_Rockscale[i] = { 0.3f,0.3f,0.3f };
				m_RockRandPos[i].x = float(l_smokedist(mt));
				m_RockPos[i].x = StartPos.x + m_RockRandPos[i].x;
				m_RockPos[i].y = StartPos.y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = 0.0f;
				m_RockAddPower[i].x = float(l_smokedist(mt)) / 10;
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
			helper->Float3SubFloat(m_Rockscale[i], l_AddScale);
			if (helper->CheckMax(m_Rockscale[i].x, m_ResetFew, m_ResetFew)) {
				m_RockAlive[i] = false;
			}
		}
	}
}
void ThornParticle::RightRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.005f;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_RockAlive[i]) {
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				uniform_int_distribution<int> l_powerdist(3, 6);
				m_Rockscale[i] = { 0.3f,0.3f,0.3f };
				m_RockRandPos[i].y = float(l_smokedist(mt));
				m_RockPos[i].x = StartPos.x;
				m_RockPos[i].y = StartPos.y + m_RockRandPos[i].y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = 0.0f;
				m_RockAddPower[i].x = float(l_smokedist(mt)) / 10;
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
			helper->Float3SubFloat(m_Rockscale[i], l_AddScale);
			if (helper->CheckMax(m_Rockscale[i].x, m_ResetFew, m_ResetFew)) {
				m_RockAlive[i] = false;
			}
		}
	}
}
void ThornParticle::LeftRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
	float l_AddScale = 0.005f;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < particleobj.size(); i++) {
			//飛ばす方向をランダムで決める
			if (!m_RockAlive[i]) {
				m_Rockscale[i] = { 0.3f,0.3f,0.3f };
				//乱数指定
				mt19937 mt{ std::random_device{}() };
				uniform_int_distribution<int> l_smokedist(-3, 3);
				uniform_int_distribution<int> l_powerdist(3, 6);
				m_RockRandPos[i].y = float(l_smokedist(mt));
				m_RockPos[i].x = StartPos.x;
				m_RockPos[i].y = StartPos.y + m_RockRandPos[i].y;
				m_RockPos[i].z = StartPos.z;
				m_RockAddPower[i].y = 0.0f;
				m_RockAddPower[i].x = float(l_powerdist(mt)) / 10;
				m_RockAlive[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < particleobj.size(); i++) {
		if (m_RockAlive[i]) {
			m_RockAddPower[i].y -= m_Gravity[i];
			m_RockPos[i].y += m_RockAddPower[i].y;
			m_RockPos[i].x -= m_RockAddPower[i].x;
			helper->Float3SubFloat(m_Rockscale[i], l_AddScale);
			if (helper->CheckMax(m_Rockscale[i].x, m_ResetFew, m_ResetFew)) {
				m_RockAlive[i] = false;
			}
		}
	}
}