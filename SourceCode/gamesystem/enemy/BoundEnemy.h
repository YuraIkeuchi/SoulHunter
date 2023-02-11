#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//跳ねる敵
class BoundEnemy :public InterEnemy {
public:
	BoundEnemy();
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause() override;//ポーズのとき
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void Move();
};

