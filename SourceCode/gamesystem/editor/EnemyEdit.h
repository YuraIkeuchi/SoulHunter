#pragma once
#include "InterEnemy.h"
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "PlayerEffect.h"
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
	void NormalEnemyArgment(std::vector<InterEnemy*>& enemy,Player* player,PlayerBullet* playerbullet,
	PlayerEffect* playereffect,Block* block, HitStop* hitstop);
	void ThornEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
		PlayerEffect* playereffect, HitStop* hitstop);
	void BoundEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
		PlayerEffect* playereffect, Block* block, HitStop* hitstop);
	void BirdEnemyArgment(std::vector<InterEnemy*>& enemy, Player* player, PlayerBullet* playerbullet,
		PlayerEffect* playereffect, Block* block, HitStop* hitstop);
private:
	
};