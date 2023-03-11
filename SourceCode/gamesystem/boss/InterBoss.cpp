#include "InterBoss.h"
#include"Collision.h"
#include "ParticleEmitter.h"
#include "VariableCommon.h"
#include "PlayerSword.h"
//�X�V
void InterBoss::Update() {
	//�����蔻��
	collidePlayer();
	collideBoss();
	BirthParticle();
	DeathParticle();
	//�{�X�̍s��
	if (!m_Movie) {
		if (m_HP > 0) {
			Spec();
		}
		else {
			Dead();
		}
	}
	
	//HP���}�C�i�X�ɂ��Ȃ�
	if (m_HP <= 0) {
		m_HP = 0;
		m_DeathTimer++;
		m_DeathParticleCount++;
	}

	//�_���[�W�̃C���^�[�o��
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}

	//�G�t�F�N�g�̐���
	ArgEffect();
	//�G�t�F�N�g�̍X�V
	for (BossEffect* bosseffect : bosseffects) {
		if (bosseffect != nullptr) {
			bosseffect->Update(m_Position, m_Effect, m_HitDir);
		}
	}
}
//�`��
void InterBoss::Draw(DirectXCommon* dxCommon) {
	//�{�X�̕`��
	IKEObject3d::PreDraw();
	if (m_Alive) {
		Fbx_Draw(dxCommon);
	}

	//�G�t�F�N�g�̕`��
	for (BossEffect* bosseffect : bosseffects) {
		if (bosseffect != nullptr) {
			bosseffect->Draw();
		}
	}
	//�p�[�e�B�N���̕`��
	//�{�X���Ƃ̃I�u�W�F�N�g�̕`��
	specialDraw(dxCommon);
}
//�v���C���[���_���[�W��H�炤
bool InterBoss::collidePlayer() {
	XMFLOAT3 l_PlayerPos = player->GetPosition();
	int playerhp = player->GetHP();
	int l_Interval = player->GetInterVal();
	//�O�ϓ����蔻��
	Sphere sphere;
	sphere.center = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	sphere.radius = 1;

	Box box;
	box.center = { m_Position.x,m_Position.y,m_Position.z };
	box.scale = { m_HitRadius.x,m_HitRadius.y,m_HitRadius.z };

	if (Collision::CheckSphere2Box(sphere, box) && l_Interval == 0 && m_HP > 0 && player->GetHP() >= 1) {
		player->PlayerHit(m_Position);
		return true;
	}
	else {
		return false;
	}

	return true;
}
//�{�X���_���[�W�H�炤(�ʏ�U��)
bool InterBoss::collideBoss() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_OBBScale);
	OBB1.SetParam_Rot(m_fbxObject->GetMatrot());
	OBB2.SetParam_Pos(PlayerSword::GetInstance()->GetPosition());
	OBB2.SetParam_Scl(PlayerSword::GetInstance()->GetScale());
	OBB2.SetParam_Rot(PlayerSword::GetInstance()->GetSwordMatrot());

	//OBB�ƌ����Ŕ�����
	if (player->GetRotation().y == 90.0f) {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x < m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = 10;
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
			m_DamageTimer = 10;
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
//�G�t�F�N�g�̐���
void InterBoss::ArgEffect() {
	if (m_EffectArgment) {
		BossEffect* newEffect;
		newEffect = new BossEffect();
		newEffect->Initialize();
		bosseffects.push_back(newEffect);
		m_EffectArgment = false;
	}
}
//�{�X�o��V�[���X�V
void InterBoss::AppUpdate() {
	App();
}
//�{�X�o��V�[���`��
void InterBoss::AppDraw(DirectXCommon* dxCommon) {
	//�{�X�̕`��
	IKEObject3d::PreDraw();
	if (m_Alive) {
		Fbx_Draw(dxCommon);
	}
	//�{�X���Ƃ̃I�u�W�F�N�g�̕`��
	specialDrawApp();
}
//�{�X�o��V�[���X�V
void InterBoss::EndUpdate() {
	End();
}
//�{�X�o��V�[���`��
void InterBoss::EndDraw(DirectXCommon* dxCommon) {
	//�{�X�̕`��
	IKEObject3d::PreDraw();
	if (m_Addcolor.x != 1.0f) {
		Fbx_Draw(dxCommon);
	}
	//�{�X���Ƃ̃I�u�W�F�N�g�̕`��
	specialDrawEnd();
}
//�p�[�e�B�N�����o�Ă���
void InterBoss::BirthParticle() {
	XMFLOAT4 s_color = { 0.8f,0.8f,0.8f,0.3f };
	XMFLOAT4 e_color = { 0.8f,0.8f,0.8f,0.3f };
	float s_scale = 1.0f;
	float e_scale = 0.0f;
	//����
	if (m_FootParticleCount >= 3 && m_Alive) {
		for (int i = 0; i < 5; ++i) {
			ParticleEmitter::GetInstance()->HootEffect(30, { m_Position.x,(m_Position.y - 1.0f),m_Position.z }, s_scale, e_scale, s_color, e_color);
		}
		m_FootParticleCount = 0;
	}
}
//���񂾎��̃p�[�e�B�N��
void InterBoss::DeathParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,1.0f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,1.0f };
	float s_scale = 2.0f;
	float e_scale = 4.0f;
	float l_velocity = 0.1f;
	if (m_DeathParticleCount > 1) {
		for (int i = 0; i < 3; ++i) {
			ParticleEmitter::GetInstance()->DeathEffect(50, { m_Position.x,(m_Position.y - 1.0f),m_Position.z }, s_scale, e_scale, s_color, e_color, l_velocity);
		}
		m_DeathParticleCount = 0;
	}
}