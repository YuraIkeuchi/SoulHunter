#include "ChestEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "Input.h"
#include <Easing.h>
#include "VariableCommon.h"
#include "PlayerSword.h"
using namespace DirectX;

ChestEnemy::ChestEnemy() {
	IKESprite::LoadTexture(28, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(28, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::CloseChest);

	//宝箱に近づいたときのテクスチャ
	IKETexture* chestTex_ = IKETexture::Create(ImageManager::ChestTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	chestTex_->TextureCreate();
	chestTex_->SetRotation({ 0,0,0 });
	chestTex_->SetScale({ 0.6f,0.3f,0.3f });
	chestTex.reset(chestTex_);


	Shake* shake_ = new Shake();
	shake.reset(shake_);
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
	m_EnemyType = ChestType;
	m_HP = 1;
	return true;


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
	
	//敵が消える
	VanishChestEnemy();
	//パーティクル生成
	BirthParticle();
	DeathBirthParticle();
	//ダメージ時の動き
	DamageChestAct();
	//エフェクト関係
	ArgEffect();
	//魂関係
	ArgSoul();
	//ミニマップに表示させる
	MapEnemy();
	//テクスチャ動く
	TexMove();
	//テクスチャ当たり判定
	TexCollide();
	//プレイヤーとの当たり判定
	PlayerCollide();
	//宝箱の当たり判定(敵が食らう側)
	ChestCollision();
	//動き
	ChestMove();
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
	if (m_Hit && !m_Attack) {
		chestTex->Draw();
	}
}
//ダメージを受ける
bool ChestEnemy::ChestCollision() {
	OBB1.SetParam_Pos(m_Position);
	OBB1.SetParam_Scl(m_Scale);
	OBB1.SetParam_Rot(m_Object->GetMatrot());
	OBB2.SetParam_Pos(PlayerSword::GetInstance()->GetPosition());
	OBB2.SetParam_Scl(PlayerSword::GetInstance()->GetScale());
	OBB2.SetParam_Rot(PlayerSword::GetInstance()->GetSwordMatrot());

	if (m_MoveNumber == IntervalChest && m_HP > 0) {
		//OBBと向きで判定取る
		if (player->GetRotation().y == 90.0f) {
			if (Collision::OBBCollision(OBB1, OBB2) && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x < m_Position.x)) {
				m_HitDir = HitLeft;
				m_BoundPower.x = 0.6f;
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
			if (Collision::OBBCollision(OBB1, OBB2) && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x > m_Position.x)) {
				m_HitDir = HitRight;
				m_BoundPower.x = -0.6f;
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
//宝箱の攻撃
void ChestEnemy::ChestMove() {
	Input* input = Input::GetInstance();
	if ((input->TriggerButton(input->Button_A)) && (m_Hit) && (!m_Attack)) {
		m_Attack = true;
		m_Frame = 0.0f;
		shake->SetShakeStart(true);
		m_MoveNumber = ShakeChest;
		m_AfterColor = { 1.0f,0.0f,0.0f,1.0f };
	}

	if (m_Attack && m_HP != 0) {
		if (m_MoveNumber == ShakeChest) {			//シェイクする
			shake->ShakePos(m_ShakePos.x, 11, 5, 50, 70);
			shake->ShakePos(m_ShakePos.y, 11, 5, 50, 70);
			if (!shake->GetShakeStart()) {
				m_ShakePos = { 0.0f,0.0f,0.0f };
				m_MoveNumber = SetChest;
				m_Frame = 0.0f;
				m_AfterPos = { m_StartPos.x,m_StartPos.y + 8.0f,0.0f };
			}
			else {
				m_Position.x += m_ShakePos.x;
				m_Position.y += m_ShakePos.y;
			}
		}
		else if (m_MoveNumber == SetChest) {			//上に行く
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.1f;
			}
			else {
				m_Frame = 1.0f;
				m_IntervalTimer++;
				if (m_IntervalTimer > 30) {
					m_AfterPos = { m_Position.x,m_StartPos.y,m_Position.z };
					m_Frame = 0.0f;
					m_IntervalTimer = 0;
					m_MoveNumber = AttackChest;
				}
			}
		}
		else if (m_MoveNumber == AttackChest) {			//攻撃
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.1f;
			}
			else {
				m_Frame = 0.0f;
				m_MoveNumber = IntervalChest;
			}
		}
		else if (m_MoveNumber == IntervalChest) {			//攻撃後の硬直
			m_IntervalTimer++;
			if (m_IntervalTimer >= 50) {
				m_IntervalTimer = 0;
				m_MoveNumber = ReturnChest;
				m_AfterPos = m_StartPos;
				m_AfterColor = { 1.0f,1.0f,1.0f,1.0f };
			}
		}
		else {			//戻る
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.1f;
			}
			else {
				m_Frame = 0.0f;
				m_Attack = false;
			}
		}

		m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_AfterPos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_AfterPos.z)
		};

		m_Color = {
Ease(In,Cubic,m_Frame,m_Color.x,m_AfterColor.x),
Ease(In,Cubic,m_Frame,m_Color.y,m_AfterColor.y),
	Ease(In,Cubic,m_Frame,m_Color.z,m_AfterColor.z),
		Ease(In,Cubic,m_Frame,m_Color.w,m_AfterColor.w),
		};
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
	if (Collision::CircleCollision(l_plaPos.x, l_plaPos.y, 2.0f,m_Position.x,m_Position.y,2.0f) && (m_HP != 0.0f) &&
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
//プレイヤーとの当たり判定
bool ChestEnemy::PlayerCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	int Interval = player->GetInterVal();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 2.0f, m_PlayerPos.x, m_PlayerPos.y, 2.0f) && (m_HP > 0) &&
		Interval == 0 && player->GetHP() >= 1 && (m_MoveNumber == AttackChest || m_MoveNumber == IntervalChest) ) {
		player->PlayerHit(m_Position);
		return true;
	}
	else {
		return false;
	}

	return true;
}
//ダメージ受けた時の動き
void ChestEnemy::DamageChestAct() {
	float l_Decrease = 0.05f;
	//跳ね返り処理
	if (m_HP == 0) {
		m_DeathMotion = true;
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
	}
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
	if (m_Alive) {
		ImGui::Begin("Chest");
		ImGui::Text("HP:%d", m_HP);
		ImGui::Text("BoundX:%f", m_BoundPower.x);
		ImGui::End();
	}
}