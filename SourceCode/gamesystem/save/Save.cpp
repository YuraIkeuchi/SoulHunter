#include "Save.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "Collision.h"
#include "VariableCommon.h" 
//初期化
void Save::Initialize() {
	//セーブポイント
	modelSave = ModelManager::GetInstance()->GetModel(ModelManager::Save);
	IKEObject3d* objSave_ = new IKEObject3d();
	objSave_ = IKEObject3d::Create();
	objSave_->SetModel(modelSave);
	objSave_->SetRotation({ 0.0f,90.0f,0.0f });
	//objSave_->SetPosition({ 0, 0, -30 });
	objSave_->SetScale({ 3.0f,3.0f,3.0f });
	objSave_->SetLightPower(20.0f);
	objSave.reset(objSave_);

	//セーブ時のUI
	IKESprite* SaveSprite_[4];
	const int SaveCount = 4;
	for (int i = 0; i < SaveSprite.size(); i++) {
		SaveSprite_[i] = IKESprite::Create(ImageManager::Save1, { 0.0f,0.0f });
		SaveSprite_[i]->SetPosition({ 0.0f,600.0f });
		int number_index_y = i / SaveCount;
		int number_index_x = i % SaveCount;
		SaveSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * SaveWidth_Cut, static_cast<float>(number_index_y) * SaveHeight_Cut },
			{ static_cast<float>(SaveWidth_Cut), static_cast<float>(SaveHeight_Cut) });
		SaveSprite_[i]->SetSize({ SaveWidth_Cut,SaveHeight_Cut });
		SaveSprite[i].reset(SaveSprite_[i]);
	}

	m_ParticleCount = 0;
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
	//エフェクト
	MarkEffect* markEffect_ = new MarkEffect();
	markEffect_->Initialize();
	markEffect.reset(markEffect_);
}
//更新
void Save::Update() {

	//ボタンを押すとセーブできる
	if (Collide() && m_SaveCount == 0) {
		m_GameSave = true;
		m_SaveText = true;
	}
	//テクスチャの動き
	TexMove();
	//セーブしていますとでる
	SaveAnime();
	objSave->SetPosition(m_Position);
	objSave->Update();

	//パーティクルの更新
	if (m_Alive) {
		m_ParticleCount++;
	}
	if (m_ParticleCount > 6) {
		m_ParticleCount = 0;
	}
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,0.5f });
	particletex->Update({ m_Position.x,m_Position.y + 2.0f,m_Position.z }, m_ParticleCount, 6, SavePart);
	particletex->SetParticleBreak(true);
	particletex->SetParticleBillboard(true);
	particletex->SetStartScale(0.1f);
	particletex->SetAddScale(0.008f);

	markEffect->Update({ m_Position.x,m_Position.y + 5.0f,m_Position.z });
}
//描画
const void Save::Draw() {

	IKEObject3d::PreDraw();
	if (m_Alive) {
		objSave->Draw();
	}

	IKESprite::PreDraw();
	if (m_SaveText) {
		SaveSprite[m_SaveCount]->Draw();
	}
	particletex->Draw();
	markEffect->Draw();
}

//当たり判定
bool Save::Collide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 2.5f, m_PlayerPos.x, m_PlayerPos.y, 2.5f) && m_Alive) {
		return true;
	}
	else {
		return false;
	}

	return true;
}
//セーブポイントの位置
void Save::InitSave(int StageNumber) {
	if (StageNumber == Map1) {
		m_Alive = true;
		m_Position = { 219.0f,-137.0f,10.0f };
	}
	else if (StageNumber == Map2) {
		m_Alive = false;
		m_Position = { 130.0f,0.0f,10.0f };
	}
	else if (StageNumber == Map3) {
		m_Alive = true;
		m_Position = { 211.0f,-72.0f,10.0f };
	}
	else if (StageNumber == Map4) {
		m_Alive = false;
		m_Position = { 130.0f,0.0f,10.0f };
	}
	else if (StageNumber == Map5) {
		m_Alive = true;
		m_Position = { 264.0f,-237.0f,10.0f };
	}
	else if (StageNumber == Map6) {
		m_Alive = false;
		m_Position = { 130.0f,0.0f,10.0f };
	}
	else if (StageNumber == BossMap) {
		m_Alive = false;
		m_Position = { 130.0f,0.0f,10.0f };
	}
	else if (StageNumber == TutoRial) {
		m_Alive = true;
		m_Position = { 40.0f,-282.0f,10.0f };
	}

	objSave->SetPosition(m_Position);
}
//テクスチャの動き
void Save::TexMove() {
	//sin波によって上下に動く
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);
	m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (m_Position.y + 7.0f);
	m_TexPosition.x = m_Position.x;
	m_TexPosition.z = m_Position.z;
}
//アニメーション
void Save::SaveAnime() {
	if (m_SaveText) {
		m_SaveTimer++;

		if (m_SaveTimer % 10 == 0) {
			m_SaveCount++;
		}

		if (m_SaveCount == 4) {
			m_SaveCount = 0;
		}

		if (m_SaveTimer == 80) {
			m_SaveCount = 0;
			m_SaveTimer = 0;
			m_SaveText = false;
		}
	}
}