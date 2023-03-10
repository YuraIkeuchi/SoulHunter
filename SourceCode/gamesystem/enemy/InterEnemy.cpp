#include "InterEnemy.h"
#include "Collision.h"
#include "ImageManager.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
#include "PlayerSword.h"
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
	int l_SetDamageTimer = 20;//TargetTimerのセット値
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_HitScale);
	OBB1.SetParam_Rot(m_fbxObject->GetMatrot());
	OBB2.SetParam_Pos(PlayerSword::GetInstance()->GetPosition());
	OBB2.SetParam_Scl(PlayerSword::GetInstance()->GetScale());
	OBB2.SetParam_Rot(PlayerSword::GetInstance()->GetSwordMatrot());
	
	//OBBと向きで判定取る
	if (player->GetRotation().y == 90.0f) {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x < m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = l_SetDamageTimer;
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
			m_DamageTimer = l_SetDamageTimer;
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
//プレイヤーがダメージ食らう
bool InterEnemy::PlayerCollide() {
	float l_HitRadius = 1.0f;//当たり判定
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	int Interval = player->GetInterVal();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_HitRadius, m_PlayerPos.x, m_PlayerPos.y, l_HitRadius) && (m_HP > 0) &&
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
	float l_LockRadius = 15.0f;//ロックオン判定
	XMFLOAT3 l_PlayerPos = player->GetPosition();
	//同じブロック上にいて距離が近かったらロックオン
	m_DistanceY = m_Position.y - l_PlayerPos.y;
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_LockRadius, l_PlayerPos.x, l_PlayerPos.y, l_LockRadius) && (m_HP > 0)
		&& (m_DistanceY <= 2.0f && m_DistanceY >= -2.0f) && (player->GetAddPower() == 0.0f)) {
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
	XMFLOAT4 s_color = { 0.8f,0.8f,0.8f,0.3f };
	XMFLOAT4 e_color = { 0.8f,0.8f,0.8f,0.3f };
	float s_scale = 1.0f;
	float e_scale = 0.0f;
	//足元
	if (m_FootParticleCount >= 3 && m_Alive) {
		for (int i = 0; i < 5; ++i) {
			ParticleEmitter::GetInstance()->HootEffect(30, { m_Position.x,(m_Position.y - 1.0f),m_Position.z }, s_scale, e_scale, s_color, e_color);
		}
		m_FootParticleCount = 0;
	}
}
//死んだ時のパーティクル
void InterEnemy::DeathBirthParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,1.0f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,1.0f };
	float s_scale = 2.0f;
	float e_scale = 0.0f;
	float l_velocity = 0.2f;
	if (m_DeathParticleCount > 1) {
		for (int i = 0; i < 3; ++i) {
			ParticleEmitter::GetInstance()->DeathEffect(50, { m_Position.x,(m_Position.y - 1.0f),m_Position.z }, s_scale, e_scale, s_color, e_color, l_velocity);
		}
		m_DeathParticleCount = 0;
	}
}
//更新を範囲内に入った時のみ
bool InterEnemy::UpdateCollide() {
	float l_UpdateRadius = 23.0f;//更新判定
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_UpdateRadius, m_PlayerPos.x, m_PlayerPos.y, l_UpdateRadius)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//描画を範囲内に入った時のみ
bool InterEnemy::DrawCollide() {
	float l_DrawRadius = 21.0f;//描画判定
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_DrawRadius, m_PlayerPos.x, m_PlayerPos.y, l_DrawRadius)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//死んだときに消える
bool InterEnemy::VanishEnemy() {
	float l_AddColor = 0.025f;//加わる色
	float l_TargetDisolve = 2.0f;//規定のディゾルブ値
	int l_TargetDeathTimer = 30;//DeathTimerの最大値
	if (m_HP < 1 && m_AddPower <= m_ResetFew) {
		if (m_DeathTimer < l_TargetDeathTimer && !m_Disolve) {
			m_DeathParticleCount++;
			m_DeathTimer++;
		}
		else {
			m_Disolve = true;
			m_DeathTimer = m_ResetNumber;
		}
	}

	if (m_Disolve && m_Alive) {
		m_Addcolor.x += l_AddColor;
		m_Addcolor.y += l_AddColor;
		m_Addcolor.z += l_AddColor;
		m_Addcolor.x = min(m_Addcolor.x, m_ColorMax);
		m_Addcolor.y = min(m_Addcolor.y, m_ColorMax);
		m_Addcolor.z = min(m_Addcolor.z, m_ColorMax);
		if (m_AddDisolve < l_TargetDisolve) {
			m_AddDisolve += l_AddColor;
		}
		else {
			m_DeathParticleCount = m_ResetNumber;
			m_Soul = true;
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
		m_TargetTimer = m_ResetNumber;
		m_Speed = m_ResetFew;
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
	if (m_HitDir == HitRight) {
		if (m_BoundPower.x < 0.0f) {
			m_BoundPower.x += l_Decrease;
		}
		else {
			m_BoundPower.x = 0.0f;
		}
	}
	else if (m_HitDir == HitLeft) {
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
		if (m_DamageTimer < m_ResetNumber) {
			m_Damage = false;
			m_DamageTimer = m_ResetNumber;
		}
	}
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
//魂の生成
void InterEnemy::ArgSoul() {
	
}
//ミニマップの座標
void InterEnemy::MapEnemy() {
	XMFLOAT2 l_LimitPos = { 4.5f,-2.4f };
	//敵の座標
	m_EnemyPosition.x = m_Position.x * l_LimitPos.x;
	m_EnemyPosition.y = m_Position.y * l_LimitPos.y;

	MiniEnemySprite->SetPosition(m_EnemyPosition);
}
