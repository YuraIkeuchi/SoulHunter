#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//���˂�G
class BoundEnemy :public InterEnemy {
public:
	BoundEnemy();
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause() override;//�|�[�Y�̂Ƃ�
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void Move();
};

