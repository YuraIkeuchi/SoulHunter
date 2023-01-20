#include "BoundEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include "ParticleManager.h"
using namespace DirectX;

BoundEnemy::BoundEnemy() {
	IKESprite::LoadTexture(26, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(26, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BoundEnemy);
	ParticleInit();
}
//初期化
bool BoundEnemy::Initialize() {
	m_ChangeColor = true;
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_Scale = { 0.03f, 0.03f, 0.03f };
	//FBX
	IKEFBXObject3d* m_fbxObject_ = new IKEFBXObject3d();
	m_fbxObject_->Initialize();
	m_fbxObject_->SetModel(m_fbxModel);
	m_Position = { 110.0f,-90.0,0.0f };
	m_fbxObject_->SetScale(m_Scale);
	m_fbxObject_->SetPosition(m_Position);
	m_fbxObject_->LoadAnimation();
	m_fbxObject_->PlayAnimation(0);
	m_fbxObject.reset(m_fbxObject_);
	m_EnemyType = Wing;
	//X方向
	m_Radius.x = 1.4f * 2.7f;
	//下方向
	m_Radius.y = 0.6f * 2.7f;
	m_HP = 4;
	m_fbxObject->Update(true, 1, m_AnimationStop);
	return true;
}
//更新
void BoundEnemy::Action() {
	m_OldPos = m_Position;

	if (m_Alive && UpdateCollide()) {
		m_fbxObject->Update(true, 1, m_AnimationStop);
		PlayerCollide();
		Fbx_SetParam();
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
	}

	//マップチップとの当たり判定
	if (block->EnemyMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump, m_AddPower, m_TouchWall, m_HP)) {
		m_Gravity = 0.02f;
		m_HootParticleCount = 5;
		//初期化
		m_Air = false;
	}

	//行動
	Move();

	//ダメージ時の動き
	DamageAct();
	//パーティクル生成
	BirthParticle();
	//エフェクト関係
	ArgEffect();
	//魂関係
	ArgSoul();

	VanishEnemy();
	ParticleUpdate();
	//ミニマップに表示させる
	MapEnemy();
}
//描画
void BoundEnemy::Draw(DirectXCommon* dxCommon) {
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
void BoundEnemy::Pause() {
	//ミニマップに表示させる
	MapEnemy();
	Fbx_SetParam();
	//m_fbxObject->StopAnimation();
	m_fbxObject->Update(false, 1, m_AnimationStop);
}
//行動
void BoundEnemy::Move() {
	if (m_Jump && m_HP > 0) {
		m_AddPower = 0.5f;
		m_Jump = false;
	}

	//自然落下
	if (!m_Jump) {
		//下降度をマイナス
		//ダッシュ中のときは重力がない
		m_AddPower -= m_Gravity;
		m_Position.y += m_AddPower;
	}

	//HPがあるときは動く
	if (m_HP > 0) {
		if (m_TouchWall == LeftTouch) {
			m_Rotation.y = 0.0f;
			m_Speed = 0.1f;
		}
		else if (m_TouchWall == RightTouch) {
			m_Rotation.y = 180.0f;
			m_Speed = -0.1f;
		}
	}
	else {
		m_Speed = 0.0f;
	}

	m_Position.x += m_Speed;
}
//解放
void BoundEnemy::Finalize() {
	//enemyeffects.pop_back();
}

void BoundEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != 0.0f && m_EnemyPosition.y != 0.0f && m_Alive) {
		MiniEnemySprite->Draw();
	}
}