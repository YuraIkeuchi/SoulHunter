#pragma once
#include "InterEnemy.h"
#include "GamePlayer.h"
#include "Block.h"
//エネミーのエディタクラス
class EnemyEdit {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://各敵の生成(引数が多いので後々修正する)
	void NormalEnemyArgment(std::vector<InterEnemy*>& enemy,GamePlayer* player);
	void ThornEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player);
	void BoundEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player);
	void BirdEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player);
	void FollowEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player);
	void ChestEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player);
private:
	
};