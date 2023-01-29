#pragma once
#include "InterEnemy.h"
#include "Player.h"
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
	void NormalEnemyArgment(std::vector<InterEnemy*>& enemy,Player* player,
	Block* block);
	void ThornEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player);
	void BoundEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
		Block* block);
	void BirdEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player,
		Block* block);
	void FollowEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player);
private:
	
};