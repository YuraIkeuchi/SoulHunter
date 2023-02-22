#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//上下に動く敵
class ThornEnemy :public InterEnemy {
public:
	ThornEnemy();
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause()override;//ポーズのとき
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void RotMove();
	//bool Collision(XMFLOAT3 position, float radius);
	bool ThornCollision();
	
public:
	//gettersetter
	
private:
	//回転のための変数
	XMFLOAT3 m_AfterRot = {};
	float m_Frame = 0.0f;

	int m_RotNumber = 0;
	int m_Interval = 0;
	float m_AddAngle = 0.0f;
	
	enum RotNumber {
		Stop,
		Right,
		Left,
		Turn
	};
};

