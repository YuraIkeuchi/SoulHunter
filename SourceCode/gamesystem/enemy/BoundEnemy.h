#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//���˂�G
class BoundEnemy :public InterEnemy {
public:
	BoundEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause() override;//�|�[�Y�̂Ƃ�
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void Move();
};

