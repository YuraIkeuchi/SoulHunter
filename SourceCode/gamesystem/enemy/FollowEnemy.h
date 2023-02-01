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
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void FollowMove();
	bool FollowCollision();
	bool VanishFollowEnemy();
	void FollowDamageAct();
public:
	//gettersetter

private:
	bool m_Follow = false;
	int m_FollowTimer = 0;
	//��]�̂��߂̕ϐ�
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	float m_Frame = 0.0f;

	//�Ǐ]�֌W
	int m_TargetTimer = 0;
	XMFLOAT2 m_FollowVel{};
	XMFLOAT2 m_Rebound{};
	XMFLOAT2 m_Distance{};
	XMFLOAT3 m_TargetPos{};
};

