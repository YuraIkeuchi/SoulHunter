#include "Enemy.h"
#include "ModelManager.h"
#include "VariableCommon.h"
#include "ParticleManager.h"
#include "Easing.h"
using namespace DirectX;

Enemy::Enemy() {
	IKESprite::LoadTexture(26, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(26, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::NormalEnemy);
	ParticleInit();
}
//初期化
bool Enemy::Initialize() {
	m_ChangeColor = true;
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_Scale = { 0.025f, 0.025f, 0.025f };
	//FBX
	IKEFBXObject3d* m_fbxObject_ = new IKEFBXObject3d();
	m_fbxObject_->Initialize();
	m_fbxObject_->SetModel(m_fbxModel);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_fbxObject_->SetScale(m_Scale);
	m_fbxObject_->SetPosition(m_Position);
	m_fbxObject_->SetRotation(m_Rotation);
	m_fbxObject_->LoadAnimation();
	m_fbxObject_->PlayAnimation(0);
	m_fbxObject.reset(m_fbxObject_);
	//敵の種類
	m_EnemyType = Normal;
	//X方向
	m_Radius.x = 1.4f * 2.7f;
	//下方向
	m_Radius.y = 0.6f * 2.7f;
	m_HP = 3;
	return true;
}
//更新
void Enemy::Action() {
	m_OldPos = m_Position;

	if (m_Alive && UpdateCollide()) {
	
		m_fbxObject->Update(true, 1, m_AnimationStop);
		//当たり判定
		PlayerCollide();
		Fbx_SetParam();
	
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
	}

	//自然落下
	if (!m_Jump) {
		m_Air = true;
		//下降度をマイナス
		//ダッシュ中のときは重力がない
		m_AddPower -= m_Gravity;
		m_Position.y += m_AddPower;
	}
	//マップチップとの当たり判定
	if (block->EnemyMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump, m_AddPower, m_TouchWall, m_HP)) {
		m_OnGround = true;
		m_Gravity = 0.02f;
		//初期化
		m_AddPower = 0;
		m_Air = false;
	}

	VanishEnemy();

	//エネミーの左右移動
	if (m_OnGround && m_HP >= 1) {
		//プレイヤーをロックオンしていない
		if (!m_Lock) {
			Move();//普通の移動
			m_TargetTimer = 0;
		}
		//プレイヤーをロックオンしている
		else {
			AttackExtra();//予備動作
			Tackle();//突進してくる
		}


	}

	//ダメージ時の動き
	DamageAct();
	//死んだときの挙動
	DeathMove();
	//パーティクル生成
	BirthParticle();
	//ロックオン
	LockOn();
	//エフェクト関係
	ArgEffect();
	//魂関係
	ArgSoul();

	ParticleUpdate();
	//ミニマップに表示させる
	MapEnemy();
}
//描画
void Enemy::Draw(DirectXCommon* dxCommon) {
	if (m_Alive && DrawCollide()) {
		Fbx_Draw(dxCommon);
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}
	}
	particletex->Draw();
}
//ポーズ開いたときはキャラが動かない
void Enemy::Pause() {
	//ミニマップに表示させる
	MapEnemy();
	Fbx_SetParam();
	m_fbxObject->StopAnimation();
	m_fbxObject->Update(true, 1, m_AnimationStop);
}
//動き
void Enemy::Move() {
	m_TargetTimer = 0;
	m_Rotation.x = 0.0f;
	m_Rotation.z = 0.0f;
	if (m_TouchWall == LeftTouch) {
		m_Rotation.y = 90.0f;
		m_Speed = 0.1f;
	}
	else if (m_TouchWall == RightTouch) {
		m_Rotation.y = 270.0f;
		m_Speed = -0.1f;
	}


	if (m_SetMove && m_HP > 0) {
		//m_Rotation.z -= 2.0f;
		m_Position.x += m_Speed;
		m_MoveTimer++;

		if (m_MoveTimer == 100) {
			m_MoveTimer = 0;
			m_SetMove = false;
			m_fbxObject->StopAnimation();
		}
	}

	else {
		m_NotMoveTimer++;
		if (m_NotMoveTimer == 50) {
			m_NotMoveTimer = 0;
			m_SetMove = true;
			m_fbxObject->PlayAnimation(0);
		}
	}
}
//攻撃前の予備動作
void Enemy::AttackExtra() {
	//ロックオンした瞬間に飛ぶ
	if (m_TargetTimer == 1 && !m_AttackExtra) {
		m_AddPower = 0.3f;
		m_Jump = false;
		m_AttackExtra = true;
		//回転向き
		if (m_Position.x > player->GetPosition().x) {
			if (m_Rotation.y == 90.0f) {
				m_Rotation.z = 360.0f;
				m_AfterRot.z = 270.0f;
			}
			else if (m_Rotation.y == 270.0f) {
				m_Rotation.z = 0.0f;
				m_AfterRot.z = 90.0f;
			}
		}
		else{
			if (m_Rotation.y == 90.0f) {
				m_Rotation.z = 360.0f;
				m_AfterRot.z = 270.0f;
			}
			else if (m_Rotation.y == 270.0f) {
				m_Rotation.z = 0.0f;
				m_AfterRot.z = 90.0f;
			}
		}
	}

	//イージングで回転指定
	if (m_AttackExtra) {
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.1f;
		}
		else {
			m_Frame = 0.0f;
			m_AttackExtra = false;
		}


		m_Rotation.z = Ease(In, Cubic, m_Frame, m_Rotation.z, m_AfterRot.z);
	}
}
//攻撃
void Enemy::Tackle() {
	m_fbxObject->StopAnimation();
	if (m_BoundPower.x == 0.0f) {
		m_TargetTimer++;
	}
	
	//突進までのインターバルは動かない
	if (m_TargetTimer <= 29) {
		m_Speed = 0.0f;
	}
	//プレイヤーの位置によって突進する方向が変わる
	if (m_TargetTimer == 30) {
		if (player->GetPosition().x > m_Position.x) {
			m_TouchWall = LeftTouch;
			m_Speed = 0.15f;
		}
		else {
			m_TouchWall = RightTouch;
			m_Speed = -0.15f;
		}
	}
	else if (m_TargetTimer == 200) {
		m_TargetTimer = 0;
	}
	m_HootParticleCount++;
	//回転方向が変わる
	if (m_Speed == 0.15f) {
		m_Rotation.x += 10.0f;
	}
	else if(m_Speed == -0.15f) {
		m_Rotation.x -= 10.0f;
	}
	m_Position.x += m_Speed;
	m_SetMove = false;
	m_MoveTimer = 0;
	m_NotMoveTimer = 0;
}
//死んだときの動き
void Enemy::DeathMove() {
	//死んだとき跳ねるような挙動をする
	if (m_DeathMotion && m_Jump) {
		m_AddPower = 0.5f;
		m_Jump = false;
		m_DeathMotion = false;
		m_fbxObject->StopAnimation();
		//m_Rotation = { 0.0f,180.0f,0.0f };
	}

	if (m_HP == 0) {
		if (m_AddPower > 0.0f) {
			m_Rotation.z -= 30.0f;
		}
		else {
			m_Rotation.z = 0.0f;
		}
	}
}
//解放
void Enemy::Finalize() {
	//enemyeffects.pop_back();
}
//ミニマップの描画
void Enemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}