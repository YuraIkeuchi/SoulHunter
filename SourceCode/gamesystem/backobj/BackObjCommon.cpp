#include "BackObjCommon.h"
#include"Collision.h"


bool BackObjCommon::Initialize() {

	return true;
}
//更新
void BackObjCommon::Update() {
	//各オブジェのそれぞれのまとめ
	SetObj();
	if (UpdateCollide()) {
		Obj_SetParam();
	}
}

//描画
void BackObjCommon::Draw(DirectXCommon* dxCommon) {
}

//更新を範囲内に入った時のみ
bool BackObjCommon::UpdateCollide() {
	//マジックナンバー解消のための変数(関数内でしか使わないのでローカル)
	const float l_UpdateRadius = 210.0f;//更新範囲
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
bool BackObjCommon::DrawCollide() {
	//マジックナンバー解消のための変数(関数内でしか使わないのでローカル)
	const float l_DrawRadius = 200.0f;//描画範囲
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, l_DrawRadius, m_PlayerPos.x, m_PlayerPos.y, l_DrawRadius)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

