#include "FollowEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include <Easing.h>
using namespace DirectX;

FollowEnemy::FollowEnemy() {
	IKESprite::LoadTexture(27, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(27, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::ThornEnemy);
}
//������
bool FollowEnemy::Initialize() {
	m_Color = { 1.0f,0.0f,0.0f,1.0f };
	IKEObject3d* m_Object_ = new IKEObject3d();
	m_Object_ = IKEObject3d::Create();
	m_Object_->SetModel(m_Model);
	m_Position = { 97.0f,-100.0,0.0f };
	m_Object_->SetPosition(m_Position);
	m_Scale = { 1.7f,1.7f,1.7f };
	m_Object_->SetScale(m_Scale);
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_Object_->SetRotation(m_Rotation);
	m_Object_->SetLightEffect(false);
	m_Object.reset(m_Object_);
	//�G�̎��
	m_EnemyType = Thorn;
	return true;
	m_HP = 3;
	
}
//�X�V
void FollowEnemy::Action() {
	//X����
	m_Radius.x = 2.0f;
	//������
	m_Radius.y = 2.0f;
	m_OldPos = m_Position;
	if (m_Alive && UpdateCollide()) {
		if (m_HP >= 1) {
			FollowMove();
		}
		if (PlayerCollide()) {
			m_Follow = false;
			m_FollowTimer = 0;
		}
		Obj_SetParam();
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
	}
	else {
		m_Follow = false;
		m_FollowTimer = 0;
	}

	//�_���[�W�̃C���^�[�o��
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
			m_Frame = 0.0f;
			m_Rotation.x = m_Rotation.x - 360.0f;
		}
	}
	//�����蔻��
	block->FollowEnemyMapCollideCommon(m_Position, m_Radius, m_OldPos);
	//�G��������
	VanishFollowEnemy();
	//�p�[�e�B�N������
	BirthParticle();
	DeathBirthParticle();
	//�_���[�W������
	FollowDamageAct();
	//�G�t�F�N�g�֌W
	ArgEffect();
	//���֌W
	ArgSoul();
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
}
//�`��
void FollowEnemy::Draw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
		//�G�t�F�N�g�֌W
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}
	}
}
//�_���[�W���󂯂�(���̓G�͎󂯂Ȃ��@�e�����)
bool FollowEnemy::FollowCollision() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_Scale);
	OBB1.SetParam_Rot(m_Object->GetMatrot());
	OBB2.SetParam_Pos(player->GetSwordPosition());
	OBB2.SetParam_Scl(player->GetSwordScale());
	OBB2.SetParam_Rot(player->GetSwordMatrot());

	//OBB�ƌ����Ŕ�����
	if (player->GetRotation().y == 90.0f) {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x < m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = 20;
			m_EffectArgment = true;
			m_HP--;
			m_Effect = true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x > m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = 20;
			m_EffectArgment = true;
			m_HP--;
			m_Effect = true;
			return true;
		}
		else {
			return false;
		}
	}

	return true;
}
//�|�[�Y
void FollowEnemy::Pause() {
	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
	Obj_SetParam();
	m_Object->Update();
}
//�Ǐ]
void FollowEnemy::FollowMove() {
	m_TargetTimer++;
	XMFLOAT3 position{};
	position.x = (player->GetSwordPosition().x - m_Position.x);
	position.y = (player->GetSwordPosition().y - m_Position.y);
	m_FollowVel.x = sin(-atan2f(position.x, position.y)) * 0.15f;
	m_FollowVel.y = cos(-atan2f(position.x, position.y)) * 0.15f;
	m_Rotation.x = (atan2f(position.x, position.y) * (180.0f / XM_PI));

	//�U���܂ň��t���[������
	if (!m_Follow) {
		m_FollowTimer++;
		if (m_FollowTimer >= 30) {
			m_Follow = true;
		}
	}
	else {
		m_Position.x -= m_FollowVel.x;
		m_Position.y += m_FollowVel.y;
	}
}
//������
bool FollowEnemy::VanishFollowEnemy() {
	if (m_HP < 1 && m_AddPower <= 0.0f) {
		if (DeathTimer < 30 && !m_Disolve) {
			m_DeathParticleCount++;
			DeathTimer++;
		}
		else {
			m_Disolve = true;
			DeathTimer = 0;
		}
	}

	if (m_Disolve && m_Alive) {
		if (m_Addcolor.x <= 1.0f) {
			m_Addcolor.x += 0.025f;
			m_Addcolor.y += 0.025f;
			m_Addcolor.z += 0.025f;
		}
		else {
			m_Addcolor.x = 1.0f;
			m_Addcolor.y = 1.0f;
			m_Addcolor.z = 1.0f;
		}
		if (m_AddDisolve < 5.0f) {
			m_AddDisolve += 0.2f;
		}
		else {
			m_DeathParticleCount = 0;
			m_Soul = true;
			m_Alive = false;
		}
	}
	return true;
}
//�_���[�W���̓���
void FollowEnemy::FollowDamageAct() {
	if (FollowCollision()) {
		m_Distance.x = player->GetPosition().x - m_Position.x;
		m_Distance.y = player->GetPosition().y - m_Position.y;
		m_Rebound.x = (sin(atan2f(m_Distance.x, m_Distance.y)) * 2.0f) * -1.0f;
		m_Rebound.y = (cos(atan2f(m_Distance.x, m_Distance.y)) * 2.0f) * -1.0f;
		m_AfterRot.x = m_Rotation.x + 360.0f;
		m_Follow = false;
		m_FollowTimer = 0;
	}
	if (m_Damage) {
		m_Rebound = {
		Ease(In,Cubic,0.5f,m_Rebound.x,0.0f),
		Ease(In,Cubic,0.5f,m_Rebound.y,0.0f),
		};

		m_Position.x += m_Rebound.x;
		m_Position.y += m_Rebound.y;

		if (m_Frame < 1.0f) {
			m_Frame += 0.05f;
		}
		else {
			m_Frame = 1.0f;
		}
		m_Rotation.x = Ease(In, Cubic, m_Frame, m_Rotation.x, m_AfterRot.x);
	}
}
//���
void FollowEnemy::Finalize() {
}
//�}�b�v�̕`��
void FollowEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}
//ImGui
void FollowEnemy::ImGuiDraw() {
	ImGui::Begin("Follow");
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::End();
}