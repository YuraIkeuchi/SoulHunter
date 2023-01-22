#include "InterEnemy.h"
#include "Collision.h"
#include "ImageManager.h"
#include "VariableCommon.h"
bool InterEnemy::Initialize() {

	return true;
}
//�X�V
void InterEnemy::Update() {
	Action();//�G�̍s��
}
//�`��
void InterEnemy::Draw(DirectXCommon* dxCommon) {

}

//�G���_���[�W�H�炤
bool InterEnemy::Collision() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_Scale);
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
//�v���C���[���_���[�W�H�炤
bool InterEnemy::PlayerCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	int Interval = player->GetInterVal();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 1.0f, m_PlayerPos.x, m_PlayerPos.y, 1.0f) && (m_HP > 0) &&
		Interval == 0 && player->GetHP() >= 1) {
		//hitstop->SetStopTimer(10);
		player->PlayerHit(m_Position);
		return true;
	}
	else {
		return false;
	}

	return true;
}
//�v���C���[�����b�N�I������
bool InterEnemy::LockOn() {
	XMFLOAT3 l_PlayerPos = player->GetPosition();
	//�����u���b�N��ɂ��ċ������߂������烍�b�N�I��
	m_DistanceY = m_Position.y - l_PlayerPos.y;
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 15.0f, l_PlayerPos.x, l_PlayerPos.y, 15.0f) && (m_HP > 0)
		&& (m_DistanceY <= 2.0f && m_DistanceY >= -2.0f)) {

		m_Lock = true;
		return true;
	}
	else {
		m_Lock = false;
		return false;
	}
	return true;
}
//�p�[�e�B�N�����o�Ă���
void InterEnemy::BirthParticle() {
	//����
	if (m_HootParticleCount >= 5 && m_Alive) {

		for (int i = 0; i < 3; ++i) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = m_Position.z;
			//const float rnd_sca = 0.1f;
			//float sca{};
			//sca = (float)rand() / RAND_MAX*rnd_sca;
			ParticleManager::GetInstance()->Add(30, { m_Position.x + vel.x,(m_Position.y - 1.0f) + vel.y,m_Position.z }, vel, XMFLOAT3(), 1.2f, 0.6f);
		}
		m_HootParticleCount = 0;
	}
}
//�X�V��͈͓��ɓ��������̂�
bool InterEnemy::UpdateCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 20.0f, m_PlayerPos.x, m_PlayerPos.y, 20.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//�`���͈͓��ɓ��������̂�
bool InterEnemy::DrawCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 18.0f, m_PlayerPos.x, m_PlayerPos.y, 18.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//���񂾂Ƃ��ɏ�����
bool InterEnemy::VanishEnemy() {
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
		if (m_AddDisolve < 2.0f) {
			m_AddDisolve += 0.025f;
		}
		else {
			m_DeathParticleCount = 0;
			m_Soul = true;
			m_SoulArgment = true;
			m_Alive = false;
		}
	}
	return true;
}
//�_���[�W���󂯂��Ƃ��̓���
void InterEnemy::DamageAct() {
	float l_Decrease = 0.0f;
	//�v���C���[�Ƃ��������Ƃ��ːi�����߂�
	if (Collision()) {
		m_TargetTimer = 0;
		m_Speed = 0.0f;
		m_Effect = true;
		if (m_EnemyType == Bird) {
			m_BirdEffectArgment = true;
		}
		//�G�����˕Ԃ�
		if (player->GetPosition().x > m_Position.x) {
			m_HitDir = HitRight;
			if (m_EnemyType == Wing) {
				m_BoundPower.x = -1.0f;
			}
			else {
				m_BoundPower.x = -0.8f;
				if (m_EnemyType == Normal){
					m_Rotation = { 0.0f,90.0f,0.0f };
				}
			}
		}
		else {
			m_HitDir = HitLeft;
			if (m_EnemyType == Wing) {
				m_BoundPower.x = 1.0f;
			}
			else {
				m_BoundPower.x = 0.8f;
				if (m_EnemyType == Normal) {
					m_Rotation = { 0.0f,270.0f,0.0f };
				}
			}
		}
		if (m_HP == 0) {
			m_DeathMotion = true;
		}
	}

	//���˕Ԃ菈��
	if (m_EnemyType == Normal || m_EnemyType == Bird) {
		if (m_HP > 0) {
			l_Decrease = 0.05f;
		}
		else {
			l_Decrease = 0.01f;
		}
	}
	else {
		l_Decrease = 0.05f;
	}
	if (m_HitDir == 0) {
		if (m_BoundPower.x < 0.0f) {
			m_BoundPower.x += l_Decrease;
		}
		else {
			m_BoundPower.x = 0.0f;
		}
	}
	else if (m_HitDir == 1) {
		if (m_BoundPower.x > 0.0f) {
			m_BoundPower.x -= l_Decrease;
		}
		else {
			m_BoundPower.x = 0.0f;
		}
	}


	m_Position.x += m_BoundPower.x;

	//�_���[�W�̃C���^�[�o��
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}
}

//�p�[�e�B�N���̏�����
void InterEnemy::ParticleInit() {
	ParticleTex* particletex_;
	particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
}
//�p�[�e�B�N���̍X�V
void InterEnemy::ParticleUpdate() {
	BirthParticle();
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_DeathParticleCount, 1, EndPart);
}
//�G�t�F�N�g�̐���
void InterEnemy::ArgEffect() {
	if (m_EffectArgment) {
		EnemyEffect* newEffect;
		newEffect = new EnemyEffect();
		newEffect->Initialize();
		enemyeffects.push_back(newEffect);
		m_EffectArgment = false;
	}
}

//���̐���
void InterEnemy::ArgSoul() {
	
}

void InterEnemy::MapEnemy() {
	//�v���C���[�̍��W
	m_EnemyPosition.x = m_Position.x * 4.5f;
	m_EnemyPosition.y = m_Position.y * -2.4f;

	MiniEnemySprite->SetPosition(m_EnemyPosition);
}
