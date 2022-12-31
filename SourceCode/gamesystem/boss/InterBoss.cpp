#include "InterBoss.h"
#include"Collision.h"
//更新
void InterBoss::Update() {
	//当たり判定
	collidePlayer();
	collideBoss();
	BulletCollision();
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


	//技を一回しかくらわないように
	if (!playerbullet->GetAlive()) {
		m_BulletHit = false;
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
	ImGui::Text("Timer : %d", m_MovieTimer);
	ImGui::Text("Scale.x : %f", m_Scale.x);
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
//ボスがダメージ食らう(通常攻撃)
bool InterBoss::collideBoss() {

	XMFLOAT3 AttackPos = player->GetAttackPos();

	//外積当たり判定
	Sphere sphere;
	sphere.center = { m_Position.x,m_Position.y,m_Position.z };
	sphere.radius = 1;

	Box box;
	box.center = { AttackPos.x + 1.0f,AttackPos.y,AttackPos.z };
	box.scale = { 6.5f,5.5f,8.5f };

	if (Collision::CheckSphere2Box(sphere, box) && (m_HP > 0) && (player->GetAttackTimer() == 2)) {
		m_HP--;
		m_Effect = true;
		m_EffectArgment = true;
		//どっちにあたったか
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

	return true;
}
//敵がダメージ食らう(弾)
bool InterBoss::BulletCollision() {
	XMFLOAT3 bulletpos = playerbullet->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 1.5f, bulletpos.x, bulletpos.y, 1.5f) && (m_HP > 0)
		&& (playerbullet->GetAlive()) && (!m_BulletHit)) {
		m_HP -= 2;
		m_Effect = true;
		m_EffectArgment = true;
		m_BulletHit = true;
		//どっちにあたったか
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