#include "ChestEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include <Easing.h>
using namespace DirectX;

ChestEnemy::ChestEnemy() {
	IKESprite::LoadTexture(27, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(27, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::CloseChest);

	//宝箱に近づいたときのテクスチャ
	IKETexture* chestTex_ = IKETexture::Create(ImageManager::ChestTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	chestTex_->TextureCreate();
	chestTex_->SetRotation({ 0,0,0 });
	chestTex_->SetScale({ 0.6f,0.3f,0.3f });
	chestTex.reset(chestTex_);
}
//初期化
bool ChestEnemy::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* m_Object_ = new IKEObject3d();
	m_Object_ = IKEObject3d::Create();
	m_Object_->SetModel(m_Model);
	m_Position = { 97.0f,-100.0,0.0f };
	m_Object_->SetPosition(m_Position);
	m_Scale = { 4.0f,4.0f,4.0f };
	m_Object_->SetScale(m_Scale);
	m_Rotation = { 0.0f,180.0f,0.0f };
	m_Object_->SetRotation(m_Rotation);
	m_Object_->SetLightEffect(false);
	m_Object.reset(m_Object_);
	//敵の種類
	m_EnemyType = Thorn;
	return true;
	m_HP = 3;

}
//更新
void ChestEnemy::Action() {
	//X方向
	m_Radius.x = 2.0f;
	//下方向
	m_Radius.y = 2.0f;
	m_OldPos = m_Position;
	if (m_Alive && UpdateCollide()) {
		Obj_SetParam();
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
	}
	else {
		m_Follow = false;
		m_FollowTimer = 0;
	}

	//ダメージのインターバル
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
			m_Frame = 0.0f;
			m_Rotation.x = m_Rotation.x - 360.0f;
		}
	}


	////自然落下
	//if (!m_Jump) {
	//	m_Air = true;
	//	//下降度をマイナス
	//	//ダッシュ中のときは重力がない
	//	m_AddPower -= m_Gravity;
	//	m_Position.y += m_AddPower;
	//}
	////マップチップとの当たり判定
	//if (block->EnemyMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump, m_AddPower, m_TouchWall, m_HP)) {
	//	m_OnGround = true;
	//	m_Gravity = 0.02f;
	//	//初期化
	//	m_AddPower = 0;
	//	m_Air = false;
	//}

	//敵が消える
	VanishChestEnemy();
	//パーティクル生成
	BirthParticle();
	DeathBirthParticle();
	//エフェクト関係
	ArgEffect();
	//魂関係
	ArgSoul();
	//ミニマップに表示させる
	MapEnemy();
	//テクスチャ当たり判定
	TexCollide();
	//テクスチャ動く
	TexMove();
}
//描画
void ChestEnemy::Draw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}
	}

	//テキスト
	IKETexture::PreDraw(1);
	if (m_Hit) {
		chestTex->Draw();
	}
}
//ダメージを受ける(この敵は受けない　弾かれる)
bool ChestEnemy::FollowCollision() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_Scale);
	OBB1.SetParam_Rot(m_Object->GetMatrot());
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
//ポーズ
void ChestEnemy::Pause() {
	//ミニマップに表示させる
	MapEnemy();
	Obj_SetParam();
	m_Object->Update();
}
//追従
void ChestEnemy::FollowMove() {
	m_TargetTimer++;
	XMFLOAT3 position{};
	position.x = (player->GetSwordPosition().x - m_Position.x);
	position.y = (player->GetSwordPosition().y - m_Position.y);
	m_FollowVel.x = sin(-atan2f(position.x, position.y)) * 0.15f;
	m_FollowVel.y = cos(-atan2f(position.x, position.y)) * 0.15f;
	m_Rotation.x = (atan2f(position.x, position.y) * (180.0f / XM_PI));

	//攻撃まで一定フレームある
	if (!m_Follow) {
		m_FollowTimer++;
		if (m_FollowTimer >= 30) {
			m_Follow = true;
		}
	}
	else {
		m_Position.x -= m_FollowVel.x;
		m_Position.y += m_FollowVel.y;
	}
}
//消える
bool ChestEnemy::VanishChestEnemy() {
	if (m_HP < 1 && m_AddPower <= 0.0f) {
		if (DeathTimer < 30 && !m_Disolve) {
			m_DeathParticleCount++;
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
		if (m_AddDisolve < 5.0f) {
			m_AddDisolve += 0.2f;
		}
		else {
			m_DeathParticleCount = 0;
			m_Soul = true;
			m_Alive = false;
		}
	}
	return true;
}

//テキストが動く(sin波)
void ChestEnemy::TexMove() {
	//sin波によって上下に動く
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);

		if (m_Hit) {
			m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (m_Position.y + 7.0f);
			m_TexPosition.x = m_Position.x;
			m_TexPosition.z = m_Position.z;
		}

	chestTex->SetPosition(m_TexPosition);
	chestTex->Update();
}

//当たり判定
bool ChestEnemy::TexCollide() {
	XMFLOAT3 l_plaPos = player->GetPosition();
	if (Collision::CircleCollision(l_plaPos.x, l_plaPos.y, 3.0f,m_Position.x,m_Position.y,3.0f) && (m_HP != 0.0f) &&
		player->GetAddPower() == 0.0f) {
		m_Hit = true;
		player->SetCollideChest(true);
	}
	else {
		m_Hit = false;
		player->SetCollideChest(false);
	}
	return true;
}
//解放
void ChestEnemy::Finalize() {
}
//マップの描画
void ChestEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}
//ImGui
void ChestEnemy::ImGuiDraw() {
	ImGui::Begin("Chest");
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::End();
}