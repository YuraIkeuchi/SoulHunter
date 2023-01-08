#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "IKEObject3d.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�}�b�v�`�b�v�̃N���X
class Block {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Block();

	void Initialize(std::vector<std::vector<int>>& map, int mapNumber,int StageNumber);
	void Finalize();
	void Update(XMFLOAT3& pos);
	void Draw(XMFLOAT3& pos);

	void ResetBlock();

	//�}�b�v�`�b�v����
	void MapCreate(int mapNumber,int StageNumber);

	//�����������̂ō\���̂ɂ���\��
	//�}�b�v�`�b�v�����蔻��(�v���C���[)
	bool PlayerMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
		const XMFLOAT3& old_pos, bool& is_jump,float& addPower);
	//�}�b�v�`�b�v�����蔻��(�U��)
	bool AttackMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,const XMFLOAT3& old_pos);
	//�}�b�v�`�b�v�����蔻��(�G)
	bool EnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius,
		const XMFLOAT3& old_pos, bool& is_jump,float& EnemyaddPower,int& touchWall,int& HP);
	//�}�b�v�`�b�v�����蔻��(���ł�G)
	bool BirdEnemyMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, int &touchWall,
		const XMFLOAT3& old_pos, bool& Attack);
	//�}�b�v�`�b�v�����蔻��(��)
	bool PlayerSoulMapCollideCommon(XMFLOAT3& pos, XMFLOAT2 radius, 
		const XMFLOAT3& old_pos, bool& is_jump, float& addPower);

	//getter
	const bool& GetThornHit() { return  m_ThornHit; }
	const int& GetThornDir() { return  m_ThornDir; }
	const bool& GetLeftGoal() { return  m_Left_Goal; }
	const bool& GetRightGoal() { return  m_Right_Goal; }
	const bool& GetDownGoal() { return  m_Down_Goal; }
	const bool& GetUpGoal() { return  m_Up_Goal; }
	const bool& GetHitDown() { return m_HitDown; }
	//setter
	void SetThornDir(const int& thorndir) { this->m_ThornDir = thorndir; }
	void SetThornHit(const bool& thornhit) { this->m_ThornHit = thornhit; }
	void SetLeftGoal(const bool& Left_goal) { this->m_Left_Goal = Left_goal; }
	void SetRightGoal(const bool& Right_goal) { this->m_Right_Goal = Right_goal; }
	void SetDownGoal(const bool& Down_goal) { this->m_Down_Goal = Down_goal; }
	void SetUpGoal(const bool& Up_goal) { this->m_Up_Goal = Up_goal; }
private:
	//�n�ʂɂ������Ă��邩
	bool m_HitDown = false;
	//���ɓ���������
	bool m_ThornHit = false;
	//�ǂ̃S�[���ɓ���������
	bool m_Left_Goal = false;
	bool m_Right_Goal = false;
	bool m_Down_Goal = false;
	bool m_Up_Goal = false;
	//�}�b�v�`�b�v1�̑傫��
	const float LAND_SCALE = 5.0f;
	//�}�b�v�`�b�v�֌W
	unique_ptr<IKEModel> modelNormalBlock = nullptr;
	unique_ptr<IKEModel> modelInBlock = nullptr;
	unique_ptr<IKEModel> modelAirBlock = nullptr;
	unique_ptr<IKEModel> modelToge = nullptr;
	unique_ptr<IKEModel> modelGoalBlock = nullptr;
	//�e�}�b�v�̓ǂݍ���
	std::vector<std::vector<int>> stagemap; //1�}�b�v
	std::vector<std::vector<int>> bossmap; //�{�X�}�b�v
	unique_ptr <IKEObject3d> objNormalBlock[map_max_y][map_max_x]; //�X�e�[�W�u���b�N
	unique_ptr <IKEObject3d> objInBlock[map_max_y][map_max_x]; //�X�e�[�W�u���b�N
	unique_ptr <IKEObject3d> objToge[map_max_y][map_max_x]; //�X�e�[�W�u���b�N(��)
	
	//�e�ϐ�
	int m_GoalType[map_max_y][map_max_x];//�S�[���̃^�C�v
	int m_AirType[map_max_y][map_max_x];//�������ǂ���
	XMFLOAT3 m_Distance[map_max_y][map_max_x];//�v���C���[�Ƃ̋���
	XMFLOAT3 m_InDistance[map_max_y][map_max_x];//�v���C���[�Ƃ̋���
	XMFLOAT3 m_TogeDistance[map_max_y][map_max_x];//��ɓ���
	int m_ThornDir = 0;//���̌���
	
	//�G�̃^�C�v
	enum EnemyType {
		Normal,
		Wing,
	};

	enum TouchWall {
		Right,
		Left,
		Down,
	};

	enum GoalType {
		NoGoal,
		DownGoal,
		UpGoal,
		RightGoal,
		LeftGoal
	};

	enum AirType {
		NoAir,
		AirBlock,
	};

	enum ThornDir {
		NoThorn,
		UpThorn,
		DownThorn,
		LeftThorn,
		RightThorn
	};
};