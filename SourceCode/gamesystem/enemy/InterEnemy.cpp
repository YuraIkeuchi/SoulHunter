#include "InterEnemy.h"
#include "Collision.h"
#include "ParticleManager.h"
bool InterEnemy::Initialize() {
	return true;
}
//更新
void InterEnemy::Update() {
	Action();//敵の行動
}
//描画
void InterEnemy::Draw(DirectXCommon* dxCommon) {

}

//敵がダメージ食らう
bool InterEnemy::Collision() {

	XMFLOAT3 AttackPos = player->GetAttackPos();
	
	//外積当たり判定
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
//プレイヤーがダメージ食らう
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
//プレイヤーをロックオンする
bool InterEnemy::LockOn() {
	XMFLOAT3 l_PlayerPos = player->GetPosition();
	//同じブロック上にいて距離が近かったらロックオン
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
//パーティクルが出てくる
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
//更新を範囲内に入った時のみ
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
//描画を範囲内に入った時のみ
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
//死んだときに消える
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
//ダメージを受けたときの動き
void InterEnemy::DamageAct() {
	float l_Decrease = 0.0f;
	//プレイヤーとあたったとき突進を辞める
	if (Collision()) {
		m_TargetTimer = 0;
		m_Speed = 0.0f;
		m_Effect = true;
		if (m_EnemyType == Bird) {
			m_BirdEffectArgment = true;
		}
		//敵が跳ね返る
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

	//跳ね返り処理
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

	//ダメージのインターバル
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}
}

//パーティクルの初期化
void InterEnemy::ParticleInit() {
	//パーティクル
	/*ParticleObj* particleobj_;
	particleobj_ = new ParticleObj();
	particleobj_->Initialize();
	particleobj.reset(particleobj_);*/

	ParticleTex* particletex_;
	particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);
}
//パーティクルの更新
void InterEnemy::ParticleUpdate() {
	//particleobj->SetStartColor({ 1.0f,0.0f,0.0f,1.0f });
	//particleobj->SetParticleBreak(true);
	//particleobj->Update(m_Position, m_ParticleObjCount, 1, 2);

	particletex->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	particletex->SetParticleBreak(true);
	particletex->Update(m_Position, m_ParticleObjCount, 1, 2);
}
//エフェクトの生成
void InterEnemy::ArgEffect() {
	if (m_EffectArgment) {
		EnemyEffect* newEffect;
		newEffect = new EnemyEffect();
		newEffect->Initialize();
		enemyeffects.push_back(newEffect);
		m_EffectArgment = false;
	}
}
//羽エフェクト生成
void InterEnemy::BirdArgment() {
	if (m_BirdEffectArgment) {
		BirdEnemyEffect* newBirdEnemyEffect;
		newBirdEnemyEffect = new BirdEnemyEffect();
		newBirdEnemyEffect->Initialize();
		birdenemyeffects.push_back(newBirdEnemyEffect);
		m_BirdEffectArgment = false;
	}
}
//魂の生成
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
