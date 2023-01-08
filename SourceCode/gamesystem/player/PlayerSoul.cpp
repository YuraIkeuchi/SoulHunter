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
	m_Scale = { 0.0f,0.0f,0.0f };
	m_Radius.x = 2.0f;
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
	m_OldPos= m_Pos;
	SetEffect(enemy);
	if (block->PlayerSoulMapCollideCommon(m_Pos, m_Radius,m_OldPos, m_Jump,
		m_AddPower) && m_Effect) {
		m_AddPower = 0.0f;
		m_BoundPower = 0.0f;
	}
	//�����蔻��
	Collide();
	//���̓���
	Move();
	//����������
	VanishSoul(enemy);

	if (UpdateCollide()) {
		if (m_Effect) {
			soultex->Update();
		}
		soultex->SetColor({ 1.0f,1.0f,1.0f,1.0f });
		soultex->SetPosition(m_Pos);
		soultex->SetScale(m_Scale);
		soultex->SetColor(m_Color);
		particlesoul->SetStartColor({ 0.0f,0.5f,1.0f,0.8f });
		particlesoul->SetParticleBreak(true);
		particlesoul->Update({ m_Pos.x,m_Pos.y - 0.5f,m_Pos.z }, m_ParticleCount, 10, 0);
	}
	else {
		m_ParticleCount = 0;
	}
}
//�`��
void PlayerSoul::Draw() {
	IKETexture::PreDraw(1);
	if (DrawCollide()) {
		if (m_Effect) {
			soultex->Draw();
		}
		particlesoul->Draw();
	}
	
}
//�G�t�F�N�g�̓���
void PlayerSoul::SetEffect(InterEnemy* enemy) {
	//�G�t�F�N�g�̔���
	//�G�t�F�N�g�̔���
	if (enemy->GetSoul() && !m_Effect && !m_EndSoul) {
		m_Scale = { 0.2f,0.2f,0.2f };
		m_BoundPower = (float)(rand() % 8 - 4);
		m_AddPower = (float)(rand() % 3 + 3);
		//effectcolor.w = (float)(rand() % 10);
		if (m_BoundPower == 0.0f) {
			m_BoundPower = 1.0f;
		}

		m_BoundPower = m_BoundPower / 10;
		m_AddPower = m_AddPower / 10;
		m_Pos = enemy->GetPosition();
		m_Effect = true;
		m_EndSoul = true;
	}
	if (m_Effect && !m_Move) {
		m_ParticleCount++;

		if (m_ParticleCount > 10) {
			m_ParticleCount = 0;
		}
		m_AddPower -= 0.02f;
		m_Pos.x += m_BoundPower;
		m_Pos.y += m_AddPower;
	/*	m_Scale[0].x -= 0.01f;
		m_Scale[0].y -= 0.01f;
		m_Scale[0].z -= 0.01f;*/
		if (m_Scale.x <= 0.0f) {
			m_Effect = false;
			enemy->SetSoul(false);
		}
	}
}
//�����蔻��
bool PlayerSoul::Collide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Pos.x, m_Pos.y, 1.2f, m_PlayerPos.x, m_PlayerPos.y, 1.2f) && (m_Effect) && (!m_Move)) {
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
		m_Pos = {
			Ease(In,Cubic,m_Frame,m_Pos.x,m_AfterPos.x),
			Ease(In,Cubic,m_Frame,m_Pos.y,m_AfterPos.y),
			Ease(In,Cubic,m_Frame,m_Pos.z,m_AfterPos.z)
		};
		m_Scale = {
			Ease(In,Cubic,m_Frame,m_Scale.x,0.05f),
			Ease(In,Cubic,m_Frame,m_Scale.y,0.05f),
			Ease(In,Cubic,m_Frame,m_Scale.z,0.05f)
		};
	}
}
//����������
void PlayerSoul::VanishSoul(InterEnemy* enemy) {
	if (m_Effect) {
		m_Timer++;
		if (m_Timer > 400) {
			m_Frame += 0.025f;
			m_Scale = {
		Ease(In,Cubic,m_Frame,m_Scale.x,0.0f),
		Ease(In,Cubic,m_Frame,m_Scale.y,0.0f),
		Ease(In,Cubic,m_Frame,m_Scale.z,0.0f)
			};
		}

		if (m_Scale.x == 0.0f) {
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
}
//�X�V��͈͓��ɓ��������̂�
bool PlayerSoul::UpdateCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Pos.x, m_Pos.y, 20.0f, m_PlayerPos.x, m_PlayerPos.y, 20.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//�`���͈͓��ɓ��������̂�
bool PlayerSoul::DrawCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Pos.x, m_Pos.y, 20.0f, m_PlayerPos.x, m_PlayerPos.y, 20.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}