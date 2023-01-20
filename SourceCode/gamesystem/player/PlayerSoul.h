#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "InterEnemy.h"
#include "IKETexture.h"
#include "Player.h"
#include "Block.h"
#include "ParticleManager.h"
#include <memory> 
using namespace std;         //  ���O��Ԏw��
//�v���C���[�̍��̃N���X
class PlayerSoul {
public:
	void SetBlock(Block* block_) { this->block.reset(block_); }
	void SetPlayer(Player* player) { this->player.reset(player); }
	PlayerSoul();

	void Initialize();//������
	void Finalize();//���
	//������ɂ��G���ƂɕK�v�ɂȂ��Ă��܂���
	void Update(InterEnemy* enemy);
	void Draw();//�`��
	void SetEffect(InterEnemy* enemy);
	bool Collide();//�����蔻��
	void Move();//���̓���
	void VanishSoul(InterEnemy* enemy);//����������
	bool UpdateCollide();//�X�V�͈�
	bool DrawCollide();//�`��͈�
	void BirthParticle();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	void SetEffect(bool m_Effect) { this->m_Effect = m_Effect; }
	
private:
	//�e�N�X�`��
	unique_ptr<IKETexture> soultex;
	//�p�[�e�B�N��
	//�N���X
	unique_ptr<Player> player = nullptr;//
	unique_ptr<Block> block = nullptr;
	//�ϐ�
	XMFLOAT3 m_Position;//���W
	XMFLOAT3 m_OldPos;//�ʒu�t���[�����ꂽ���W
	XMFLOAT3 m_AfterPos = { 0.0f,0.0f,0.0f };//�C�[�W���O��̍��W
	XMFLOAT3 m_Scale = {0.0f,0.0f,0.0f};//�傫��
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	float m_BoundPower = 0.0f;//��тł��u�Ԃɉ�����
	float m_AddPower = 0.0f;//������
	XMFLOAT2 m_Radius;//�}�b�v�`�b�v�����蔻��p�̑傫��
	bool m_Effect = false;//�o��
	bool m_EndSoul = false;//��������
	bool m_Jump = false;//�n�ʂɂ��Ă��邩�ǂ���
	int m_Timer = 0;//����
	int m_ParticleCount = 0;//�p�[�e�B�N���̏o����b�Ԋu
	bool m_Move = false;//�������ǂ���
	float m_Frame = 0.0f;//�t���[��
	//unique_ptr<ParticleManager> soulparticle;
public:
	Sphere collider;
};