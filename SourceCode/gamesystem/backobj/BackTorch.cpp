#include "BackTorch.h"
#include <Easing.h>
BackTorch::BackTorch() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}

//‰Šú‰»
void BackTorch::Initialize() {
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(model);
	m_pos = { 110.0f,-90.0,0.0f };
	object3d_->SetPosition(m_pos);
	m_scale = { 3.0f,6.0f,1.0f };
	object3d_->SetScale(m_scale);
	object3d.reset(object3d_);
	m_ParticleCount = 0;
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
}

//ƒZƒbƒg
void BackTorch::SetObj() {
	object3d->SetPosition(m_pos);
	object3d->SetRotation(m_rot);
	object3d->SetScale(m_scale);

	m_ParticleCount++;
	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->SetParticleBreak(true);
	if (UpdateCollide()) {
		particletex->Update({ m_pos.x,m_pos.y + 8.0f,m_pos.z }, m_ParticleCount, 6, 4);
	}
}
//“Á•Ê‚È•`‰æ
void BackTorch::specialDraw() {
	//ImGui::Begin("Torch");
	//ImGui::Text("m_Position.x : %f", m_rot.x);
	//ImGui::Text("m_Position.y : %f", m_rot.y);
	//ImGui::Text("m_Position.z : %f", m_rot.z);
	//ImGui::End();
	if (DrawCollide()) {
		particletex->Draw();
	}
}
