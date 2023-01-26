#include "BackTorch.h"
#include <Easing.h>
#include "ParticleEmitter.h"
#include "VariableCommon.h"
BackTorch::BackTorch() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}

//������
bool BackTorch::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(m_Model);
	m_Position = { 810.0f,-90.0,0.0f };
	m_Scale = { 3.0f,6.0f,1.0f };
	object3d_->SetScale(m_Scale);
	m_Object.reset(object3d_);

	m_ParticleCount = 0;
	return true;
}

//�Z�b�g
void BackTorch::SetObj() {
	m_ParticleCount++;
	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}
	BirthParticle();
}
//���ʂȕ`��
void BackTorch::specialDraw() {
}

void BackTorch::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("a");
	ImGui::Text("%d", m_Particle);
	ImGui::End();*/
	//�I�u�W�F�N�g�̕`��
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		specialDraw();
		Obj_Draw();
	}
}

void BackTorch::BirthParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,0.5f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,0.5f };
	float s_scale = 3.0f;
	float e_scale = 0.0f;

	if (m_Particle) {
		ParticleEmitter::GetInstance()->FireEffect(30, { m_Position.x,m_Position.y + 8.0f,m_Position.z }, s_scale, e_scale, s_color, e_color);
	}
}

void BackTorch::ParticleCheck(int StageNumber) {
	if (StageNumber != BossMap) {
		m_Particle = true;
	}
	else {
		m_Particle = false;
	}
}
