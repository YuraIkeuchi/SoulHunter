#include "InterEnemy.h"
#include "Collision.h"
#include "ParticleManager.h"
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

	XMFLOAT3 AttackPos = player->GetAttackPos();
	
	//�O�ϓ����蔻��
	Sphere sphere;
	sphere.center = { m_Position.x,m_Position.y,m_Position.z };
	sphere.radius = 1;

	Box box;
	box.center = { AttackPos.x + 1.0f,AttackPos.y,AttackPos.z };
	box.scale = { 6.5f,5.5f,8.5f };

	if (Collision::CheckSphere2Box(sphere, box) && (m_HP > 0) && (player->GetAttackTimer() == 5)) {
		m_Damage = true;
		m_DamageTimer = 50;
		m_EffectArgment = true;
		m_HP--;
		m_Effect = true;
		return true;
	}
	else {
		return false;
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
	//m_PlayerPos = player->GetPosition();
	if (m_ParticleCount >= 5.0f && m_Alive) {

		for (int i = 0; i < m_ParticleNum; ++i) {
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
		m_ParticleCount = 0.0f;
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
			m_ParticleObjCount++;
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
			m_ParticleObjCount = 0;
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
	//�p�[�e�B�N��
	/*ParticleObj* particleobj_;
	particleobj_ = new ParticleObj();
	particleobj_->Initialize();
	particleobj.reset(particleobj_);*/

	ParticleTex* particletex_;
	particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
}
//�p�[�e�B�N���̍X�V
void InterEnemy::ParticleUpdate() {
	//particleobj->SetStartColor({ 1.0f,0.0f,0.0f,1.0f });
	//particleobj->SetParticleBreak(true);
	//particleobj->Update(m_Position, m_ParticleObjCount, 1, 2);

	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_ParticleObjCount, 1, 2);
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
//�H�G�t�F�N�g����
void InterEnemy::BirdArgment() {
	if (m_BirdEffectArgment) {
		BirdEnemyEffect* newBirdEnemyEffect;
		newBirdEnemyEffect = new BirdEnemyEffect();
		newBirdEnemyEffect->Initialize();
		birdenemyeffects.push_back(newBirdEnemyEffect);
		m_BirdEffectArgment = false;
	}
}
//���̐���
void InterEnemy::ArgSoul() {
	//Block* block_;
	if (m_SoulArgment) {
		//m_SoulCount++;
		//if (m_SoulCount <= 5) {
		//	PlayerSoul* newplayersoul;
		//	newplayersoul = new PlayerSoul();
		//	newplayersoul->Initialize();
		//	newplayersoul->SetBlock(block.get());
		//	newplayersoul->SetPlayer(player.get());
		//	//newplayersoul->SetPlayer(player);
		//	//newplayersoul->SetBlock(block);
		//	playersouls.push_back(newplayersoul);
		//}
		//else {
		//	m_SoulArgment = false;
		//	m_SoulCount = 0;
		//}
	
	}
}
