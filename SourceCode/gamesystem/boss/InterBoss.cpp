#include "InterBoss.h"
#include"Collision.h"
#include "ParticleManager.h"
//更新
void InterBoss::Update() {
	//当たり判定
	collidePlayer();
	collideBoss();
	BirthParticle();
	//ボスの行動
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


	//ダメージのインターバル
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}

	//エフェクトの生成
	ArgEffect();
	//エフェクトの更新
	for (BossEffect* bosseffect : bosseffects) {
		if (bosseffect != nullptr) {
			bosseffect->Update(m_Position, m_Effect, m_HitDir);
		}
	}
	//ボスの名前の更新
	bossname->Update();
	//パーティクル
	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_ParticleCount, 1, 2);
}
//描画
void InterBoss::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("Boss");
	ImGui::Text("HP : %f", m_HP);
	ImGui::End();*/
	//ボスの描画
	IKEObject3d::PreDraw();
	if (m_Alive) {
		Fbx_Draw(dxCommon);
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
	specialDraw(dxCommon);
}
//プレイヤーがダメージを食らう
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
//ボスがダメージ食らう(通常攻撃)
bool InterBoss::collideBoss() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_OBBScale);
	OBB1.SetParam_Rot(m_fbxObject->GetMatrot());
	OBB2.SetParam_Pos(player->GetSwordPosition());
	OBB2.SetParam_Scl(player->GetSwordScale());
	OBB2.SetParam_Rot(player->GetSwordMatrot());

	//OBBと向きで判定取る
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
//ボス登場シーン更新
void InterBoss::AppUpdate() {
	App();
}
//ボス登場シーン描画
void InterBoss::AppDraw(DirectXCommon* dxCommon) {
	//ボスの描画
	IKEObject3d::PreDraw();
	if (m_Alive) {
		Fbx_Draw(dxCommon);
	}
	//ボスごとのオブジェクトの描画
	specialDrawApp();
}
//ボス登場シーン更新
void InterBoss::EndUpdate() {
	End();
}
//ボス登場シーン描画
void InterBoss::EndDraw(DirectXCommon* dxCommon) {
	//ボスの描画
	IKEObject3d::PreDraw();
	if (m_Addcolor.x != 1.0f) {
		Fbx_Draw(dxCommon);
	}
	//ボスごとのオブジェクトの描画
	specialDrawEnd();
}
//パーティクルが出てくる
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