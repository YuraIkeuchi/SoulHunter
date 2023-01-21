#include "SwordParticle.h"
#include "ModelManager.h"
#include "imgui.h"
SwordParticle::SwordParticle() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::Particle);
}

void SwordParticle::Initialize() {
	IKEObject3d* object_[Particle_Max];
	for (int i = 0; i < object.size(); i++) {
		object_[i] = new IKEObject3d();
		object_[i] = IKEObject3d::Create();
		//object_[i]->CreateGraphicsPipeline(L"Resources/shaders/BasicVS.hlsl", L"Resources/shaders/BasicPS.hlsl");
		object_[i]->SetModel(model);
		object_[i]->SetColor(m_StartColor);
		object_[i]->SetPosition(m_pos[i]);
		object_[i]->SetLightEffect(false);
		//object_[i]->SetScale({ 5.0f,15.0f,5.0f });
		object[i].reset(object_[i]);
		m_pos[i] = { 0.0f,3.0f,3.0f };
	}

}

void SwordParticle::Update(XMFLOAT3 StartPos, int Timer, int TargetTimer, XMMATRIX matrix) {
	NormalParticle(Timer, TargetTimer, matrix);
	for (int i = 0; i < object.size(); i++) {
		object[i]->SetPosition(m_pos[i]);
		object[i]->SetScale(m_scale[i]);
		object[i]->SetColor(m_StartColor);
		if (m_Alive[i]) {
			object[i]->AffineUpdate();
		}
	}
}

void SwordParticle::Draw() {
	IKEObject3d::PreDraw();
	for (int i = 0; i < object.size(); i++) {
		if (m_Alive[i]) {
			object[i]->Draw();
		}
	}
}

void SwordParticle::ImGuiDraw() {
	//ImGui::Begin("color");
	//for (int i = 0; i < m_NormalParticleCount; i++) {
	//	ImGui::Text("Affine[%d]::%d", i, object[i]->GetAffine());
	//}
	//ImGui::End();
}

void SwordParticle::ChangeShader(int DrawNumber) {
	/*if (m_ShaderChange) {
		if (DrawNumber == 0) {
			for (int i = 0; i < object.size(); i++) {
				object[i]->CreateGraphicsPipeline(L"Resources/shaders/BasicVS.hlsl", L"Resources/shaders/BasicPS.hlsl");
			}
			}
		else if (DrawNumber == 1) {
			for (int i = 0; i < object.size(); i++) {
				object[i]->CreateGraphicsPipeline(L"Resources/shaders/ToonVS.hlsl", L"Resources/shaders/ToonPS.hlsl");
			}
		}
		else if (DrawNumber == 2) {
			for (int i = 0; i < object.size(); i++) {
				object[i]->CreateGraphicsPipeline(L"Resources/shaders/SingleColorVS.hlsl", L"Resources/shaders/SingleColorPS.hlsl");
			}
		}
		m_ShaderChange = false;
	}*/
}

void SwordParticle::NormalParticle(int Timer, int TargetTimer, XMMATRIX matrix) {
	
	for (int i = 0; i < object.size(); i++) {
		if (m_Alive[i]) {
			m_pos[i].x += (cos(m_angle[i]) * m_speed[i].x);
			m_pos[i].y += (sin(m_angle[i]) * m_speed[i].y);
			/*	m_speed[i].x += 0.05f;
				m_speed[i].y += 0.05f;*/
			if (!m_ScaleChange[i]) {
				m_scale[i].x += 0.01f;
				m_scale[i].y += 0.01f;
				m_scale[i].z += 0.01f;

				if (m_scale[i].x >= 0.2f) {
					m_ScaleChange[i] = true;
				}
			}
			else {
				m_scale[i].x -= 0.01f;
				m_scale[i].y -= 0.01f;
				m_scale[i].z -= 0.01f;

				if (m_scale[i].x <= 0.0f) {
					m_Alive[i] = false;
				}
			}
		}
	}

}
void SwordParticle::SetMatrix(XMMATRIX matrix)
{
	for (int i = 0; i < object.size(); i++) {
		if (!m_Alive[i]) {
			object[i]->AddMatrix(matrix);
		}
	}
}

void SwordParticle::SetParticle(int Timer, int TargetTimer, XMMATRIX matrix) {
	if (Timer >= TargetTimer) {
		for (int i = 0; i < object.size(); i++) {
			if (!m_Alive[i]) {
				object[i]->AddMatrix(matrix);
				//パーティクルを出す
				m_RandPos[i] = { 0,
			 (static_cast<float>(rand() % 20) + 20) * -1.2f,
				 (static_cast<float>(rand() % 30) + 10)
				};
				m_RandPos[i] = { m_RandPos[i].x,
					m_RandPos[i].y / 10,
					 m_RandPos[i].z / 10
				};
				m_pos[i] = m_RandPos[i];
				m_angle[i] = (float)(rand() % 360);
				m_speed[i] = { 0.02f,0.02f };
				m_Number[i] = rand() % 2;
				m_addPower[i].y = 0.0f;
				m_scale[i] = { 0.1f,0.1f,0.1f };
				m_Alive[i] = true;
				m_ScaleChange[i] = false;
				break;
			}
		}
	}
}