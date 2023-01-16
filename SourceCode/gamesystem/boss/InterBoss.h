#pragma once
#include <DirectXMath.h>
#include "DirectXCommon.h"
#include "Player.h"
#include "Pause.h"
#include "IKETexture.h"
#include "ParticleTex.h"
#include "BossEffect.h"
#include "BossName.h"
#include "VariableCommon.h"
#include "ObjCommon.h"
#include "CollisionPrimitive.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
#define DIRECTINPUT_VERSION 0x0800

class InterBoss :
	public ObjCommon {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetPause(Pause* pause) { this->pause.reset(pause); }
	
	//gettersetter
	bool GetEffect() { return  m_Effect; }
	bool GetAlive() { return  m_Alive; }
	const float& GetHP() { return  m_HP; }
	const int& GetDeathTimer() { return  m_DeathTimer; }

	void SetEffect(bool effect) { this->m_Effect = effect; }
	void SetAlive(bool m_Alive) { this->m_Alive = m_Alive; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
public:
	
	//������
	virtual bool Initialize() = 0;
	//������
	virtual bool BattleInitialize() = 0;
	//�X�V
	void Update();
	//�`��
	void Draw(DirectXCommon* dxCommon);
	//�o��V�[���X�V
	void AppUpdate();
	//�o��V�[���`��
	void AppDraw(DirectXCommon* dxCommon);
	//�I���V�[���X�V
	void EndUpdate();
	//�I���V�[���`��
	void EndDraw(DirectXCommon* dxCommon);
	virtual void App() = 0;//�{�X�o�����[�V����

	virtual void Spec() = 0;//�{�X���L�̏���

	virtual void Dead() = 0;//�{�X���L�̏���
	virtual void End() = 0;//�{�X���L�̏���
	virtual void specialDraw(DirectXCommon* dxCommon) = 0;//�{�X���L�̕`��
	virtual void specialDrawApp() = 0;//�{�X���L�̕`��
	virtual void specialDrawEnd() = 0;//�{�X���L�̕`��
	//�p�[�e�B�N��
	void BirthParticle();
	bool collidePlayer();//�v���C���[�Ƃ̓����蔻��
	bool collideBoss();//�U������
	void ArgEffect();//�G�t�F�N�g�̐���
	//void Pause(const int& Timer);
protected:
	//�e�N���X
	std::vector<BossEffect*> bosseffects;
	unique_ptr<Player> player = nullptr;
	unique_ptr<ParticleTex> particletex = nullptr;
	unique_ptr<Pause> pause = nullptr;
	OBB OBB1 = {};
	OBB OBB2 = {};
	//���W���]
	const float PI = 3.14f;
	XMFLOAT3 m_OldPos = { 0,0,0 };
	XMFLOAT3 m_AfterScale{ 2.8f,2.8f,2.8f };
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_TargetPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_OBBScale = { 0.0f,0.0f,0.0f };
	//������͈�
	float m_HitRadius = 0.0f;
	//HP
	float m_HP = 1.0f;
	//�G�t�F�N�g
	bool m_Effect = false;
	float m_Frame = 0.0f;//�t���[��
	float m_RotFrame = 0.0f;//�t���[��
	bool m_Active = false;//�s���J�n
	int m_Action = 0;//�U���̎��
	int m_Pat = 0;//�p�^�[��
	int m_Aiming = 0;//�G�Ǐ]
	int m_CoolT = 0;//�N�[���^�C��
	int m_TargetCoolT = 0;
	int m_AttackCount = 0;//�U���܂ł̊�
	int m_MoveCount = 0;//����s��������
	bool m_Alive = false;//�����Ă܂���
	bool m_BulletHit = false;//�e���q�b�g������
	bool m_Movie = false;//���[�r�[�����ǂ���
	int m_MovieTimer = 0;//���[�r�[�̎���
	bool m_AppMove = false;//�o��V�[��
	bool m_EffectArgment = false;//�G�t�F�N�g����
	int m_DeathTimer = 0;//���ʂ܂ł̎���
	int m_ParticleCount = 0;//�p�[�e�B�N���̐����܂ł̃t���[��
	
	int m_HitDir;
	//�_���[�W�t���O
	bool m_Damage = false;
	int m_DamageTimer = 0;

	//�p�[�e�B�N���֌W
	int m_FoodParticleCount = 0;
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleNum = 5;
};

