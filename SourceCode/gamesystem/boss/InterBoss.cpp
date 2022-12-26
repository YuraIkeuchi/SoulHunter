#include "InterBoss.h"
#include"Collision.h"
//�X�V
void InterBoss::Update() {
	//�����蔻��
	collidePlayer();
	collideBoss();
	BulletCollision();
	SpecialCollide();
	//�{�X�̍s��
	if (!pause->GetIsPause()) {
		if (!m_Movie) {
			if (m_HP > 0) {
				Spec();
			}
			else {
				End();
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


	//�Z����񂵂������Ȃ��悤��
	if (!playerbullet->GetAlive()) {
		m_BulletHit = false;
	}
	//�K�E�Z�������������ǂ���
	if (!player->GetSpecialEffect()) {
		m_SpecialHit = false;
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
	particletex->SetStartColor({ 1.0f,0.0f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_ParticleCount, 1, 2);
}
//�`��
void InterBoss::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("Boss");
	ImGui::Text("Timer : %d", m_MovieTimer);
	ImGui::Text("Scale.x : %f", m_Scale.x);
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
	specialDraw();
}
//�v���C���[���_���[�W��H�炤
bool InterBoss::collidePlayer() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	int playerhp = player->GetHP();
	int Interval = player->GetInterVal();
	if (Collision::CircleCollision(m_Position.x, m_Position.y,m_HitRadius, m_PlayerPos.x, m_PlayerPos.y, m_HitRadius) && Interval == 0 && m_HP > 0) {
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
	XMFLOAT3 AttackPos = player->GetAttackPos();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 2.5f, AttackPos.x, AttackPos.y, 2.5f) && (m_HP > 0) && (player->GetAttackTimer() == 2)) {
		m_HP--;
		m_Effect = true;
		m_EffectArgment = true;
		//�ǂ����ɂ���������
		if (AttackPos.x > m_Position.x) {
			m_HitDir = HitRight;
		}
		else {
			m_HitDir = HitLeft;
		}
		return true;
	}
	else {
		return false;
	}
}
//�G���_���[�W�H�炤(�e)
bool InterBoss::BulletCollision() {
	XMFLOAT3 bulletpos = playerbullet->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 1.5f, bulletpos.x, bulletpos.y, 1.5f) && (m_HP > 0)
		&& (playerbullet->GetAlive()) && (!m_BulletHit)) {
		m_HP -= 2;
		m_Effect = true;
		m_EffectArgment = true;
		m_BulletHit = true;
		//�ǂ����ɂ���������
		if (bulletpos.x > m_Position.x) {
			m_HitDir = HitRight;
		}
		else {
			m_HitDir = HitLeft;
		}
		return true;
	}
	else {
		return false;
	}

	return true;
}

//�G���_���[�W�H�炤(�K�E�Z)
bool InterBoss::SpecialCollide() {
	bool l_SpecialAlive = playereffect->GetSpecialAlive();
	XMFLOAT3 l_SpecialPos = playereffect->GetSpecialPosition();
	float l_SpecialRadius = playereffect->GetSpecialRadius();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_SpecialRadius, l_SpecialPos.x, l_SpecialPos.y, l_SpecialRadius)
		&& (m_HP > 0) && (l_SpecialAlive) && (!m_SpecialHit)) {
		m_HP -= 5;
		m_EffectArgment = true;
		m_SpecialHit = true;
		m_Effect = true;
		return true;
	}
	else {
		return false;
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

void InterBoss::AppUpdate() {
	App();
}

void InterBoss::AppDraw(DirectXCommon* dxCommon) {
	//�{�X�̕`��
	IKEObject3d::PreDraw();
	if (m_Alive) {
		Fbx_Draw(dxCommon);
	}
	//�{�X���Ƃ̃I�u�W�F�N�g�̕`��
	specialDrawApp();
}