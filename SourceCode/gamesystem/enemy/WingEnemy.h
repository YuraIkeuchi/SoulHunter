#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//���˂�G
class WingEnemy :public InterEnemy {
public:
	WingEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	//void SetPlayerEffect(PlayerEffect* playereffect) { this->playereffect.reset(playereffect); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause() override;//�|�[�Y�̂Ƃ�
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void Move();
};

