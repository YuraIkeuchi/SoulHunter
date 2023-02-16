#include "PlayerSoul.h"
#include"Collision.h"
#include"ImageManager.h"
#include "Easing.h"
#include "ParticleEmitter.h"
#include "VariableCommon.h"
using namespace DirectX;
//読み込み
PlayerSoul::PlayerSoul() {
	IKETexture* soultex_;
	soultex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	soultex_->TextureCreate();
	soultex_->SetPosition({ 0.0f,90.0f,0.0f });
	//DushEffecttexture->SetRotation({ 90,0,0 });
	soultex.reset(soultex_);
}
//初期化
void PlayerSoul::Initialize() {
	m_Scale = { 0.0f,0.0f,0.0f };
	m_Radius.x = 2.0f;
	m_Radius.y = 0.8f;
	m_Effect = false;
	m_EndSoul = false;
}
//解放
void PlayerSoul::Finalize() {

}
//更新
void PlayerSoul::Update(InterEnemy* enemy) {
	//エフェクトの発生
	m_OldPos= m_Position;
	SetEffect(enemy);
	if (block->PlayerSoulMapCollideCommon(m_Position, m_Radius,m_OldPos, m_Jump,
		m_AddPower) && m_Effect) {
		m_AddPower = 0.0f;
		m_BoundPower = 0.0f;
	}
	//当たり判定
	Collide();
	//魂の動き
	Move();
	//魂が消える
	VanishSoul(enemy);
	//パーティクル
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
//描画
void PlayerSoul::Draw() {
	IKETexture::PreDraw(AddBlendType);
	if (DrawCollide()) {
		if (m_Effect) {
			soultex->Draw();
		}
	}
}
//エフェクトの動き
void PlayerSoul::SetEffect(InterEnemy* enemy) {
	//エフェクトの発生
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
//当たり判定
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
//取った後の動き
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
//魂が消える
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
//更新を範囲内に入った時のみ
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
//描画を範囲内に入った時のみ
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