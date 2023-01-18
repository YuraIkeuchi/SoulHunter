//#include "ParticleHeal.h"
//#include "ImageManager.h"
//#include "imgui.h"
////読み込み
//ParticleHeal::ParticleHeal() {
//
//}
////初期科
//void ParticleHeal::Initialize() {
//	IKETexture* particletex_[ParticleHeal_Max];
//	for (int i = 0; i < particletex.size(); i++) {
//		particletex_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
//		particletex_[i]->TextureCreate();
//		particletex_[i]->SetPosition({ 0.0f,90.0f,0.0f });
//		//DushEffecttexture->SetRotation({ 90,0,0 });
//		m_scale[i] = { 0.0f,0.0f,0.0f };
//		m_Alive[i] = false;
//		particletex_[i]->SetScale(m_scale[i]);
//		particletex[i].reset(particletex_[i]);
//	}
//
//	IKETexture* healeffecttex_;
//	healeffecttex_ = IKETexture::Create(ImageManager::HealEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
//	healeffecttex_->TextureCreate();
//	healeffecttex.reset(healeffecttex_);
//	m_HealEffectNumber = Appear;
//}
////更新
//void ParticleHeal::Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
//	ParticleMove(StartPos, Timer, TargetTimer);
//	for (int i = 0; i < particletex.size(); i++) {
//		particletex[i]->SetPosition(m_pos[i]);
//		particletex[i]->SetScale(m_scale[i]);
//		particletex[i]->SetColor(m_color[i]);
//		if (m_Alive[i]) {
//			particletex[i]->Update();
//		}
//	}
//	HealEffect(StartPos);
//	if (m_Heal) {
//		healeffecttex->Update();
//	}
//	healeffecttex->SetColor({ 0.8f,1.0f,0.1f,0.5f });
//	healeffecttex->SetPosition(m_HealPos);
//	healeffecttex->SetRotation(m_HealRot);
//	healeffecttex->SetScale(m_HealScale);
//	healeffecttex->SetColor(m_HealColor);
//	//else if (ParticleType == Heal) {
//
//	//	HealParticle(StartPos, Timer, TargetTimer);
//	//	for (int i = 0; i < m_HealParticleCount; i++) {
//	//		object[i]->SetPosition(m_pos[i]);
//	//		object[i]->SetScale(m_scale[i]);
//	//		object[i]->SetColor(m_color);
//	//		if (m_Alive[i]) {
//	//			object[i]->Update();
//	//		}
//	//	}
//	//}
//
//}
////描画
//void ParticleHeal::Draw() {
//	//ImGui::Begin("Heal");
//	//ImGui::SliderFloat("color.a", &m_HealColor.w, 1, 0);
//	//ImGui::End();
//	IKETexture::PreDraw(1);
//	for (int i = 0; i < particletex.size(); i++) {
//		if (m_Alive[i]) {
//			particletex[i]->Draw();
//		}
//	}
//	IKETexture::PreDraw(0);
//	if (m_HealStart) {
//		healeffecttex->Draw();
//	}
//}
////IMGuiの描画
//void ParticleHeal::ImGuiDraw() {
//	
//}
////回復のパーティクル
//void ParticleHeal::ParticleMove(const XMFLOAT3& StartPos, int Timer, int TargetTimer) {
//	m_StartPos = StartPos;
//	//フレーム数が目標を超えたら出現する
//	if (Timer >= TargetTimer) {
//		for (int i = 0; i < particletex.size(); i++) {
//			//飛ばす方向をランダムで決める
//			if (!m_Alive[i]) {
//				m_color[i] = m_StartColor;
//				m_AddPower[i].x = (float)(rand() % 4 - 2) / 5;
//				m_Angle[i] = (float)(rand() % 360);
//				m_speed[i] = { 0.08f,0.08f };
//				m_Number[i] = rand() % 2;
//				/*	m_AddPower[i].x = m_AddPower[i].x / 10;
//					m_AddPower[i].y = m_AddPower[i].y / 20;*/
//				m_pos[i].x = m_StartPos.x + m_AddPower[i].x;
//				m_pos[i].y = m_StartPos.y;
//				m_pos[i].z = m_StartPos.z;
//				m_AddPower[i].y = 0.0f;
//				m_scale[i] = { 0.4f,0.4f,0.4f };
//				m_Alive[i] = true;
//				m_ScaleChange[i] = false;
//				break;
//			}
//		}
//	}
//	//実際に動く
//	for (int i = 0; i < particletex.size(); i++) {
//		if (m_Alive[i]) {
//			m_AddPower[i].y = 0.05f;
//			//m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
//			m_pos[i].y += m_AddPower[i].y;
//			m_scale[i].x -= 0.005f;
//			m_scale[i].y -= 0.005f;
//			m_scale[i].z -= 0.005f;
//
//			if (m_scale[i].x <= 0.0f) {
//				m_Alive[i] = false;
//			}
//			
//		}
//	}
//}
////開腹した瞬間のエフェクト
//void ParticleHeal::HealEffect(const XMFLOAT3& StartPos) {
//	if (m_Heal && !m_HealStart) {
//		m_HealPos = StartPos;
//		m_HealStart = true;
//	}
//	//エフェクトの動き
//	if (m_HealStart) {
//		m_HealRot.z += 10.0f;
//		if (m_HealEffectNumber == Appear) {
//			m_HealScale.x += 0.2f;
//			m_HealScale.y += 0.2f;
//			m_HealScale.z += 0.2f;
//			m_HealColor.w += 0.05f;
//			if (m_HealColor.w > 1.0f) {
//				m_HealEffectNumber = Disappear;
//			}
//		}
//		else {
//			m_HealColor.w -= 0.05f;
//			if (m_HealColor.w < 0.0f) {
//				m_HealScale = { 0.0f,0.0f,0.0f };
//				m_HealColor.w = 0.0f;
//				m_HealEffectNumber = Appear;
//				m_Heal = false;
//				m_HealStart = false;
//			}
//		}
//	}
//}
