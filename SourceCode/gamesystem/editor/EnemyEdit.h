#pragma once
#include "InterEnemy.h"
#include "Player.h"
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