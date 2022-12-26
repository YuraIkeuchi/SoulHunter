#include "FireBall.h"
#include "ImageManager.h"
#include "imgui.h"
#include "Collision.h"
//読み込み
FireBall::FireBall() {
	//m_Model = ModelManager::GetInstance()->GetModel(ModelManager::Particle);
	//IKEObject3d* m_Object_;
	//m_Object_ = new IKEObject3d();
	//m_Object_ = IKEObject3d::Create();
	////obje3dci]->CreateGraphicsPipeline(L"Resources/shaders/BasicVS.hlsl", L"Resources/shaders/BasicPS.hlsl");
	//m_Object_->SetModel(m_Model);
	//m_Object_->SetLightEffect(false);
	//m_Object.reset(m_Object_);
	IKETexture* firetex_;
	firetex_ = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	firetex_->TextureCreate();
	firetex_->SetPosition({ 0.0f,90.0f,0.0f });
	firetex.reset(firetex_);
}
//初期化
bool FireBall::Initialize() {
	m_Scale = { 0.3f, 0.3f, 0.3f };
	m_Color = { 1.0f,0.5f,0.0f,1.0f };
	//m_Object->SetPosition(m_Position);
	//m_Object->SetScale(m_Scale);
	//ParticleObj* particleobj_ = new ParticleObj();
	//particleobj_->Initialize();
	//particleobj.reset(particleobj_);

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
	if (m_Position.x <= -140.0f || m_Position.x >= 250.0f) {
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