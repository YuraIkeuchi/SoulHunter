#include "InterBoss.h"
#include"Collision.h"
//更新
void InterBoss::Update() {
	//当たり判定
	collidePlayer();
	collideBoss();
	BulletCollision();
	SpecialCollide();
	//ボスの行動
	if (!pause->GetIsPause()) {
		if (!m_Movie) {
			if (m_HP > 0) {
				Spec();
			}
			else {
				End();
			}
		}
		else {
			App();
		}
	}
	//HPをマイナスにしない
	if (m_HP <= 0) {
		m_HP = 0;
		m_DeathTimer++;
		//パーティクルが発生する
		if (m_Scale.x > 0.0f) {
			m_ParticleCount++;
		}
		else {
			m_ParticleCount = 0;
		}
	}


	//技を一回しかくらわないように
	if (!playerbullet->GetAlive()) {
		m_BulletHit = false;
	}
	//必殺技があたったかどうか
	if (!player->GetSpecialEffect()) {
		m_SpecialHit = false;
	}
	//生きてる時しか更新しない
	if (m_Alive) {
		enemyobj->Update();
	}
	//エフェクトの生成
	ArgEffect();
	//エフェクトの更新
	for (BossEffect* bosseffect : bosseffects) {
		if (bosseffect != nullptr) {
			bosseffect->Update(m_pos, m_Effect, m_HitDir);
		}
	}
	//ボスの名前の更新
	bossname->Update();
	//パーティクル
	particletex->SetStartColor({ 1.0f,0.0f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_pos, m_ParticleCount, 1, 2);
}
//描画
void InterBoss::Draw() {
	/*ImGui::Begin("Boss");
	ImGui::Text("Timer : %d", m_MovieTimer);
	ImGui::Text("Scale.x : %f", m_Scale.x);
	ImGui::End();*/
	//ボスの描画
	IKEObject3d::PreDraw();
	if (m_Alive) {
		enemyobj->Draw();
	}

	//エフェクトの描画
	for (BossEffect* bosseffect : bosseffects) {
		if (bosseffect != nullptr) {
			bosseffect->Draw();
		}
	}
	//パーティクルの描画
	particletex->Draw();
	//ボスの名前
	bossname->Draw();
	//ボスごとのオブジェクトの描画
	specialDraw();
}
//プレイヤーがダメージを食らう
bool InterBoss::collidePlayer() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	int playerhp = player->GetHP();
	int Interval = player->GetInterVal();
	if (Collision::CircleCollision(m_pos.x, m_pos.y,m_HitRadius, m_PlayerPos.x, m_PlayerPos.y, m_HitRadius) && Interval == 0 && m_HP > 0) {
		player->PlayerHit(m_pos);
		return true;
	}
	else {
		return false;
	}
	return true;
}
//ボスがダメージ食らう(通常攻撃)
bool InterBoss::collideBoss() {
	XMFLOAT3 AttackPos = player->GetAttackPos();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, 2.5f, AttackPos.x, AttackPos.y, 2.5f) && (m_HP > 0) && (player->GetAttackTimer() == 2)) {
		m_HP--;
		m_Effect = true;
		m_EffectArgment = true;
		//どっちにあたったか
		if (AttackPos.x > m_pos.x) {
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
//敵がダメージ食らう(弾)
bool InterBoss::BulletCollision() {
	XMFLOAT3 bulletpos = playerbullet->GetPosition();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, 1.5f, bulletpos.x, bulletpos.y, 1.5f) && (m_HP > 0)
		&& (playerbullet->GetAlive()) && (!m_BulletHit)) {
		m_HP -= 2;
		m_Effect = true;
		m_EffectArgment = true;
		m_BulletHit = true;
		//どっちにあたったか
		if (bulletpos.x > m_pos.x) {
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

//敵がダメージ食らう(必殺技)
bool InterBoss::SpecialCollide() {
	bool l_SpecialAlive = playereffect->GetSpecialAlive();
	XMFLOAT3 l_SpecialPos = playereffect->GetSpecialPosition();
	float l_SpecialRadius = playereffect->GetSpecialRadius();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, l_SpecialRadius, l_SpecialPos.x, l_SpecialPos.y, l_SpecialRadius)
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
//エフェクトの生成
void InterBoss::ArgEffect() {
	if (m_EffectArgment) {
		BossEffect* newEffect;
		newEffect = new BossEffect();
		newEffect->Initialize();
		bosseffects.push_back(newEffect);
		m_EffectArgment = false;
	}
}