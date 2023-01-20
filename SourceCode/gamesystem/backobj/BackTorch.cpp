#include "BackTorch.h"
#include <Easing.h>
BackTorch::BackTorch() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}

//初期化
bool BackTorch::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(m_Model);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Scale = { 3.0f,6.0f,1.0f };
	object3d_->SetScale(m_Scale);
	m_Object.reset(object3d_);

	m_ParticleCount = 0;
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);

	return true;
}

//セット
void BackTorch::SetObj() {
	m_ParticleCount++;
	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->SetParticleBreak(true);
	if (UpdateCollide()) {
		particletex->Update({ m_Position.x,m_Position.y + 8.0f,m_Position.z }, m_ParticleCount, 6, 4);
	}
}
//特別な描画
void BackTorch::specialDraw() {
	particletex->Draw();
}

void BackTorch::Draw(DirectXCommon* dxCommon) {
	
	//オブジェクトの描画
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		specialDraw();
		Obj_Draw();
	}
}
