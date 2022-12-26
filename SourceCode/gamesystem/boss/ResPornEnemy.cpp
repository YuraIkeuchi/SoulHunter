#include "ResPornEnemy.h"
#include "imgui.h"
//初期化
void ResPornEnemy::Initialize() {
	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
}
//更新
void  ResPornEnemy::Update(InterBoss* boss) {
	//一定の時間立つと敵が出現する(パーティクルも出現する)
	if (boss->GetHP() > 0) {
		m_ResPornTimer++;
	}

	//ここで出現
	if (boss->GetHP() > 0) {
		if (m_ResPornTimer == 500) {
			m_ResPornType = rand() % 3;
			m_ResPornParticle = true;
			m_ResPornPos.x = boss->GetPosition().x;
			m_ResPornPos.y = -140.0f;
			m_ResPornPos.z = boss->GetPosition().z;
		}

		if (m_ResPornTimer == 650) {
			m_EnemyArgment = true;
			m_ResPornTimer = 0;
		}

		if (m_ResPornTimer >= 550) {
			m_ParticleCount = 1;
		}
		else {
			m_ParticleCount = 0;
		}
	}
	else {
		m_ParticleCount = 0;
	}

	particletex->SetStartColor({ 0.7f,0.3f,0.7f,1.0f });
	particletex->SetStartScale(0.5f);
	particletex->SetParticleBreak(true);
	particletex->SetAddScale(0.01f);
	particletex->Update(m_ResPornPos, m_ParticleCount, 1, 0);
}
//描画
const void ResPornEnemy::Draw() {
	ImGui::Begin("ResPorn");
	ImGui::Text("m_ResPornTimer::%d", m_ResPornTimer);
	ImGui::End();
	particletex->Draw();
}