#pragma once
#include"InterEnemy.h"
using namespace std;         //  ���O��Ԏw��
//�㉺�ɓ����G
class ChestEnemy :public InterEnemy {
public:
	ChestEnemy();
	bool Initialize() override;//������
	void Action()override;//�X�V
	void Finalize() override;//�J��
	void Pause()override;//�|�[�Y�̂Ƃ�
	void MapDraw(XMFLOAT4 Color) override;//�~�j�}�b�v�̂Ƃ�
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void FollowMove();
	bool FollowCollision();
	bool VanishChestEnemy();
	void TexMove();//�e�N�X�`��������
	bool TexCollide();//�e�N�X�`�������蔻��
public:
	//gettersetter

private:
	//�e�N�X�`��
	unique_ptr<IKETexture> chestTex = nullptr;
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
	//�󔠂��J����e�L�X�g�̕ϐ��֌W
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition{};
	bool m_Hit = false;
};

