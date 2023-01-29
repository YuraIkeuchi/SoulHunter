#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//�㉺�ɓ����G
class FollowEnemy :public InterEnemy {
public:
	FollowEnemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause()override;//�|�[�Y�̂Ƃ�
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void RotMove();
	//bool Collision(XMFLOAT3 position, float radius);
	bool ThornCollision();

public:
	//gettersetter

private:
	//��]�̂��߂̕ϐ�
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	float m_Frame = 0.0f;

	int m_RotNumber = 0;
	int m_Interval = 0;

	enum RotNumber {
		Stop,
		Right,
		Left,
		Turn
	};
};

