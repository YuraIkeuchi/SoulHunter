#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//跳ねる敵
class WingEnemy :public InterEnemy {
public:
	WingEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	//void SetPlayerEffect(PlayerEffect* playereffect) { this->playereffect.reset(playereffect); }
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause() override;//ポーズのとき
	void Draw(DirectXCommon* dxCommon) override;//描画
	void Move();
};

