#include "PlayerSoul.h"
#include"Collision.h"
#include"ImageManager.h"
#include "Easing.h"
#include "ParticleEmitter.h"
#include "VariableCommon.h"
using namespace DirectX;
//�ǂݍ���
PlayerSoul::PlayerSoul() {
	IKETexture* soultex_;
	soultex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	soultex_->TextureCreate();
	soultex_->SetPosition({ 0.0f,90.0f,0.0f });
	//DushEffecttexture->SetRotation({ 90,0,0 });
	soultex.reset(soultex_);
}
//������
void PlayerSoul::Initialize() {
	m_Scale = { 0.0f,0.0f,0.0f };
	m_Radius.x = 2.0f;
	m_Radius.y = 0.8f;
	m_Effect = false;
	m_EndSoul = false;
}
//���
void PlayerSoul::Finalize() {

}
//�X�V
void PlayerSoul::Update(InterEnemy* enemy) {
	//�G�t�F�N�g�̔���
	m_OldPos= m_Position;
	SetEffect(enemy);
	if (block->PlayerSoulMapCollideCommon(m_Position, m_Radius,m_OldPos, m_Jump,
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
	//�p�[�e�B�N��
	BirthParticle();
	soultex->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	soultex->SetPosition(m_Position);
	soultex->SetScale(m_Scale);
	soultex->SetColor(m_Color);
	if (UpdateCollide()) {
		if (m_Effect) {
			soultex->Update();
		}
	}
	else {
		m_ParticleCount = 0;
	}
}
//�`��
void PlayerSoul::Draw() {
	IKETexture::PreDraw(AddBlendType);
	if (DrawCollide()) {
		if (m_Effect) {
			soultex->Draw();
		}
	}
}
//�G�t�F�N�g�̓���
void PlayerSoul::SetEffect(InterEnemy* enemy) {
	//�G�t�F�N�g�̔���
	if (enemy->GetSoul() && !m_Effect && !m_EndSoul) {
		m_Scale = { 0.2f,0.2f,0.2f };
		m_BoundPower = (float)(rand() % 8 - 4);
		m_AddPower = (float)(rand() % 3 + 3);
		if (m_BoundPower == 0.0f) {
			m_BoundPower = 1.0f;
		}

		m_BoundPower = m_BoundPower / 10;
		m_AddPower = m_AddPower / 10;
		m_Position = enemy->GetPosition();
		m_Effect = true;
		m_EndSoul = true;
	}
	if (m_Effect && !m_Move) {
		m_ParticleCount++;

		if (m_ParticleCount > 10) {
			m_ParticleCount = 0;
		}
		m_AddPower -= 0.02f;
		m_Position.x += m_BoundPower;
		m_Position.y += m_AddPower;
		if (m_Scale.x <= 0.0f) {
			m_Effect = false;
			enemy->SetSoul(false);
		}
	}
}
//�����蔻��
bool PlayerSoul::Collide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 1.5f, m_PlayerPos.x, m_PlayerPos.y, 1.5f) && (m_Effect) && (!m_Move)) {
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
		m_Position = {
			Ease(In,Cubic,m_Frame,m_Position.x,m_AfterPos.x),
			Ease(In,Cubic,m_Frame,m_Position.y,m_AfterPos.y),
			Ease(In,Cubic,m_Frame,m_Position.z,m_AfterPos.z)
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
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 20.0f, m_PlayerPos.x, m_PlayerPos.y, 20.0f)) {
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
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 20.0f, m_PlayerPos.x, m_PlayerPos.y, 20.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

void PlayerSoul::BirthParticle() {
	XMFLOAT4 s_color = { 0.0f,0.5f,1.0f,0.8f };
	XMFLOAT4 e_color = { 0.0f,0.5f,1.0f,0.8f };
	float s_scale = 3.0f;
	float e_scale = 0.0f;


	if (m_ParticleCount > 3) {
		ParticleEmitter::GetInstance()->FireEffect(50, { m_Position.x,m_Position.y - 0.5f,m_Position.z }, s_scale, e_scale, s_color, e_color);
		m_ParticleCount = 0;
	}
}