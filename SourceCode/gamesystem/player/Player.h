#pragma once
#include "Block.h"
#include "DirectXCommon.h"
#include "VolumManager.h"
#include "ParticleHeal.h"
#include "SwordParticle.h"
#include "ObjCommon.h"
#include "AttackEffect.h"
#include "WallAttackEffect.h"
#include "PlayerDamageEffect.h"
#include "PlayerDushEffect.h"
#include "VariableCommon.h"
#include "Shake.h"
#include "ParticleManager.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

class Player :
	public ObjCommon
{
public:
	void SetBlock(Block* block) { this->block.reset(block); }
	Player();

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
	//���̍X�V
	void SwordUpdate();
	//�G�t�F�N�g�̍X�V
	void EffectUpdate();
	//�v���C���[�̋���
	//�ړ�
	void PlayerMove();
	//�����A�j���[�V����
	void WalkAnimation();
	//���ʈړ�����
	void MoveCommon(float Velocity,int Dir,float RotationY);
	//�W�����v
	void PlayerJump();
	//����
	void PlayerFall();
	//�U��
	void PlayerAttack();
	//�U�������蔻�����邩
	bool CheckAttack();
	//�_�b�V��
	void PlayerDush();
	//HP��
	void PlayerHeal();
	//�_���[�W
	void PlayerDamage();
	//�U���G�t�F�N�g
	void AttackArgment();
	//�ǃG�t�F�N�g
	void DushArgment();
	//�_�b�V���G�t�F�N�g
	void DamageArgment();
	//�_���[�W�G�t�F�N�g
	void WallArgment();
	//�S�[����̓���
	void GoalMove();
	//���񂾎��̓���
	bool DeathMove();
	//�v���C���[���G�ɂ��������u�Ԃ̔���
	void PlayerHit(const XMFLOAT3& pos);
	//�v���C���[���G�ɂ��������u�Ԃ̔���
	void PlayerThornHit(const XMFLOAT3& pos);
	//�X�L�����Z�b�g
	void ResetSkill();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

	/// <summary>
	/// �J��
	/// </summary>
	void Finalize();
	//�|�[�Y�̂Ƃ�
	void Pause();
	//�G�f�B�^�[�̂Ƃ�
	void Editor();
	//�X�e�[�W���Ƃ̈ʒu������
	void InitPlayer(int StageNUmber);

	//���ɂ����������̕�������
	void ResPornPlayer();

	//���[�h�����Ƃ��̈ʒu������
	void LoadPlayer(const XMFLOAT3& StartPos);

	//�����Ƀp�[�e�B�N��
	void BirthParticle();

	//�A�j���[�V�����֌W
	void PlayerAnimetion(int Number,int AnimeSpeed);
	
	//�����V�[���̂��߂̏���
	void IntroductionUpdate(int Timer);
	void IntroductionDraw(DirectXCommon* dxCommon);

	//�{�X�o��V�[���̂��߂̏���
	void BossAppUpdate(int Timer);
	void BossAppDraw(DirectXCommon* dxCommon);
	//�{�X�I���V�[���̂��߂̏���
	void BossEndUpdate(int Timer);
	void BossEndDraw(DirectXCommon* dxCommon);
	//�N���A�V�[���̂��߂̏���
	void ClearUpdate(int Timer);
	void ClearDraw(DirectXCommon* dxCommon);
public:
	//getter setter
	bool GetAlive() { return  m_Alive; }
	int GetHP() { return  m_HP; }
	float GetSoulCount() { return  m_SoulCount; }
	int GetInterVal() { return  m_Interval; }
	float GetAddPower() { return  m_AddPower; }
	float GetVelosity() { return  m_Velocity; }
	bool GetUseCompass() { return  s_UseCompass; }
	bool GetUseLibra() { return  s_UseLibra; }
	bool GetUseDush() { return  s_UseDush; }
	bool GetUseHeal() { return  s_UseHeal; }
	bool GetChangeInterVal() { return  m_ChangeInterVal; }
	bool GetReadText() { return  m_ReadText; }

	const XMFLOAT3& GetSwordScale() { return  m_SwordScale; }
	const XMFLOAT3& GetSwordPosition() { return  m_SwordPos; }
	XMMATRIX GetSwordMatrot() { return m_SwordMatRot; }

	void SetHP(int HP) { this->m_HP = HP; }
	void SetSoulCount(float SoulCount) { this->m_SoulCount = SoulCount; }
	void SetInterval(int Interval) { this->m_Interval = Interval; }
	void SetUseDush(bool UseDush) { this->s_UseDush = UseDush; }
	void SetUseLibra(bool UseLibra) { this->s_UseLibra = UseLibra; }
	void SetUseCompass(bool UseCompass) { this->s_UseCompass = UseCompass; }
	void SetUseHeal(bool UseHeal) { this->s_UseHeal = UseHeal; }
	void SetChangeInterVal(bool m_ChangeInterVal) { this->m_ChangeInterVal = m_ChangeInterVal; }
	void SetGoalDir(int m_GoalDir) { this->m_GoalDir = m_GoalDir; }
	void SetCollideChest(bool m_CollideChest) { this->m_CollideChest = m_CollideChest; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
	void SetReadText(bool m_ReadText) { this->m_ReadText = m_ReadText; }

private:
	//�X�L�����g���邩�ǂ���
	static bool s_UseDush;
	static bool s_UseLibra;
	static bool s_UseCompass;
	static bool s_UseHeal;
private:
	//�U���̈ʒu�����
	XMFLOAT3 m_AttackPos = { 0.0f,0.0f,0.0f };
	unique_ptr<SwordParticle> swordparticle = nullptr;
	unique_ptr<ParticleManager> hoot;
	unique_ptr<ParticleManager> heal;
	unique_ptr<ParticleManager> death;
	//�N���X
	unique_ptr<Block> block = nullptr;
	vector<AttackEffect*> attackeffects;
	vector<WallAttackEffect*>walleffects;
	vector<PlayerDushEffect*> dusheffects;
	vector<PlayerDamageEffect*> damageeffects;
	unique_ptr<Shake> shake = nullptr;
	//�v���C���[�h��
	bool m_PlayMode = false;
	//�����Ă��邩�ǂ���
	bool m_Alive = true;
	//���X�|�[��
	int m_RespornTimer = 0;
	//�U���ł��邩
	bool m_Attack = false;
	int m_AttackTimer = 0;
	//�U�����̃G�t�F�N�g��������
	bool m_AttackArgment = false;
	//2��ڂ̍U������
	int m_AttackCount = 0;
	int m_SecondTimer = 0;
	//�U�����ǂɂ����������̃G�t�F�N�g��������
	bool m_WallArgment = false;
	//�_�b�V�����̃G�t�F�N�g��������
	bool m_DushArgment = false;
	//�_���[�W�G�t�F�N�g��������
	bool m_DamageArgment = false;
	//HP
	int m_HP = 0;
	//���G����
	int m_Interval = 0;
	int m_FlashCount = 0;
	//�_���[�W�󂯂��Ƃ��̔���
	float m_BoundPower = 0.0f;
	//�_���[�W���󂯂�����
	int m_HitDir = 0;
	//�_���[�W���̃G�t�F�N�g
	bool m_Effect = false;
	//�v���C���[�֌W
	//���W
	XMFLOAT3 m_OldPlayerPos = {0.0f,0.0f,0.0f};
	//�v���C���[�̃}�b�v�`�b�v�̓����蔻�����萳�m�ɍs�����߂̏���
	XMFLOAT3 m_LimitRightPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_LimitLeftPos = { 0.0f,0.0f,0.0f };
	bool m_RightLimit = false;
	bool m_LeftLimit = false;
	//���S�_����̑傫��
	XMFLOAT2 m_Radius = {0.0f,0.0f};
	//�W�����v�������ǂ���
	bool m_Jump = false;
	//�㏸�x
	float m_AddPower = 0.0f;
	//�d�͉����x
	float m_Gravity = 0.0f;
	//�W�����v��
	int m_JumpCount = 4;
	//�W�����v���̓����̕ϐ�
	bool m_JumpRot = false;
	float m_RotFrame = 0.0f;
	//�����Ă������
	float m_Velocity = 0.0f;
	int m_PlayerDir = 0;
	enum PlayerDir {
		Right,
		Left
	};
	//�_�b�V���֌W
	bool m_Dush = false;
	int m_DushTimer = 10;
	enum DushDir {
		NoDush,
		DushRight,
		DushLeft,
	};
	int m_DushDir = 0;
	//�����̃p�[�e�B�N��
	int m_FoodParticleNum = 5;
	int m_FoodParticleCount = 0;
	XMFLOAT3 m_FoodParticlePos = { 0.0f,0.0f,0.0f };
	//���ʂ̃p�[�e�B�N��
	int m_ParticleCount = 0;
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	//���̃p�[�e�B�N��
	int m_SwordParticleCount = 0;
	XMFLOAT3 m_SwordParticlePos = { 0.0f,0.0f,0.0f };
	//�S�[�������Ƃ��̕ϐ�
	bool m_ChangeInterVal = false;
	int m_IntervalTimer = 0;
	int m_GoalDir = 0;
	enum GoalDir {
		No,
		LeftGoal,
		RightGoal,
		UpGoal,
		DownGoal
	};
	//�󔠂����Ă��邩
	bool m_ReadText = false;
	bool m_CollideObj = false;
	bool m_CollideChest = false;
	//�v���C���[���g���鍰�̐�
	float m_SoulCount = 20.0f;

	//�K�E�Z
	float m_Frame = 0.0f;
	//�p�[�e�B�N���̂��߂̕ϐ�
	int m_ParticleNumber = 0;
	//���[�r�[���̓���
	bool m_Movie = false;
	//�f�B�]���u
	float Disolve = -1.0f;
	//��������
	int m_SaveTimer = 0;
	XMFLOAT3 m_RespornPos = { 0.0f,0.0f,0.0f };
	//HP�񕜊֌W
	int m_HealCount = 0;
	int m_HealTimer = 0;
	int m_HealType = 0;
	enum HealType {
		NoHeal,
		InterVal,
		Invocation,
		Fail,
	};

	//��s��
	XMMATRIX m_HandMat;
	XMVECTOR m_VectorSwordPos;//���̍��W
	XMFLOAT3 m_SwordPos;//���̍��W
	XMFLOAT3 m_SwordRotation = { 32.0f,91.0f,48.0f };
	XMFLOAT3 m_SwordScale = { 4.5f,4.5f,4.5f };
	XMFLOAT4 m_SwordColor = { 1.0f,1.0f,0.0f,0.0f };
	float m_SwordFrame = 0.0f;
	bool m_SwordEase = false;
	int m_SwordType = 0;
	int m_SwordParticleNum = 0;
	float m_SwordAfterAlpha = 0.0f;
	XMMATRIX m_SwordMatRot;
	enum SwordType {
		NoSword,
		ArgSword,
		DeleteSword,
	};

	//���񂾓���
	bool m_Death = false;
	int m_DeathTimer = 0;
	//�V�F�C�N�p�ϐ�
	XMFLOAT3 m_ShakePos = { 0.0f,0.0f,0.0f };

	//�A�j���[�V�����^�C�}�[�p
	struct AnimationTimer {
		int MoveAnimation = 0;
		int NotAnimation = 0;
		int FallAnimation = 0;
	};

	AnimationTimer m_AnimationTimer;
	enum AnimationType {
		FirstAttack,
		SecondAttack,
		Walk,
		FirstJump,
		Wait,
		Death,
		SecondJump,
		ThirdJump,
		FinalJump,
		Dush,
		Damage,
		Fall
	};
};

