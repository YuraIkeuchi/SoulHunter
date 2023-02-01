#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//上下に動く敵
class FollowEnemy :public InterEnemy {
public:
	FollowEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause()override;//ポーズのとき
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void FollowMove();
	bool FollowCollision();
	bool VanishFollowEnemy();
	void FollowDamageAct();
public:
	//gettersetter

private:
	bool m_Follow = false;
	int m_FollowTimer = 0;
	//回転のための変数
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	float m_Frame = 0.0f;

	//追従関係
	int m_TargetTimer = 0;
	XMFLOAT2 m_FollowVel{};
	XMFLOAT2 m_Rebound{};
	XMFLOAT2 m_Distance{};
	XMFLOAT3 m_TargetPos{};
};

