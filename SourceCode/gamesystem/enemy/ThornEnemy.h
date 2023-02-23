#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//�㉺�ɓ����G
class ThornEnemy :public InterEnemy {
public:
	ThornEnemy();
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause()override;//�|�[�Y�̂Ƃ�
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void RotMove();
	//bool Collision(XMFLOAT3 position, float radius);
	bool ThornCollision();
	
public:
	//gettersetter
	
private:
	//��]�̂��߂̕ϐ�
	XMFLOAT3 m_AfterRot = {};
	float m_Frame = 0.0f;

	int m_RotNumber = 0;
	int m_Interval = 0;
	float m_AddAngle = 0.0f;
	
	enum RotNumber {
		Stop,
		Right,
		Left,
		Turn
	};
};

