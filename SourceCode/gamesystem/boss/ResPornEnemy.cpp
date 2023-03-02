#include "ResPornEnemy.h"
#include "imgui.h"
#include <random>
//初期化
void ResPornEnemy::Initialize() {
}
//更新
void  ResPornEnemy::Update(InterBoss* boss) {
	XMFLOAT3 l_BirthPos = { boss->GetPosition().x,-140.0f,0.0f };
	//一定の時間立つと敵が出現する(パーティクルも出現する)
	if (boss->GetHP() > 0) {
		m_ResPornTimer++;
	}

	//ここで出現
	if (boss->GetHP() > 0) {
		if (m_ResPornTimer == EnemySet) {
			//乱数指定
			mt19937 mt{ std::random_device{}() };
			uniform_int_distribution<int> l_resdist(0, 2);
			m_ResPornType = l_resdist(mt);
			m_ResPornParticle = true;
			m_ResPornPos.x = l_BirthPos.x;
			m_ResPornPos.y = l_BirthPos.y;
			m_ResPornPos.z = l_BirthPos.z;
		}

		if (m_ResPornTimer == EnemyBirth) {
			m_EnemyArgment = true;
			m_ResPornTimer = 0;
		}

		if (m_ResPornTimer >= ParticleBirth) {
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
//描画
const void ResPornEnemy::Draw() {
}