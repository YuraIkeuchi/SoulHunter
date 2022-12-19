#include "PlayerSoul.h"
#include "Input.h"
#include"Collision.h"
#include<Easing.h>
#include<sstream>
#include <XorShift.h>
#include<iomanip>
#include"ImageManager.h"
using namespace DirectX;
//�ǂݍ���
PlayerSoul::PlayerSoul() {
	IKETexture* soultex_;
	soultex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	soultex_->TextureCreate();
	soultex_->SetPosition({ 0.0f,90.0f,0.0f });
	//DushEffecttexture->SetRotation({ 90,0,0 });
	soultex.reset(soultex_);
	ParticleSoul* particlesoul_ = new ParticleSoul();
	particlesoul_->Initialize();
	particlesoul.reset(particlesoul_);
}
//������
void PlayerSoul::Initialize() {
	//DushEffecttexture->SetRotation({ 90,0,0 });
	m_scale = { 0.0f,0.0f,0.0f };
	m_Radius.x = 1.4f;
	m_Radius.y = 0.8f;
	m_Effect = false;
}
//���
void PlayerSoul::Finalize() {

}
//�X�V
void PlayerSoul::Update(InterEnemy* enemy) {

	Input* input = Input::GetInstance();
	//�G�t�F�N�g�̔���
	m_OldPos= m_pos;
	SetEffect(enemy);
	if (block->PlayerSoulMapCollideCommon(m_pos, m_Radius,m_OldPos, m_Jump,
		m_AddPower) && m_Effect) {
		m_AddPower = 0.0f;
		m_BoundPower = 0.0f;
	}
	Collide();
	if (m_Effect) {
		m_Timer++;
		if (m_Timer > 400) {
			m_Timer = 0;
			m_Effect = false;
			enemy->SetSoul(false);
			m_ParticleCount = 0;
		}
	}
	if (enemy->GetAlive()) {
		m_Effect = false;
		m_EndSoul = false;
	}
	Move();
	if (m_Effect) {
		soultex->Update();
	}
	soultex->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	soultex->SetPosition(m_pos);
	soultex->SetScale(m_scale);

	particlesoul->SetStartColor({ 0.0f,0.5f,1.0f,0.8f });
	particlesoul->SetParticleBreak(true);
	particlesoul->Update({ m_pos.x,m_pos.y - 0.5f,m_pos.z }, m_ParticleCount, 10, 0);
	//collider.center = XMVectorSet(pos.x,pos.y,pos.z,1);
}
//�`��
void PlayerSoul::Draw() {
	//////bool playersoul = enemy->geteffect();
	//ImGui::Begin("soul");
	//ImGui::Text("m_Effect::%d", m_Effect);
	//ImGui::Text("m_endeffect::%d", m_EndSoul);
	//ImGui::End();
	IKETexture::PreDraw(1);
	if (m_Effect) {
		soultex->Draw();
	}
	particlesoul->Draw();
	
}
//�G�t�F�N�g�̓���
void PlayerSoul::SetEffect(InterEnemy* enemy) {
	//�G�t�F�N�g�̔���
	//�G�t�F�N�g�̔���
	if (enemy->GetSoul() && !m_Effect && !m_EndSoul) {
		m_scale = { 0.2f,0.2f,0.2f };
		m_BoundPower = (float)(rand() % 8 - 4);
		m_AddPower = (float)(rand() % 3 + 3);
		//effectcolor.w = (float)(rand() % 10);
		if (m_BoundPower == 0.0f) {
			m_BoundPower = 1.0f;
		}

		m_BoundPower = m_BoundPower / 10;
		m_AddPower = m_AddPower / 10;
		m_pos = enemy->GetPosition();
		m_Effect = true;
		m_EndSoul = true;
	}
	if (m_Effect && !m_Move) {
		m_ParticleCount++;

		if (m_ParticleCount > 10) {
			m_ParticleCount = 0;
		}
		m_AddPower -= 0.02f;
		m_pos.x += m_BoundPower;
		m_pos.y += m_AddPower;
	/*	m_Scale[0].x -= 0.01f;
		m_Scale[0].y -= 0.01f;
		m_Scale[0].z -= 0.01f;*/
		if (m_scale.x <= 0.0f) {
			m_Effect = false;
			enemy->SetSoul(false);
		}
	}
}
//�����蔻��
bool PlayerSoul::Collide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, 1.0f, m_PlayerPos.x, m_PlayerPos.y, 1.0f) && (m_Effect) && (!m_Move)) {
		//m_ParticleCount = 0;
		//m_Effect = false;
		m_Timer = 0;
		m_ParticleCount = 0;
		m_Frame = 0.0f;
		m_Move = true;
	
		return true;
	}
	else {
		return false;
	}

	return true;
}
//�������̓���
void PlayerSoul::Move() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (m_Move) {
		m_AfterPos = { m_PlayerPos.x - 27.0f,m_PlayerPos.y + 14.0f,m_PlayerPos.z };
		if (m_Frame < 1.0f) {
			m_Frame += 0.025f;
		}
		else {
			m_ParticleCount = 0;
			m_Effect = false;
			if (player->GetSoulCount() < 72.0f) {
				player->SetSoulCount(player->GetSoulCount() + 4.0f);
			}
			m_Move = false;
		}
		m_pos = {
			Ease(In,Cubic,m_Frame,m_pos.x,m_AfterPos.x),
			Ease(In,Cubic,m_Frame,m_pos.y,m_AfterPos.y),
			Ease(In,Cubic,m_Frame,m_pos.z,m_AfterPos.z)
		};
	}
}
