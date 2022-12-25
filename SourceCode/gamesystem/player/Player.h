#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Block.h"
#include "IKEFBXModel.h"
#include "IKEFBXObject3d.h"
#include "DirectXCommon.h"
#include "PlayerBullet.h"
#include "ParticleTex.h"
#include "VolumManager.h"
#include "ParticleHeal.h"
#include "SwordParticle.h"
#include "ObjCommon.h"
#include "JumpEffect.h"
#include "AttackEffect.h"
#include "PlayerWing.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

class Player :
	public ObjCommon
{
public:
	void SetPlayerBullet(PlayerBullet* playerbullet) { this->playerbullet.reset(playerbullet); }
	void SetBlock(Block* block) { this->block.reset(block); }
	Player();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	//static Player* Create(IKEModel* model = nullptr);

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
	//�H�֌W
	void WingUpdate();
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
	//�_�b�V��
	void PlayerDush();
	//�e������
	void PlayerShot();
	//�K�E�Z
	void PlayerSpecial();
	//HP��
	void PlayerHeal();
	//�_���[�W
	void PlayerDamage();
	//�G�t�F�N�g����
	void JumpArgment();
	void AttackArgment();
	//�S�[����̓���
	void GoalMove();
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

	//�{�X�V�[���̂��߂̏���
	void BossAppUpdate(int Timer);
	void BossAppDraw(DirectXCommon* dxCommon);
public:
	//getter setter
	const XMFLOAT3& GetAttackPos() { return  m_AttackPos; }
	bool GetAlive() { return  m_Alive; }
	int GetHP() { return  m_HP; }
	int GetJumpCount() { return  m_JumpCount; }
	float GetSoulCount() { return  m_SoulCount; }
	int GetInterVal() { return  m_Interval; }
	float GetCameraDistance() { return  m_CameraDistance; }
	float GetAddPower() { return  m_AddPower; }
	float GetVelosity() { return  m_Velocity; }
	bool GetUseCompass() { return  s_UseCompass; }
	bool GetUseLibra() { return  s_UseLibra; }
	bool GetUseDush() { return  s_UseDush; }
	bool GetUseHeal() { return  s_UseHeal; }
	bool GetEffect() { return  m_Effect; }
	int GetAttackTimer() { return  m_AttackTimer; }
	bool GetDush() { return  m_Dush; }
	bool GetChangeInterVal() { return  m_ChangeInterVal; }
	bool GetSpecialEffect() { return  m_SpecialEffect; }
	bool GetReadText() { return  m_ReadText; }

	void SetHP(int HP) { this->m_HP = HP; }
	void SetSoulCount(float SoulCount) { this->m_SoulCount = SoulCount; }
	void SetInterval(int Interval) { this->m_Interval = Interval; }
	void SetEffect(bool effect) { this->m_Effect = effect; }
	void SetSpecialEffect(bool SpecialEffect) { this->m_SpecialEffect = SpecialEffect; }
	void SetUseDush(bool UseDush) { this->s_UseDush = UseDush; }
	void SetUseLibra(bool UseLibra) { this->s_UseLibra = UseLibra; }
	void SetUseCompass(bool UseCompass) { this->s_UseCompass = UseCompass; }
	void SetUseHeal(bool UseHeal) { this->s_UseHeal = UseHeal; }
	void SetChangeInterVal(bool m_ChangeInterVal) { this->m_ChangeInterVal = m_ChangeInterVal; }
	void SetGoalDir(int m_GoalDir) { this->m_GoalDir = m_GoalDir; }
	void SetCollideObj(bool m_CollideObj) { this->m_CollideObj = m_CollideObj; }
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
	unique_ptr<ParticleTex> particletex = nullptr;
	unique_ptr<SwordParticle> swordparticle = nullptr;
	unique_ptr<ParticleHeal> particleheal = nullptr;
	//�N���X
	unique_ptr<PlayerBullet> playerbullet = nullptr;
	unique_ptr<Block> block = nullptr;
	std::vector<JumpEffect*> jumpeffects;
	std::vector<AttackEffect*> attackeffects;
	unique_ptr<PlayerWing> playerwing = nullptr;
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
	//HP
	int m_HP = 5;
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
	//�W�����v���̃G�t�F�N�g��������
	bool m_JumpArgment = false;
	//�����Ă������
	float m_Velocity = 0.0f;
	int m_PlayerDir = 0;
	enum PlayerDir {
		Right,
		Left
	};
	//�_�b�V���֌W
	bool m_Dush = false;
	int m_DushTimer = 15;
	enum DushDir {
		NoDush,
		DushRight,
		DushLeft,
	};
	int m_DushDir = 0;
	//�����̃p�[�e�B�N��
	int m_FoodParticleNum = 5;
	float m_FoodParticleCount = 0;
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
	//�A�j���[�V�����֌W
	int m_Number = 0;
	bool m_AnimeLoop = false;
	int m_AnimeTimer = 0;
	int m_AnimeSpeed = 1;
	bool m_AnimationStop = false;
	//�K�E�Z
	bool m_Special = false;
	float m_Frame = 0.0f;
	float m_AfterPosY = 0.0f;
	int m_SpecialCount = 0;
	bool m_SpecialEffect = false;
	//�K�E�Z���̃J�����̋���
	float m_CameraDistance = 0.0f;
	//�p�[�e�B�N���̂��߂̕ϐ�
	int m_ParticleNumber = 0;
	float m_BulletDistance = 0.0f;
	//��o�p�̍U���^�C�v
	int m_AttackType = 0;
	enum AttackType {
		Sword,
		Shot,
		Special
	};
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
	XMFLOAT3 m_SwordRotation = { 60.0f,100.0f,0.0f };
	XMFLOAT4 m_SwordColor = { 1.0f,1.0f,0.0f,0.0f };
	float m_SwordFrame = 0.0f;
	bool m_SwordEase = false;
	int m_SwordType = 0;
	int m_SwordParticleNum = 0;
	float m_SwordAfterAlpha = 0.0f;
	enum SwordType {
		NoSword,
		ArgSword,
		DeleteSword,
	};
	XMFLOAT3 m_WingPosition = { 0.0f,0.0f,0.0f };
	int m_WingDeleteCount = 0;
};

