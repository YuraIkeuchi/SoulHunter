#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//���ʂ̓G
class Enemy :public InterEnemy {
public:
	Enemy();
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Finalize() override;//�J��
	void Action()override;//�X�V
	void Pause() override;//�|�[�Y�̂Ƃ�
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void Move();//���ʂ̈ړ�
	void AttackExtra();//�U���O�̗\������
	void Tackle();//�^�b�N��
	void DeathMove();//���񂾂Ƃ��̓���
	void Draw(DirectXCommon* dxCommon) override;//�`��
private:
	bool m_AttackExtra = false;//�U���O�̗\������
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };//�C�[�W���O��̉�]
	float m_Frame = 0.0f;//�t���[��
};

