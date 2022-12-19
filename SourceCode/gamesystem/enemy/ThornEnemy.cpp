#include "ThornEnemy.h"
#include"Collision.h"
#include "ModelManager.h"
#include <Easing.h>
using namespace DirectX;

ThornEnemy::ThornEnemy() {
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
}
//描画
void ThornEnemy::Draw(DirectXCommon* dxCommon) {
	/*ImGui::Begin("Thorn");
	ImGui::Text("m_AfterRot.x : %f", m_AfterRot.x);
	ImGui::Text("m_Rotation.x : %f", m_Rotation.x);
	ImGui::Text("m_RotNunmber : %d", m_RotNumber);
	ImGui::Text("frame : %f", m_Frame);
	ImGui::End();*/
	IKEObject3d::PreDraw();
	if (m_Alive && DrawCollide()) {
		Obj_Draw();
	}
}
//ダメージを受ける(この敵は受けない　弾かれる)
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
//ポーズ
void ThornEnemy::Pause() {
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