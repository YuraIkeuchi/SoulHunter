#include "ResPornEnemy.h"
#include "imgui.h"
//������
void ResPornEnemy::Initialize() {
}
//�X�V
void  ResPornEnemy::Update(InterBoss* boss) {
	//���̎��ԗ��ƓG���o������(�p�[�e�B�N�����o������)
	if (boss->GetHP() > 0) {
		m_ResPornTimer++;
	}

	//�����ŏo��
	if (boss->GetHP() > 0) {
		if (m_ResPornTimer == 1200) {
			m_ResPornType = rand() % 3;
			m_ResPornParticle = true;
			m_ResPornPos.x = boss->GetPosition().x;
			m_ResPornPos.y = -140.0f;
			m_ResPornPos.z = 0.0f;
		}

		if (m_ResPornTimer == 1350) {
			m_EnemyArgment = true;
			m_ResPornTimer = 0;
		}

		if (m_ResPornTimer >= 1250) {
			m_ParticleCount = 1;
		}
		else {
			m_ParticleCount = 0;
		}
	}
	else {
		m_ParticleCount = 0;
	}
}
//�`��
const void ResPornEnemy::Draw() {
}