#include "InterBoss.h"
#include"Collision.h"
#include "ParticleManager.h"
//�X�V
void InterBoss::Update() {
	//�����蔻��
	collidePlayer();
	collideBoss();
	BirthParticle();
	//�{�X�̍s��
	if (!pause->GetIsPause()) {
		if (!m_Movie) {
			if (m_HP > 0) {
				Spec();
			}
			else {
				Dead();
			}
		}
	}
	//HP���}�C�i�X�ɂ��Ȃ�
	if (m_HP <= 0) {
		m_HP = 0;
		m_DeathTimer++;
		//�p�[�e�B�N������������
		if (m_Scale.x > 0.0f) {
			m_ParticleCount++;
		}
		else {
			m_ParticleCount = 0;
		}
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
	//�{�X�̖��O�̍X�V
	bossname->Update();
	//�p�[�e�B�N��
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_ParticleCount, 1, 2);
}
//�`��
void InterBoss::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("Boss");
	ImGui::Text("HP : %f", m_HP);
	ImGui::End();*/
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
	particletex->Draw();
	//�{�X�̖��O
	bossname->Draw();
	//�{�X���Ƃ̃I�u�W�F�N�g�̕`��
	specialDraw(dxCommon);
}
//�v���C���[���_���[�W��H�炤
bool InterBoss::collidePlayer() {
	XMFLOAT3 l_PlayerPos = player->GetPosition();
	int playerhp = player->GetHP();
	int l_Interval = player->GetInterVal();
	if (Collision::SphereCollision(m_Position.x, m_Position.y,m_Position.z,m_HitRadius, l_PlayerPos.x, l_PlayerPos.y,l_PlayerPos.z, m_HitRadius) && l_Interval == 0 && m_HP > 0) {
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
	//m_PlayerPos = player->GetPosition();
	if (m_FoodParticleCount >= 5 && m_Alive) {

		for (int i = 0; i < m_ParticleNum; ++i) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = m_Position.z;
			//const float rnd_sca = 0.1f;
			//float sca{};
			//sca = (float)rand() / RAND_MAX*rnd_sca;
			ParticleManager::GetInstance()->Add(30, { m_ParticlePos.x + vel.x,(m_ParticlePos.y - 1.0f) + vel.y,m_ParticlePos.z }, vel, XMFLOAT3(), 1.2f, 0.6f);
		}
		m_FoodParticleCount = 0;
	}
}