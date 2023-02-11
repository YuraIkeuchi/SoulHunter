#pragma once
#include "Block.h"
#include "DirectXCommon.h"

#include "ObjCommon.h"
#include "Shake.h"
#include "PlayerEffect.h"
#include <memory>
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

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;
	void ImGuiDraw();

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
	//�v���C���[�̉�]
	void PlayerRolling();
	//HP��
	void PlayerHeal();
	//�_���[�W
	void PlayerDamage();
	//�S�[����̓���
	void GoalMove();
	//���񂾎��̓���
	bool DeathMove();
	//�v���C���[���G�ɂ��������u�Ԃ̔���
	void PlayerHit(const XMFLOAT3& pos);
	//�v���C���[���G�ɂ��������u�Ԃ̔���
	void PlayerThornHit(const XMFLOAT3& pos);
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
	//���񂾎�
	void DeathBirthParticle();
	//�񕜃p�[�e�B�N��
	void HealParticle();
	//�U�����Z�b�g
	void ResetAttack();

	//�A�j���[�V�����֌W
	void PlayerAnimetion(int Number,int AnimeSpeed);
	//�G�t�F�N�g����
	void BirthEffect(const std::string& newname, XMFLOAT3 pos, int dir);

	//csv���J��
	void OpenCsv();
	//csv�̃��[�h
	void LoadCsv();
	
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
	bool GetChangeInterVal() { return  m_ChangeInterVal; }
	bool GetReadText() { return  m_ReadText; }

	void SetHP(int HP) { this->m_HP = HP; }
	void SetSoulCount(float SoulCount) { this->m_SoulCount = SoulCount; }
	void SetInterval(int Interval) { this->m_Interval = Interval; }
	void SetChangeInterVal(bool m_ChangeInterVal) { this->m_ChangeInterVal = m_ChangeInterVal; }
	void SetGoalDir(int m_GoalDir) { this->m_GoalDir = m_GoalDir; }
	void SetCollideChest(bool m_CollideChest) { this->m_CollideChest = m_CollideChest; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
	void SetReadText(bool m_ReadText) { this->m_ReadText = m_ReadText; }
	void SetTutorialFinish(bool m_TutorialFinish) { this->m_TutorialFinish = m_TutorialFinish; }

private:
	
private:
	vector<PlayerEffect*> effects;

	//�N���X
	unique_ptr<Block> block = nullptr;
	
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
	//2��ڂ̍U������
	int m_AttackCount = 0;
	int m_SecondTimer = 0;
	//HP
	int m_HP = 0;
	//���G����
	int m_Interval = 0;
	int m_FlashCount = 0;
	//�_���[�W�󂯂��Ƃ��̔���
	float m_BoundPower = 0.0f;
	//�_���[�W���󂯂�����
	int m_HitDir = 0;
	//�v���C���[�֌W
	//���W
	XMFLOAT3 m_OldPos = {0.0f,0.0f,0.0f};
	//�v���C���[�̃}�b�v�`�b�v�̓����蔻�����萳�m�ɍs�����߂̏���
	XMFLOAT3 m_LimitPos = { 0.0f,0.0f,0.0f };
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
	float m_Velocity = 0.0f;
	//�����Ă������
	int m_PlayerDir = 0;
	enum PlayerDir {
		Right,
		Left
	};
	//�_�b�V���֌W
	bool m_Dush = false;
	bool m_Rolling = false;
	float m_SideFrame = 0.0f;
	float m_SideVelocity = 0.0f;
	//�����̃p�[�e�B�N��
	int m_FootParticleCount = 0;
	//���ʂ̃p�[�e�B�N��
	int m_DeathParticleCount = 0;

	//�S�[�������Ƃ��̕ϐ�
	bool m_ChangeInterVal = false;
	int m_GoalIntervalTimer = 0;
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
	//�C�[�W���O�̂���
	float m_Frame = 0.0f;
	//���[�r�[���̓���
	bool m_Movie = false;
	//��������
	int m_SaveTimer = 0;
	XMFLOAT3 m_RespornPos = { 0.0f,0.0f,0.0f };
	//HP�񕜊֌W
	int m_HealCount = 0;
	int m_HealTimer = 0;
	int m_HealType = 0;
	enum HealType {
		NoHeal,
		UseHeal,
	};

	//�U���̈ʒu�����
	XMFLOAT3 m_AttackPos = { 0.0f,0.0f,0.0f };
	//��s��
	XMMATRIX m_HandMat;

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
	//�v���C���[�̃A�j���[�V����
	enum AnimationType {
		FirstAttack,
		SecondAttack,
		Rolling,
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

	//csv�p�ϐ�
	std::ifstream m_PlayerFile;
	std::stringstream m_PlayerPopcom;
	std::string m_PlayerLine;

	//�`���[�g���A�����̕ϐ�
	bool m_TutorialFinish = false;
};

