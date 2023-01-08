#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Player.h"
#include "IKESprite.h"
#include "ParticleTex.h"
#include "MarkEffect.h"
#include "VariableCommon.h" 
#include <array>  
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�Z�[�u�̃N���X
class Save {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	const void Draw();
	//�����蔻��
	bool Collide();
	//�X�e�[�W���Ƃ̏�����
	void InitSave(int StageNumber);
	//�e�N�X�`���̓���
	void TexMove();
	//�A�j���[�V����
	void SaveAnime();
private:
	//�萔
	static const int SaveSprite_Max = 4;//�A�j���[�V�����̐�
public:
	//getter
	const XMFLOAT3& GetPosition() { return  m_Position; }

	bool GetAlive() { return  m_Alive; }

	bool GetGameSave() { return  m_GameSave; }
	//setter
	void SetAlive(bool Alive) { this->m_Alive = Alive; }

	void SetGameSave(bool m_GameSave) { this->m_GameSave = m_GameSave; }

	void SetPosition(const XMFLOAT3& m_Position) { this->m_Position = m_Position; }
private:
	unique_ptr<ParticleTex> particletex = nullptr;
	//�N���X
	unique_ptr<Player> player = nullptr;
	unique_ptr<MarkEffect> markEffect = nullptr;
	//OBJ�⃂�f���Ȃ�
	IKEModel* modelSave = nullptr;
	unique_ptr <IKEObject3d> objSave;
	//�e�N�X�`����X�v���C�g
	array<unique_ptr<IKESprite>, SaveSprite_Max> SaveSprite;
	//���W
	XMFLOAT3 m_Position = {0.0f,0.0f,0.0f};
	XMFLOAT3 m_TexPosition = {0.0f,0.0f,0.0f};
	//�Z�[�u�|�C���g�����邩
	bool m_Alive = false;
	bool m_GameSave = false;//�Z�[�u���ꂽ��
	bool m_SaveText = false;//�Z�[�u���Əo����
	bool m_HitSave = false;//�Z�[�u�|�C���g�ɓ������Ă��邩
	//�A�j���[�V�����֌W
	int m_SaveTimer = 0;
	int m_SaveCount = 0;
	//sin�g�Ɏg������
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//�p�[�e�B�N���֌W
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};