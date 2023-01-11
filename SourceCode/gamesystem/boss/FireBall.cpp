#include "FireBall.h"
#include "ImageManager.h"
#include "imgui.h"
#include "Collision.h"
//読み込み
FireBall::FireBall() {
	IKETexture* firetex_;
	firetex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	firetex_->TextureCreate();
	firetex_->SetPosition({ 0.0f,90.0f,0.0f });
	firetex.reset(firetex_);
}
//初期化
bool FireBall::Initialize() {
	m_Scale = { 0.4f, 0.4f, 0.4f };
	m_Color = { 1.0f,0.5f,0.0f,1.0f };
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
	return true;
}
//更新
void FireBall::Update() {
	m_OldPos = m_Position;
	Shot();
	//更新とセット
	if (m_Alive) {
		firetex->Update();
		//Obj_SetParam();
	}
	if ((m_Position.x <= -140.0f || m_Position.x >= 250.0f) || (m_Position.y <= -155.0f || m_Position.y >= -100.0f)) {
		m_Alive = false;
	}
	firetex->SetColor({ 1.0f,0.5f,0.0f,1.0f });
	firetex->SetPosition(m_Position);
	firetex->SetScale(m_Scale);
	//パーティクルの更新
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->SetParticleBreak(true);
	for (int i = 0; i < 2; i++) {
		particletex->Update(m_Position, m_ParticleCount, 2, 0);
	}
}
//ポーズ時
void FireBall::Pause() {
	if (m_Alive) {
		firetex->Update();
		//m_Object->Update();
	}
}
//描画
void FireBall::Draw(DirectXCommon* dxCommon) {
	IKETexture::PreDraw(1);
	if (m_Alive) {
	/*ImGui::Begin("Ball");
	ImGui::Text("m_Alive:%d", m_Alive);
	ImGui::End();*/
		//Obj_Draw();
	firetex->Draw();
	}
	particletex->Draw();
}
//実際に弾を撃つ
void FireBall::Shot() {
	//弾が出現したらパーティクルも発生する
	if (m_Alive) {
		m_ParticleCount++;
		if (m_ParticleCount > 2) {
			m_ParticleCount = 0;
		}
		m_Position.x += m_AddSpeed;
		m_Position.y += m_AddPowerY;
	}
	else {
		m_ParticleCount = 0;
	}
}

bool FireBall::Collide(XMFLOAT3 pos) {
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 1.5f, pos.x, pos.y, 1.5f)
		 && (m_Alive)) {
		m_Alive = false;
		return true;
	}
	else {
		return false;
	}

	return true;
}