#pragma once
#include "Block.h"
#include "Player.h"
#include "EnemyEffect.h"
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include "ParticleManager.h"
#include "HitStop.h"
#include "VariableCommon.h"
#include "CollisionPrimitive.h"
#define DIRECTINPUT_VERSION 0x0800

//�G���
class InterEnemy :
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
	void SetHitStop(HitStop* hitstop) { this->hitstop.reset(hitstop); }
	void SetBlock(Block* block) { this->block.reset(block); }

	/// getter
	bool GetLock() { return  m_Lock; }

	bool GetAlive() { return  m_Alive; }

	int GetHP() { return  m_HP; }

	float GetAngle() { return  m_Angle; }

	float GetThornPos() { return  m_ThornSetPos; }

	bool GetEffect() { return  m_Effect; }

	bool GetSoul() { return  m_Soul; }

	const XMFLOAT3& GetStartPos() { return  m_StartPos; }
	/// setter
	void SetEffect(const bool effect) { this->m_Effect = effect; }

	void SetSoul(const bool soul) { this->m_Soul = soul; }

	void SetAngle(const float angle) { this->m_Angle = angle; }

	void SetThornPos(const float m_thornPos) { this->m_ThornSetPos = m_thornPos; }

	void SetStartPos(const XMFLOAT3 m_StartPos) { this->m_StartPos = m_StartPos; }
	//bool Collision(XMFLOAT3 position, float radius);
	
protected:
	//�N���X
	unique_ptr<Player> player = nullptr;
	unique_ptr<Block> block = nullptr;
	std::vector<EnemyEffect*> enemyeffects;
	unique_ptr<ParticleManager> hoot;
	unique_ptr<ParticleManager> death;
	unique_ptr<HitStop> hitstop =nullptr;

	//�X�v���C�g
	unique_ptr<IKESprite> MiniEnemySprite;
	OBB OBB1 = {};
	OBB OBB2 = {};
	//���W��X�P�[���Ȃ�
	//XMFLOAT3 scale = { 2.7f,2.7f,2.7f };
	XMFLOAT3 fbxscale = { 0.03f,0.03f,0.03f };
	XMFLOAT3 m_BoundPower = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_OldPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };
	//����
	bool m_Alive = true;
	int DeathTimer = 0;
	//HP
	int m_HP = 3;
	//���b�N�I��
	bool m_Lock = false;
	//����
	float m_DistanceY = 0.0f;
	//�G�t�F�N�g
	bool m_Effect = false;
	bool m_Soul = false;
	bool m_EffectArgment = false;
	bool m_SoulArgment = false;
	int m_SoulCount = 0;
	//���̓I�Ɏg��
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//���ʂ̓G�֌W
	//���S�_����̑傫��
	XMFLOAT2 m_Radius;
	//�W�����v�������ǂ���
	bool m_Jump = false;
	//�㏸�x
	float m_AddPower = 0.0f;
	//�󒆃t���O
	bool m_Air = false;
	//�d�͉����x
	float m_Gravity = 0.02f;;
	//�ړ����x
	float m_Speed;
	//�U���H������Ƃ��̐������
	//�ړ����邩�ǂ���
	bool m_SetMove;
	//�q�b�g��������
	int m_HitDir;
	//�ړ�����
	int m_MoveTimer;
	//�ړ����ĂȂ��Ԃ̃C���^�[�o��
	int m_NotMoveTimer;
	//�n�ʂɂ��邩�ǂ���
	bool m_OnGround;
	//�ːi�U���̃��b�N�I������^�C�~���O�̃^�C�}�[
	int m_TargetTimer;
	//�G���ǂ����̕ǂɂ���������
	enum TouchWall {
		RightTouch,
		LeftTouch,
		DownWall,
	};
	int m_TouchWall;
	//���̓G�̕K�v�ϐ�
	float m_ThornSetPos = 0.0f;
	//�p�[�e�B�N���֌W
	int m_HootParticleCount = 0;
	int m_DeathParticleCount = 0;
	//�G�̎��(�����蔻��Ȃǂɗp����)
	int m_EnemyType = 0;
	bool m_BulletHit = 0;
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
	};
	//�A�j���[�V����
	bool m_AnimationStop = false;
	//�f�B�]���u
	bool m_Disolve = false;
	//���񂾂Ƃ��̃��[�V����
	bool m_DeathMotion = false;
	//�W�����v���̃G�t�F�N�g��������
	bool m_BirdEffectArgment = false;
	//�_���[�W�t���O
	bool m_Damage = false;
	int m_DamageTimer = 0;

	//�G�̍��W
	XMFLOAT2 m_EnemyPosition = { 0.0f,0.0f };
	
public:
	virtual ~InterEnemy() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual bool Initialize()override;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();

	virtual void Action() = 0;//�G�̍s��

	/// <summary>
	/// �|�[�Y�̂Ƃ�
	/// </summary>
	virtual void Pause() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw(DirectXCommon* dxCommon)override;

	virtual void MapDraw(XMFLOAT4 Color) = 0;


	bool Collision();//���ʂ̓����蔻��

	bool PlayerCollide();//�v���C���[���_���[�W��H�炤�����蔻��

	void DamageAct();//�_���[�W���󂯂����̓���

	bool LockOn();//���b�N�I��

	bool UpdateCollide();//�X�V�͈�

	bool DrawCollide();//�`��͈�

	//�����Ƀp�[�e�B�N��
	void BirthParticle();

	//���񂾎�
	void DeathBirthParticle();

	bool VanishEnemy();//�G�������鏈��

	void ArgEffect();//�G�t�F�N�g����

	void ArgSoul();//�G�t�F�N�g����

	//�p�[�e�B�N���֌W
	void ParticleInit();
	void ParticleUpdate();

	//�~�j�}�b�v�ɓG��\��
	void MapEnemy();
};