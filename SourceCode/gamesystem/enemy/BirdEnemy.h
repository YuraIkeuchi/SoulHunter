#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//飛ぶ敵
class BirdEnemy :public InterEnemy {
public:
	BirdEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause() override;//ポーズのとき
	void Draw(DirectXCommon* dxCommon) override;//描画
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void DeathMove();//死んだときの動き
	bool BirdLockOn();
	void Move();
private:
	//ロックオンしている間時間経過する
	int m_LockTimer = 0;
	bool m_Attack = false;//攻撃するか
	double m_speedX = 0.0f;//それぞれの軸の移動力
	double m_speedY = 0.0f;//上と同じ
	int m_BirdTouchWall = 2;//壁にあたったか
	enum BirdTouchWall {
		Down,
		Up,
		No
	};
};

