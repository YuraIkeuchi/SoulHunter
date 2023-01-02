#include "BoundEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include "ParticleManager.h"
using namespace DirectX;

BoundEnemy::BoundEnemy() {
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
	m_Radius.x = 1.0f * 2.7f;
	//������
	m_Radius.y = 0.6f * 2.7f;
	m_HP = 4;
	m_fbxObject->Update(true, 1, m_AnimationStop);
	return true;
}
//�X�V
void BoundEnemy::Action() {
	m_OldPos = m_Position;

	//�}�b�v�`�b�v�Ƃ̓����蔻��
	if (block->EnemyMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump, m_AddPower, m_TouchWall, m_HP)) {
		m_Gravity = 0.02f;
		m_ParticleCount = 5.0f;
		//������
		m_Air = false;
	}

	//�s��
	Move();

	//�_���[�W���̓���
	DamageAct();
	//�e�̃��Z�b�g
	ResetBullet();
	//�p�[�e�B�N������
	BirthParticle();
	//�G�t�F�N�g�֌W
	ArgEffect();
	//���֌W
	ArgSoul();

	VanishEnemy();
	if (m_Alive && UpdateCollide()) {
		m_fbxObject->Update(true, 1, m_AnimationStop);
		PlayerCollide();
		Fbx_SetParam();
	}
	//�G�t�F�N�g�֌W
	for (EnemyEffect* enemyeffect : enemyeffects) {
		if (enemyeffect != nullptr) {
			enemyeffect->Update(m_Position, m_Effect, m_HitDir);
		}
	}
	ParticleUpdate();
}
//�`��
void BoundEnemy::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("Enemy");
ImGui::Text("m_Disolve : %f", m_AddPower);
ImGui::End();*/
	if (m_Alive && DrawCollide()) {
		Fbx_Draw(dxCommon);
	}
	//�G�t�F�N�g�֌W
	for (EnemyEffect* enemyeffect : enemyeffects) {
		if (enemyeffect != nullptr) {
			enemyeffect->Draw();
		}
	}
	particletex->Draw();
}
//�|�[�Y�J�����Ƃ��̓L�����������Ȃ�
void BoundEnemy::Pause() {
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