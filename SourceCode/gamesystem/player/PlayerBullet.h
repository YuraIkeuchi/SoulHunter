#pragma once
#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Block.h"
#include "IKEFBXModel.h"
#include "IKEFBXObject3d.h"
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include "ParticleTex.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�v���C���[�̒e�̃N���X
class PlayerBullet :
	public ObjCommon
{
public:
	void SetBlock(Block* block) { this->block.reset(block); }
	PlayerBullet();
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;

	void StateInitialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;
	//�v���C���[�̋���
	void Draw(DirectXCommon* dxCommon);
	//�e�̈ړ�
	void Shot();

	//�|�[�Y�̂Ƃ�
	void Pause();

public:
	bool GetAlive() { return  m_Alive; }

	void SetAlive(bool Alive) { this->m_Alive = Alive; }

	void SetAddSpeed(float AddSpeed) { this->m_AddSpeed = AddSpeed; }

private:
	//�N���X
	unique_ptr<Block> block = nullptr;
	unique_ptr<ParticleTex> particletex = nullptr;
	//�ϐ�
	XMFLOAT3 m_OldPos = { 0.0f,0.0f,0.0f };
	XMFLOAT2 m_Radius = { 0.5f,0.5f };
	float m_AddSpeed = 0.0f;
	
	bool m_Alive = false;
	int m_ParticleCount = 0;
};

