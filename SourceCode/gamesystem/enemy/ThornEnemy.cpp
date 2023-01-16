#include "ThornEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include <Easing.h>
using namespace DirectX;

ThornEnemy::ThornEnemy() {

	IKESprite* MiniEnemySprite_;
	MiniEnemySprite_ = IKESprite::Create(11, { 0.0f,0.0f });
	MiniEnemySprite_->SetAnchorPoint({ 0.5f,0.5f });
	MiniEnemySprite.reset(MiniEnemySprite_);

	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::ThornEnemy);
}
//初期化
bool ThornEnemy::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* m_Object_ = new IKEObject3d();
	m_Object_ = IKEObject3d::Create();
	m_Object_->SetModel(m_Model);
	m_Position = { 97.0f,-100.0,0.0f };
	m_Object_->SetPosition(m_Position);
	m_Scale = { 1.7f,1.7f,1.7f };
	m_Object_->SetScale(m_Scale);
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_Object_->SetRotation(m_Rotation);
	m_Object_->SetLightEffect(false);
	m_Object.reset(m_Object_);
	//敵の種類
	m_EnemyType = Thorn;
	return true;
}
//更新
void ThornEnemy::Action() {
	//sin波によって上下に動く
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);
	m_Position.y = (sin(m_Angle2) * 8.0f + 8.0f) + (m_ThornSetPos);
	RotMove();
	if (m_Alive && UpdateCollide()) {
		ThornCollision();
		PlayerCollide();	
		Obj_SetParam();
	}

	//ダメージのインターバル
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}

	//ミニマップに表示させる
	MapEnemy();
}
//描画
void ThornEnemy::Draw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
	}
}
//ダメージを受ける(この敵は受けない　弾かれる)
bool ThornEnemy::ThornCollision() {
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
			m_DamageTimer = 50;
			player->PlayerThornHit(m_Position);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (Collision::OBBCollision(OBB1, OBB2) && m_HP > 0 && (!m_Damage) && (player->CheckAttack()) && (player->GetPosition().x > m_Position.x)) {
			m_Damage = true;
			m_DamageTimer = 50;
			player->PlayerThornHit(m_Position);
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}
//ポーズ
void ThornEnemy::Pause() {
	m_Position.y = (sin(m_Angle2) * 8.0f + 8.0f) + (m_ThornSetPos);
	Obj_SetParam();
	m_Object->Update();
}
//回転の動き
void ThornEnemy::RotMove() {
	switch (m_RotNumber) {
	case Stop:
		m_Interval++;
		if (m_Interval > 10) {
			m_Interval = 0;
			m_RotNumber = Right;
			m_AfterRot.x = 90.0f;
			break;
		}


	case Right:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Left;
			m_AfterRot.x = -90.0f;
			m_Frame = 0.0f;
			break;
		}

	case Left:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Turn;
			m_AfterRot.x = 720.0f;
			m_Frame = 0.0f;
			break;
		}
		
	case Turn:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_RotNumber = Stop;
			m_Rotation.x = 0.0f;
			m_Frame = 0.0f;
			break;
		}
	}
	
	m_Rotation.x = Ease(In, Cubic, m_Frame, m_Rotation.x, m_AfterRot.x);
}
//解放
void ThornEnemy::Finalize() {
	//enemyeffects.pop_back();
}

void ThornEnemy::MapDraw(XMFLOAT4 Color) {
	MiniEnemySprite->SetColor(Color);
	IKESprite::PreDraw();
	MiniEnemySprite->Draw();
}