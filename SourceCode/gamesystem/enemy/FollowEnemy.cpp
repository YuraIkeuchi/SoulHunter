#include "FollowEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include <Easing.h>
using namespace DirectX;

FollowEnemy::FollowEnemy() {
	IKESprite::LoadTexture(26, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(26, { 0.0f,0.0f });
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
}
//�X�V
void FollowEnemy::Action() {
	
	RotMove();
	if (m_Alive && UpdateCollide()) {
		ThornCollision();
		PlayerCollide();
		Obj_SetParam();
	}
	//�p�[�e�B�N������
	BirthParticle();
	//�_���[�W�̃C���^�[�o��
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}

	//�~�j�}�b�v�ɕ\��������
	MapEnemy();
}
//�`��
void FollowEnemy::Draw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
	}
}
//�_���[�W���󂯂�(���̓G�͎󂯂Ȃ��@�e�����)
bool FollowEnemy::ThornCollision() {
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
			m_DamageTimer = 50;
			player->PlayerThornHit(m_Position);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x > m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = 50;
			player->PlayerThornHit(m_Position);
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
	//m_Position.y = (sin(m_Angle2) * 8.0f + 8.0f) + (m_ThornSetPos);
	Obj_SetParam();
	m_Object->Update();
}
//��]�̓���
void FollowEnemy::RotMove() {
	switch (m_RotNumber) {
	case Stop:
		m_Interval++;
		if (m_Interval > 10) {
			m_Interval = 0;
			m_RotNumber = Right;
			m_AfterRot.x = 90.0f;
			break;
		}


	case Right:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Left;
			m_AfterRot.x = -90.0f;
			m_Frame = 0.0f;
			break;
		}

	case Left:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Turn;
			m_AfterRot.x = 720.0f;
			m_Frame = 0.0f;
			break;
		}

	case Turn:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Stop;
			m_Rotation.x = 0.0f;
			m_Frame = 0.0f;
			break;
		}
	}

	m_Rotation.x = Ease(In, Cubic, m_Frame, m_Rotation.x, m_AfterRot.x);
}
//���
void FollowEnemy::Finalize() {
	//enemyeffects.pop_back();
}

void FollowEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}

void FollowEnemy::ImGuiDraw() {
	ImGui::Begin("Follow");
	ImGui::Text("X:%f", m_Position.x);
	ImGui::Text("Y:%f", m_Position.y);
	ImGui::Text("Z:%f", m_Position.z);
	ImGui::End();
}