#include "ThornEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include <Easing.h>
using namespace DirectX;

ThornEnemy::ThornEnemy() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::ThornEnemy);
}
//‰Šú‰»
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
	//“G‚ÌŽí—Þ
	m_EnemyType = Thorn;
	return true;
}
//XV
void ThornEnemy::Action() {
	//sin”g‚É‚æ‚Á‚Äã‰º‚É“®‚­
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);
	m_Position.y = (sin(m_Angle2) * 8.0f + 8.0f) + (m_ThornSetPos);
	RotMove();
	if (m_Alive && UpdateCollide()) {
		ThornCollision();
		PlayerCollide();	
		Obj_SetParam();
	}
}
//•`‰æ
void ThornEnemy::Draw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
	}
}
//ƒ_ƒ[ƒW‚ðŽó‚¯‚é(‚±‚Ì“G‚ÍŽó‚¯‚È‚¢@’e‚©‚ê‚é)
bool ThornEnemy::ThornCollision() {
	XMFLOAT3 AttackPos = player->GetAttackPos();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 2.5f, AttackPos.x, AttackPos.y, 2.5f) && (m_HP > 0) && (player->GetAttackTimer() == 2)) {
		player->PlayerThornHit(m_Position);
		return true;
	}
	else {
		return false;
	}

	return true;
}
//ƒ|[ƒY
void ThornEnemy::Pause() {
	m_Object->Update();
}
//‰ñ“]‚Ì“®‚«
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
//‰ð•ú
void ThornEnemy::Finalize() {
	//enemyeffects.pop_back();
}