#pragma once
#include "GamePlayer.h"
#include "EnemyEffect.h"
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include "CollisionPrimitive.h"
#include "IKESprite.h"

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
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	/// getter
	bool GetLock() { return  m_Lock; }

	bool GetAlive() { return  m_Alive; }

	int GetHP() { return  m_HP; }

	float GetAngle() { return  m_Angle; }

	bool GetEffect() { return  m_Effect; }

	bool GetSoul() { return  m_Soul; }

	const XMFLOAT3& GetStartPos() { return  m_StartPos; }

	float GetThornPos() { return  m_ThornSetPos; }
	/// setter
	void SetEffect(const bool effect) { this->m_Effect = effect; }

	void SetSoul(const bool soul) { this->m_Soul = soul; }

	void SetAngle(const float angle) { this->m_Angle = angle; }

	void SetStartPos(const XMFLOAT3 m_StartPos) { this->m_StartPos = m_StartPos; }

	void SetThornPos(const float m_thornPos) { this->m_ThornSetPos = m_thornPos; }

	//bool Collision(XMFLOAT3 position, float radius);
	
protected:
	//�N���X
	unique_ptr<GamePlayer> player = nullptr;
	std::vector<EnemyEffect*> enemyeffects;
	
	//�X�v���C�g
	unique_ptr<IKESprite> MiniEnemySprite;
	OBB OBB1 = {};
	OBB OBB2 = {};
	//���W��X�P�[���Ȃ�
	XMFLOAT3 fbxscale = { 0.03f,0.03f,0.03f };
	XMFLOAT3 m_HitScale = {};
	XMFLOAT3 m_BoundPower = {};
	XMFLOAT3 m_OldPos = {};
	XMFLOAT3 m_StartPos = {};
	//����
	bool m_Alive = true;
	int m_DeathTimer = 0;
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
	
	//�p�[�e�B�N���֌W
	int m_FootParticleCount = 0;
	int m_DeathParticleCount = 0;
	//�G�̎��(�����蔻��Ȃǂɗp����)
	int m_EnemyType = 0;
	bool m_BulletHit = 0;
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
		FollowType,
		ChestType
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
	//�G�̍��W(�~�j�}�b�v)
	XMFLOAT2 m_EnemyPosition = {};
	//���̓G�̕K�v�ϐ�
	float m_ThornSetPos = 0.0f;
	//�A�j���[�V�����̃X�s�[�h
	int m_AnimeTimer = 1;
	
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

	virtual void ImGuiDraw() = 0;

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

	//�~�j�}�b�v�ɓG��\��
	void MapEnemy();
};