#pragma once
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "FollowEnemy.h"
#include "ThornObj.h"
#include "Block.h"
#include "Player.h"
#include "Chest.h"
#include "Pause.h"
#include "EnemyEdit.h"
#include "PlayerSoul.h"
#include "LightGroup.h"
//�G�̊Ǘ����܂Ƃ߂��N���X
class EnemyManager {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPause(Pause* pause) { this->pause.reset(pause); }
	void SetChest(Chest* chest) { this->chest.reset(chest); }
	EnemyManager();
public:
	//���ʂ̓G
	void NormalEnemySpecity(const char* vsShaderName);
	//���̓G
	void ThornEnemySpecity(const char* vsShaderName);
	//�H�̓G
	void BoundEnemySpecity(const char* vsShaderName);
	//���̓G
	void BirdEnemySpecity(const char* vsShaderName);
	//�Ǐ]�̓G
	void FollowEnemySpecity(const char* vsShaderName);
	//����OBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csv�J��
	void OpenEnemyParam(const int StageNumber);
	//csv��������
	void SaveEnemyParam(const int StageNumber);
	//csv��т���
	void LoadEnemyParam(const int StageNumber,Player* player,Block* block, LightGroup* light);
	//�G�̐���(�g�Q�ȊO)
	void EnemyBirth(int EnemyType, Player* player, Block* block);
	//������
	void ThornBirth(bool Argment,Player* player,int Dir);
	//�X�V
	void Update(bool Move);
	//�`��
	void Draw(DirectXCommon* dxCommon);
	void ImGuiDraw();
	void MapDraw(int MapType, XMFLOAT4 MapColor);
	//�G�̍X�V
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys, bool Move);
	//�G�̕`��(�O
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//�G�̕`��(Imgui)
	void EnemyImguiDraw(std::vector<InterEnemy*> m_Enemys);
	//�G�̕`��(�}�b�v)
	void EnemyMapDraw(std::vector<InterEnemy*> m_Enemys,int MapType,XMFLOAT4 MapColor);
	//�G�̉��
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//�Z�[�u�����ۂ̐����킹
	void SaveNum();
	//�G�폜
	void DeleteEnemy();
	//�G�̈�v�f�폜
	void DeleteEnemyPop(int Type);
	//���̓G�̈�v�f�폜
	void DeleteThornPop();
	//���C�g�̃Z�b�g
	void LightSet(const int StageNumber, LightGroup* light);
	//���̃Z�b�g
	void SoulSet(Player* player, Block* block);
	//���̍X�V
	void SoulUpdate();
	//���̕`��
	void SoulDraw();
protected:
	//�萔
	static const int Soul_Max = 3;//�\�E���̍ő吔
	static const int Enemy_Max = 20;//�G�̍ő吔
private:
	//�N���X
	unique_ptr<Pause> pause = nullptr;
	unique_ptr<Chest> chest = nullptr;
	EnemyEdit* enemyedit = nullptr;
	LightGroup* lightgroup = nullptr;
	//���N���X
	PlayerSoul* normalplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* boundplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* birdplayersoul[Soul_Max][Enemy_Max];
	//�ۉe
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };
	//�U�R�G
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_BoundEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<InterEnemy*> m_FollowEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	int m_NormalEnemyCount = 0;//�U�R�G�̐�
	int m_BoundEnemyCount = 0;//�U�R�G�̐�
	int m_BirdEnemyCount = 0;//�U�R�G�̐�
	int m_FollowEnemyCount = 0;//�U�R�G�̐�
	int m_ThornObjCount = 0;//�U�R�G�̐�
	int m_EnemyCount = 0;
	std::vector<XMFLOAT3>m_EnemyPosition;
	std::vector<XMFLOAT3>m_ThornEnemyPosition;
	std::vector<XMFLOAT3>m_BoundEnemyPosition;
	std::vector<XMFLOAT3>m_BirdEnemyPosition;
	std::vector<XMFLOAT3>m_FollowEnemyPosition;
	std::vector<XMFLOAT3>m_ThornObjPosition;
	std::vector<XMFLOAT3> m_EnemyStartPos;
	std::vector<XMFLOAT3> m_ThornEnemyStartPos;
	std::vector<XMFLOAT3> m_BoundEnemyStartPos;
	std::vector<XMFLOAT3> m_BirdEnemyStartPos;
	std::vector<XMFLOAT3> m_FollowEnemyStartPos;
	std::vector<XMFLOAT3>m_ThornObjStartPos;
	std::vector<float> m_EnemyAngle;
	std::vector<float> m_SetThornEnemyPosY;
	std::vector<XMFLOAT3> m_SetThornObjPos;
	std::vector<int> m_SetThornObjDir;
	std::vector<int> m_SetThornObjTargetTimer;

	//���ʂ̓G
	std::ifstream m_EnemyFile;
	std::stringstream m_EnemyPopcom;
	std::string m_EnemyLine;
	//���̓G
	std::ifstream m_ThornEnemyFile;
	std::stringstream m_ThornEnemyPopcom;
	std::string m_ThornEnemyLine;
	//�H�̓G
	std::ifstream m_BoundEnemyFile;
	std::stringstream m_BoundEnemyPopcom;
	std::string m_BoundEnemyLine;
	//���̓G
	std::ifstream m_BirdEnemyFile;
	std::stringstream m_BirdEnemyPopcom;
	std::string m_BirdEnemyLine;
	//�Ǐ]�̓G
	std::ifstream m_FollowEnemyFile;
	std::stringstream m_FollowEnemyPopcom;
	std::string m_FollowEnemyLine;
	//����OBJ
	std::ifstream m_ThornObjFile;
	std::stringstream m_ThornObjPopcom;
	std::string m_ThornObjLine;

	int m_Enemy_Num;
	int m_ThornEnemy_Num;
	int m_BoundEnemy_Num;
	int m_BirdEnemy_Num;
	int m_FollowEnemy_Num;
	int m_ThornObj_Num;

	//���̌���
	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};
};