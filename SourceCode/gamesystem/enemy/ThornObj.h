#pragma once
#include "Player.h"
#include "ObjCommon.h"
#include "DirectXCommon.h"
#include "ThornParticle.h"
#include <memory>
using namespace std;         //  ���O��Ԏw��
//���̖_
class ThornObj :
public ObjCommon{
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;
	void Update() override;
	//���ꂼ��̕����̓���
	void UpMove();
	void DownMove();
	void RightMove();
	void LeftMove();
	void Pause();
	void Finalize();
	bool Collide();//�����蔻��
	bool UpdateCollide();//�X�V�͈�
	bool DrawCollide();//�`��͈�
	void Draw(DirectXCommon* dxCommon) override;;
public:
	const XMFLOAT3& GetThornPos() { return  m_ThornSetPos; }
	int GetDir() { return  m_Dir; }
	int GetTargetTimer() { return  m_TargetTimer; }

	void SetThornObjPos(const XMFLOAT3 m_ThornSetPos) { this->m_ThornSetPos = m_ThornSetPos; }
	void SetDir(const int Dir) { this->m_Dir = Dir; }
	void SetTargetTimer(const int m_TargetTImer) { this->m_TargetTimer = m_TargetTImer; }
private:
	//�N���X
	unique_ptr<ThornParticle> thornparticle;
	unique_ptr<Player> player = nullptr;
	XMFLOAT3 m_Afterpos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HitArea = { 5.0f,20.0f,5.0f };
	XMFLOAT3 StartPos = {0.0f,0.0f,0.0f};
	float m_Frame = 0.0f;
	bool m_Active = false;//�s���J�n
	int m_Pat = 0;//�p�^�[��
	int m_CoolT = 0;//�N�[���^�C��
	//�����ĂȂ�����
	int m_AttackTimer = 0;
	//���ۂɓ����܂ł̎���
	int m_TargetTimer = 0;
	int m_MoveTImer = 0;
	//csv�œǂݍ��ލ��W
	XMFLOAT3 m_ThornSetPos;
	//�p�[�e�B�N���֌W
	XMFLOAT3 m_SmokeParticlePos;
	int m_SmokeParticleCount = 0;
	XMFLOAT3 m_RockParticlePos;
	float m_AfterRotetion = 0.0f;
	int m_RockParticleCount = 0;
	//�ǂ̍U�������邩
	enum ActionType {
		Stop,
		Set,
		Attack,
		Return,
	};
	//����
	int m_Dir = 0;
	enum Dir {
		Up,
		Down,
		Right,
		Left
	};
};