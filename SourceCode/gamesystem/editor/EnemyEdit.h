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
//�G�l�~�[�̃G�f�B�^�N���X
class EnemyEdit {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�e�G�̐���(�����������̂Ō�X�C������)
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