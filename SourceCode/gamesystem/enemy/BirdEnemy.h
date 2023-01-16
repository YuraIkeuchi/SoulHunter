#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//��ԓG
class BirdEnemy :public InterEnemy {
public:
	BirdEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause() override;//�|�[�Y�̂Ƃ�
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void DeathMove();//���񂾂Ƃ��̓���
	bool BirdLockOn();
	void Move();
private:
	//���b�N�I�����Ă���Ԏ��Ԍo�߂���
	int m_LockTimer = 0;
	bool m_Attack = false;//�U�����邩
	double m_speedX = 0.0f;//���ꂼ��̎��̈ړ���
	double m_speedY = 0.0f;//��Ɠ���
	int m_BirdTouchWall = 2;//�ǂɂ���������
	enum BirdTouchWall {
		Down,
		Up,
		No
	};
};

