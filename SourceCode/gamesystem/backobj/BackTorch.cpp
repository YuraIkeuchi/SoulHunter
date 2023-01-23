#include "BackTorch.h"
#include <Easing.h>
#include "ParticleEmitter.h"
BackTorch::BackTorch() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}

//������
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
	return true;
}

//�Z�b�g
void BackTorch::SetObj() {
	m_ParticleCount++;
	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}

	ParticleEmitter::GetInstance()->DemoEffect(40, { m_Position.x,m_Position.y + 8.0f,m_Position.z }, 2.0f, 0.0f, { 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });
}
//���ʂȕ`��
void BackTorch::specialDraw() {
}

void BackTorch::Draw(DirectXCommon* dxCommon) {
	
	//�I�u�W�F�N�g�̕`��
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		specialDraw();
		Obj_Draw();
	}
}
