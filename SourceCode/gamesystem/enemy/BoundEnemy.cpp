#include "BoundEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include "ParticleManager.h"
using namespace DirectX;

BoundEnemy::BoundEnemy() {
	IKESprite::LoadTexture(26, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(26, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BoundEnemy);
	ParticleInit();
}
//������
bool BoundEnemy::Initialize() {
	m_ChangeColor = true;
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_Scale = { 0.03f, 0.03f, 0.03f };
	//FBX
	IKEFBXObject3d* m_fbxObject_ = new IKEFBXObject3d();
	m_fbxObject_->Initialize();
	m_fbxObject_->SetModel(m_fbxModel);
	m_Position = { 110.0f,-90.0,0.0f };
	m_fbxObject_->SetScale(m_Scale);
	m_fbxObject_->SetPosition(m_Position);
	m_fbxObject_->LoadAnimation();
	m_fbxObject_->PlayAnimation(0);
	m_fbxObject.reset(m_fbxObject_);
	m_EnemyType = Wing;
	//X����
	m_Radius.x = 1.4f * 2.7f;
	//������
	m_Radius.y = 0.6f * 2.7f;
	m_HP = 4;
	m_fbxObject->Update(true, 1, m_AnimationStop);
	return true;
}
//�X�V
void BoundEnemy::Action() {
	m_OldPos = m_Position;

	if (m_Alive && UpdateCollide()) {
		m_fbxObject->Update(true, 1, m_AnimationStop);
		PlayerCollide();
		Fbx_SetParam();
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
	}

	//�}�b�v�`�b�v�Ƃ̓����蔻��
	if (block->EnemyMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump, m_AddPower, m_TouchWall, m_HP)) {
		m_Gravity = 0.02f;
		m_HootParticleCount = 5;
		//������
		m_Air = false;
	}

	//�s��
	Move();

	//�_���[�W���̓���
	DamageAct();
	//�p�[�e�B�N������
	BirthParticle();
	//�G�t�F�N�g�֌W
	ArgEffect();
	//���֌W
	ArgSoul();

	VanishEnemy();
	ParticleUpdate();
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
}
//�`��
void BoundEnemy::Draw(DirectXCommon* dxCommon) {
	if (m_Alive && DrawCollide()) {
		Fbx_Draw(dxCommon);
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}
	}
	particletex->Draw();
}
//�|�[�Y�J�����Ƃ��̓L�����������Ȃ�
void BoundEnemy::Pause() {
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
	Fbx_SetParam();
	//m_fbxObject->StopAnimation();
	m_fbxObject->Update(false, 1, m_AnimationStop);
}
//�s��
void BoundEnemy::Move() {
	if (m_Jump && m_HP > 0) {
		m_AddPower = 0.5f;
		m_Jump = false;
	}

	//���R����
	if (!m_Jump) {
		//���~�x���}�C�i�X
		//�_�b�V�����̂Ƃ��͏d�͂��Ȃ�
		m_AddPower -= m_Gravity;
		m_Position.y += m_AddPower;
	}

	//HP������Ƃ��͓���
	if (m_HP > 0) {
		if (m_TouchWall == LeftTouch) {
			m_Rotation.y = 0.0f;
			m_Speed = 0.1f;
		}
		else if (m_TouchWall == RightTouch) {
			m_Rotation.y = 180.0f;
			m_Speed = -0.1f;
		}
	}
	else {
		m_Speed = 0.0f;
	}

	m_Position.x += m_Speed;
}
//���
void BoundEnemy::Finalize() {
	//enemyeffects.pop_back();
}

void BoundEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}