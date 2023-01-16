#pragma once
#include"InterEnemy.h"
using namespace std;         //  名前空間指定
//普通の敵
class Enemy :public InterEnemy {
public:
	Enemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//初期化
	void Finalize() override;//開放
	void Action()override;//更新
	void Pause() override;//ポーズのとき
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void Move();//普通の移動
	void AttackExtra();//攻撃前の予備動作
	void Tackle();//タックル
	void DeathMove();//死んだときの動き
	void Draw(DirectXCommon* dxCommon) override;//描画
private:
	bool m_AttackExtra = false;//攻撃前の予備動作
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };//イージング後の回転
	float m_Frame = 0.0f;//フレーム
};

