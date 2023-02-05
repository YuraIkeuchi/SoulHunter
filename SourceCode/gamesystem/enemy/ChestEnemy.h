#pragma once
#include"InterEnemy.h"
#include "Shake.h"
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
	void ChestMove();
	bool ChestCollision();
	bool VanishChestEnemy();
	void DamageChestAct();//�_���[�W���󂯂����̓���
	void TexMove();//�e�N�X�`��������
	bool TexCollide();//�e�N�X�`�������蔻��
	bool PlayerCollide();//�v���C���[�Ƃ̓����蔻��
public:
	//gettersetter

private:
	//�N���X
	unique_ptr<Shake> shake = nullptr;
	//�e�N�X�`��
	unique_ptr<IKETexture> chestTex = nullptr;
	float m_Frame = 0.0f;
	//�󔠂��J����e�L�X�g�̕ϐ��֌W
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition{};
	//�G�̕ϐ�
	bool m_Hit = false;
	bool m_Attack = false;
	XMFLOAT3 m_AfterPos{};

	int m_MoveNumber = 0;
	//�G�̍s���p�^�[��
	enum MoveNumber {
		ShakeChest,
		SetChest,
		AttackChest,
		IntervalChest,
		ReturnChest,
	};

	int m_IntervalTimer = 0;

	//�V�F�C�N
	XMFLOAT3 m_ShakePos{};

	//�F
	XMFLOAT4 m_AfterColor{};
};

