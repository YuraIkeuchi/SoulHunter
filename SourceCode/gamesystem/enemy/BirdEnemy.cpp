#include "BirdEnemy.h"
#include "ModelManager.h"
#include "VariableCommon.h"
#include "Collision.h"
using namespace DirectX;

BirdEnemy::BirdEnemy() {
	IKESprite::LoadTexture(30, L"Resources/2d/sceneback/MiniMapEnemy.png");
	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(30, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BirdEnemy);
}
//初期化
bool BirdEnemy::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_ChangeColor = true;
	//FBX
	IKEFBXObject3d* m_fbxObject_ = new IKEFBXObject3d();
	m_fbxObject_->Initialize();
	m_fbxObject_->SetModel(m_fbxModel);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Rotation = { 0.0f,180.0f,0.0f };
	m_Scale = { 0.01f,0.01f,0.01f };
	m_fbxObject_->SetScale(m_Scale);
	m_fbxObject_->SetPosition(m_Position);
	m_fbxObject_->SetRotation(m_Rotation);
	m_fbxObject_->LoadAnimation();
	m_fbxObject_->PlayAnimation(0);
	m_fbxObject.reset(m_fbxObject_);
	m_Jump = true;
	//敵の種類
	m_EnemyType = Bird;
	//マップチップとの当たり判定に使う大きさ
	//X方向
	m_Radius.x = 3.8f;
	//下方向
	m_Radius.y = 1.6f;
	m_HP = 5;
	m_fbxObject->Update(true, m_AnimeTimer, m_AnimationStop);
	return true;
}
//更新
void BirdEnemy::Action() {
	XMFLOAT3 l_ResetRot = { 0.0f,180.0f,0.0f };
	m_OldPos = m_Position;
	if (m_Alive && UpdateCollide()) {
		//当たり判定軽量化
		PlayerCollide();
		m_fbxObject->Update(true, m_AnimeTimer, m_AnimationStop);
		Fbx_SetParam();
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Update(m_Position, m_Effect);
			}
		}
		//エフェクト関係
		for (BirdEnemyEffect* birdenemyeffect : birdenemyeffects) {
			if (birdenemyeffect != nullptr) {
				birdenemyeffect->Update(m_Position);
			}
		}
	}
	//マップにあたったとき回転が戻る
	if (block->BirdEnemyMapCollideCommon(m_Position, m_Radius, m_BirdTouchWall, m_OldPos, m_Attack)) {
		m_Rotation = l_ResetRot;
	}

	//動き
	Move();
	//ダメージ時の動き
	DamageAct();
	//死んだときの挙動
	DeathMove();
	//パーティクル生成
	BirthParticle();
	DeathBirthParticle();
	//ロックオン
	BirdLockOn();
	//エフェクト関係
	ArgEffect();
	//魂関係
	ArgSoul();
	//消える
	VanishEnemy();
	//エフェクト発生
	BirdArgment();
	//ミニマップに表示させる
	MapEnemy();
}
//描画
void BirdEnemy::Draw(DirectXCommon* dxCommon) {
	if (m_Alive && DrawCollide()) {
		Fbx_Draw(dxCommon);
		//エフェクト関係
		for (EnemyEffect* enemyeffect : enemyeffects) {
			if (enemyeffect != nullptr) {
				enemyeffect->Draw();
			}
		}

		//エフェクト関係
		for (BirdEnemyEffect* birdenemyeffect : birdenemyeffects) {
			if (birdenemyeffect != nullptr) {
				birdenemyeffect->Draw();
			}
		}
	}
}
//ポーズ開いたときはキャラが動かない
void BirdEnemy::Pause() {
	//ミニマップに表示させる
	MapEnemy();
	Fbx_SetParam();
	m_fbxObject->Update(true, m_AnimeTimer, m_AnimationStop);
}
//プレイヤーをロックオンする
bool BirdEnemy::BirdLockOn() {
	float l_LockRadius = 15.0f;
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	//同じブロック上にいて距離が近かったらロックオン
	m_DistanceY = m_Position.y - m_PlayerPos.y;
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_LockRadius, m_PlayerPos.x, m_PlayerPos.y, l_LockRadius) && (m_HP > 0)) {
		m_Lock = true;
		return true;
	}
	else {
		m_Lock = false;
		return false;
	}
	return true;
}
//移動
void BirdEnemy::Move() {
	float l_AddPosY = 0.02f;//座標に加わる力
	float l_AttackSpeed = 0.5f;//攻撃速度
	//範囲内に入って一定時間立つと突進する
	if (!m_Attack) {
		if (m_Lock) {
			m_LockTimer++;
		}
		else {
			m_LockTimer = m_ResetNumber;
		}

		if (m_LockTimer >= UpTimer) {
			if (m_BirdTouchWall == Down) {
				m_Position.y += l_AddPosY;
			}
			else if (m_BirdTouchWall == Up) {
				m_Position.y -= l_AddPosY;
			}
			else {
				m_Position.y += l_AddPosY;
			}
		}
		if (m_LockTimer == AttackTimer) {
			double l_sb, l_sbx, l_sby;
			if (!m_Attack) {
				l_sbx = player->GetPosition().x - m_Position.x;
				l_sby = player->GetPosition().y - m_Position.y;
				l_sb = sqrt(l_sbx * l_sbx + l_sby * l_sby);
				m_speedX = l_sbx / l_sb * l_AttackSpeed;
				m_speedY = l_sby / l_sb * l_AttackSpeed;
				if (player->GetPosition().x > m_Position.x) {
					m_Rotation.y = 90.0f;
				}
				else {
					m_Rotation.y = 270.0f;
				}
				m_Attack = true;
				m_LockTimer = m_ResetNumber;
			}
		}
	}
	else {
		//プレイヤーにスピード加算
		m_Position.x += (float)m_speedX;
		m_Position.y += (float)m_speedY;
	}
}
//死んだとき跳ねる
void BirdEnemy::DeathMove() {
	if (m_DeathMotion && m_Jump) {
		m_AddPower = 0.5f;
		m_Jump = false;
		m_DeathMotion = false;
		m_BirdTouchWall = No;
	}

	if (m_BirdTouchWall != Down) {
		if (m_HP == 0 && m_AddPower >= -3.0f) {
			m_Rotation.y += 20.0f;
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
		}
	}
	else {
		m_AddPower = m_ResetFew;
	}
}
//解放
void BirdEnemy::Finalize() {
	//enemyeffects.pop_back();
}
//マップの描画
void BirdEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	if (m_EnemyPosition.x != m_ResetFew && m_EnemyPosition.y != m_ResetFew && m_Alive) {
		MiniEnemySprite->Draw();
	}
}
//羽エフェクト生成
void BirdEnemy::BirdArgment() {
	if (m_BirdEffectArgment) {
		BirdEnemyEffect* newBirdEnemyEffect;
		newBirdEnemyEffect = new BirdEnemyEffect();
		newBirdEnemyEffect->Initialize();
		birdenemyeffects.push_back(newBirdEnemyEffect);
		m_BirdEffectArgment = false;
	}
}
//Imguiの描画
void BirdEnemy::ImGuiDraw() {
	if (m_Alive) {
		ImGui::Begin("Bird");
		ImGui::Text("X:%f", m_Position.x);
		ImGui::End();
	}
}