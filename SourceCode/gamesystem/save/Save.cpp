#include "Save.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "Collision.h"
#include "ParticleEmitter.h"
#include "VariableCommon.h" 
//������
void Save::Initialize() {
	//�Z�[�u�|�C���g
	modelSave = ModelManager::GetInstance()->GetModel(ModelManager::Save);
	IKEObject3d* objSave_ = new IKEObject3d();
	objSave_ = IKEObject3d::Create();
	objSave_->SetModel(modelSave);
	objSave_->SetRotation({ 0.0f,90.0f,0.0f });
	objSave_->SetScale({ 3.0f,3.0f,3.0f });
	objSave_->SetLightPower(20.0f);
	objSave.reset(objSave_);

	//�Z�[�u����UI
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
	//�G�t�F�N�g
	MarkEffect* markEffect_ = new MarkEffect();
	markEffect_->Initialize();
	markEffect.reset(markEffect_);
}
//�X�V
void Save::Update() {

	//�{�^���������ƃZ�[�u�ł���
	if (Collide() && m_SaveCount == 0 && player->GetHP() >= 1) {
		m_GameSave = true;
		m_SaveText = true;
	}
	//�e�N�X�`���̓���
	TexMove();
	//�Z�[�u���Ă��܂��Ƃł�
	SaveAnime();
	//�p�[�e�B�N��
	if (m_Alive) {
		BirthParticle();
	}
	objSave->SetPosition(m_Position);
	objSave->Update();

	markEffect->Update({ m_Position.x,m_Position.y + 5.0f,m_Position.z });
}
//�`��
const void Save::Draw() {

	IKEObject3d::PreDraw();
	if (m_Alive) {
		objSave->Draw();
	}

	IKESprite::PreDraw();
	if (m_SaveText) {
		SaveSprite[m_SaveCount]->Draw();
	}
	markEffect->Draw();
}

//�����蔻��
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
//�Z�[�u�|�C���g�̈ʒu
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
		m_Position = { 100.0f,-282.0f,10.0f };
	}

	objSave->SetPosition(m_Position);
}
//�e�N�X�`���̓���
void Save::TexMove() {
	//sin�g�ɂ���ď㉺�ɓ���
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);
	m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (m_Position.y + 7.0f);
	m_TexPosition.x = m_Position.x;
	m_TexPosition.z = m_Position.z;
}
//�A�j���[�V����
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

void Save::BirthParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,0.5f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,0.5f };
	float s_scale = 3.0f;
	float e_scale = 0.0f;

	ParticleEmitter::GetInstance()->FireEffect(50, { m_Position.x,m_Position.y + 2.0f,m_Position.z }, s_scale, e_scale, s_color, e_color);
}