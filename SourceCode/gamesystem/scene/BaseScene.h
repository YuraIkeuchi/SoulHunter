#pragma once
#include "DebugCamera.h"
#include "LightGroup.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "WingEnemy.h"
#include "ResPornEnemy.h"
#include "ParticleManager.h"
#include "PostEffect.h"
#include "PlayerEffect.h"
#include "PlayerSkill.h"
#include "PlayerSoul.h"
#include "PlayerBullet.h"
#include "ParticleManager.h"
#include "Save.h"
#include "UI.h"
#include "FirstBoss.h"
#include "Block.h"
#include "Pause.h"
#include "SkillPause.h"
#include "MiniMap.h"
#include "Option.h"
#include "Message.h"
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "MapChange.h"
#include "BackObjAlways.h"
#include "BackLight.h"
#include "TutorialText.h"
#include "VolumManager.h"
#include "AllArray.h"
#include "ThornObj.h"
#include "CameraWork.h"
#include "SceneChange.h"
#include "ImGuiEditor.h"
#include "FPSManager.h"
#include "EnemyEdit.h"
#include "ObjEdit.h"
#include "Chest.h"
#include "HitStop.h"
#include <vector>
#include<fstream>
#include<string>
#include<sstream>
#include<ostream>
#include <iostream>
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class CollisionManager;
class Player;
class TouchableObject;
//�O���錾
class SceneManager;

//�V�[���C���^�[�t�F�[�X
class BaseScene
{
public:
	//���z�f�X�g���N�^
	virtual ~BaseScene() = default;

	//������
	virtual void Initialize(DirectXCommon* dxCommon) = 0;
	//�J��
	virtual void Finalize() = 0;
	//�X�V
	virtual void Update(DirectXCommon* dxCommon) = 0;
	//�`��
	virtual void Draw(DirectXCommon* dxCommon) = 0;
	//�G�f�B�^�V�[���ł��Q�[���V�[���ł��g���̂ł������ɂ���
	void NewFinish();
	//���ʏ�����
	void BaseInitialize(DirectXCommon* dxCommon);
	//�J�����̏�����
	void CameraInitialize();
	//�v���C���[�̏�����
	void PlayerInitialize();
	//�G�l�~�[�̏�����
	void EnemyInitialize();
	//�|�[�Y�֌W�̏�����
	void PauseInitialize();
	//�v���C���[�̎菕���ɂȂ���̂̏�����
	void HelperInitialize();
	//�w�iOBJ�̏�����
	void BackObjInitialize();
	//�Q�[���̎n�܂�
	void StartGame();
	// //CSV�w��
	//���ʂ̓G
	void NormalEnemySpecity(const char* vsShaderName);
	//���̓G
	void ThornEnemySpecity(const char* vsShaderName);
	//�H�̓G
	void WingEnemySpecity(const char* vsShaderName);
	//���̓G
	void BirdEnemySpecity(const char* vsShaderName);
	//����OBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csv�J��
	void OpenEnemyParam(const int& StageNumber);
	//csv��������
	void SaveEnemyParam(const int& StageNumber);
	//csv��т���
	void LoadEnemyParam(const int& StageNumber);
	//OBJ
	//csv�J��
	void OpenObjParam(const int& StageNumber);
	//csv��������
	void SaveObjParam(const int& StageNumber);
	//CSV�w��
	void ObjSpecity(const char* vsShaderName);
	//csv��т���
	void LoadObjParam(const int& StageNumber);
	//�v���C���[�ƃX�e�[�W�̓ǂݏ���
	void SaveGame();
	void LoadGame();
	//�G�̍X�V
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys);
	//�G�̕`��(�O
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//�G�̉��
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//�w�iOBj�̍X�V
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//�w�iOBJ�̕`��
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
public:
	///�Q�[���V�[���p
	DebugCamera* camera = nullptr;
	ParticleManager* particleMan = nullptr;
	//�|�X�g�G�t�F�N�g�������邩
	bool PlayPostEffect = false;
	bool m_ChangePostEffect = false;
	//�|�X�g�G�t�F�N�g�̎��
	int PostType = 1;

	enum PostType {
		Stripe,
		Blur,
		Mosaic,
	};
	//�����蔻�� ���C
	Ray ray;
	IKETexture* titleTexture = nullptr;
	//�����蔻��
	LightGroup* lightGroup = nullptr;
	XMFLOAT3 m_EyePos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m_TargetPos = { 0.0f,0.0f,0.0f };
	//�U�R�G
	//�G�f�B�^�֌W
	std::vector<std::vector<int>> map1; //�}�b�v�`�b�v(1�}�b�v)
	std::vector<std::vector<int>> map2; //�}�b�v�`�b�v(2�}�b�v)
	std::vector<std::vector<int>> map3; //�}�b�v�`�b�v(3�}�b�v)
	std::vector<std::vector<int>> map4; //�}�b�v�`�b�v(4�}�b�v)
	std::vector<std::vector<int>> map5; //�}�b�v�`�b�v(5�}�b�v)
	std::vector<std::vector<int>> map6; //�}�b�v�`�b�v(6�}�b�v)
	std::vector<std::vector<int>> bossmap; //�}�b�v�`�b�v(�{�X�}�b�v)
	std::vector<std::vector<int>> tutorialmap; //�}�b�v�`�b�v(�`���[�g���A��)
	//Player* player = nullptr;
	CollisionManager* collsionManager = nullptr;
	
	float ambientColor0[3] = { 1,1,1 };
	// �������������l
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	//�_����
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.001f,0.001f,0.001f };
	//�X�|�b�g���C�g
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,10,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 5.0f,15.0f };

	//�ۉe
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };
	//�Q�[�����[�v�������ǂ���
	static bool m_GameLoop;
	XMFLOAT3 m_PlayerPos;
	//�G�t�F�N�g�֌W
	IKESprite* BlackFilter = nullptr;
	XMFLOAT4 BlackColor = { 0.0f,0.0f,0.0f,0.0f };
	//���N���X
	PlayerSoul* normalplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* wingplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* birdplayersoul[Soul_Max][Enemy_Max];
	//�G�f�B�^�֌W
	//�G�f�B�^�̃^�C�v

	int EditorType = 0;
	enum EditorType {
		EnemySet,
		ObjSet,
		EnemyObjSet,
	};
	
	//OBJ���ǂ̋����ɒu����
	enum m_Distance {
		NearDis,
		NormalDis,
		FarDis,
	};

	//�U�R�G
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_WingEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	//�G�̎��
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
	};
	int m_NormalEnemyCount = 0;//�U�R�G�̐�
	int m_WingEnemyCount = 0;//�U�R�G�̐�
	int m_BirdEnemyCount = 0;//�U�R�G�̐�
	int m_ThornObjCount = 0;//�U�R�G�̐�
	int m_EnemyCount = 0;
	int StartStage;
	std::vector<XMFLOAT3>m_EnemyPosition;
	std::vector<XMFLOAT3>m_ThornEnemyPosition;
	std::vector<XMFLOAT3>m_WingEnemyPosition;
	std::vector<XMFLOAT3>m_BirdEnemyPosition;
	std::vector<XMFLOAT3>m_ThornObjPosition;
	std::vector<XMFLOAT3> m_EnemyStartPos;
	std::vector<XMFLOAT3> m_ThornEnemyStartPos;
	std::vector<XMFLOAT3> m_WingEnemyStartPos;
	std::vector<XMFLOAT3> m_BirdEnemyStartPos;
	std::vector<XMFLOAT3>m_ThornObjStartPos;
	std::vector<float> m_EnemyAngle;
	std::vector<float> m_SetThornEnemyPosY;
	std::vector<XMFLOAT3> m_SetThornObjPos;
	std::vector<int> m_SetThornObjDir;
	std::vector<int> m_SetThornObjTargetTimer;
	XMFLOAT3 m_PlayerStartPos;

	//�X�e�[�W
	bool StageChange = true;
	int StageNumber = 7;
	enum StageNumber {
		Map1,
		Map2,
		Map3,
		Map4,
		Map5,
		Map6,
		BossMap,
		TutoRial,
	};

	//OBJ
	//�w�ipbj
	//��
	std::vector<BackObjCommon*> m_BackRocks;
	//��
	std::vector<BackObjCommon*> m_BackBoxs;
	//����
	std::vector<BackObjCommon*> m_BackTorchs;
	//�w�iOBJ�̎��
	enum BackObjType {
		Rock,
		Box,
		Torch,
	};
	int m_BackObjCount = 0;//�U�R�G�̐�
	//new���ŏ��̈�񂾂��ɂ�����
	static bool s_New;
	//BGM�X�^�[�g
	bool BGMStart = false;
	//�e�N���X
	//�G�f�B�^
	unique_ptr<ImGuiEditor> imguieditor;
	EnemyEdit* enemyedit = nullptr;
	ObjEdit* objedit = nullptr;
	//�v���C���[
	Player* player;
	//�{�X
	InterBoss* firstboss = nullptr;
	ResPornEnemy* respornenemy = nullptr;
	static Block* block;
	//�|�X�g�G�t�F�N�g�w��
	PostEffect* postEffect = nullptr;
	PlayerEffect* playereffect = nullptr;
	PlayerBullet* playerbullet = nullptr;
	//�q�b�g�X�g�b�v
	HitStop* hitstop = false;
	//�V�[���J�ڂ̂��߂̂���
	SceneChange* scenechange = nullptr;
	MapChange* mapchange = nullptr;
	//���ʕϐ�(�N���A�������ǂ���)
	Save* save = nullptr;
	//�|�[�Y���j���[�֘A
	Pause* pause;
	SkillPause* skillpause = nullptr;
	static MiniMap* minimap;
	Option* option = nullptr;
	//�X�L��
	PlayerSkill* playerskill = nullptr;
	//��
	Chest* chest = nullptr;
	//�w�i��obj
	BackObjAlways* backobjalways = nullptr;
	BackLight* backlight = nullptr;
	//UI�֌W
	UI* ui = nullptr;
	//�`���[�g���A���̃e�L�X�g
	array<TutorialText*, Tutorial_Max> tutorialtext;
	array<int, Tutorial_Max> CollideCount;
	//�莆�N���X
	Message* message = nullptr;
	//�J�������[�N�N���X
	CameraWork* camerawork = nullptr;
	//�Z�[�u�A���h���[�h�p
	bool m_EditorSave = false;
	bool m_EditorLoad = false;
	bool m_ObjSave = false;
	bool m_ObjLoad = false;
	static bool m_GameLoad;
	//���ʂ̓G
	std::ifstream m_EnemyFile;
	std::stringstream m_EnemyPopcom;
	std::string m_EnemyLine;
	//���̓G
	std::ifstream m_ThornEnemyFile;
	std::stringstream m_ThornEnemyPopcom;
	std::string m_ThornEnemyLine;
	//�H�̓G
	std::ifstream m_WingEnemyFile;
	std::stringstream m_WingEnemyPopcom;
	std::string m_WingEnemyLine;
	//���̓G
	std::ifstream m_BirdEnemyFile;
	std::stringstream m_BirdEnemyPopcom;
	std::string m_BirdEnemyLine;
	//����OBJ
	std::ifstream m_ThornObjFile;
	std::stringstream m_ThornObjPopcom;
	std::string m_ThornObjLine;
	//�w�i��OBJ
	std::ifstream m_BackObjFile;
	std::stringstream m_BackObjPopcom;
	std::string m_BackObjLine;

	std::vector<XMFLOAT3> m_BackRockStartPos;
	std::vector<XMFLOAT3> m_BackBoxStartPos;
	std::vector<XMFLOAT3> m_BackTorchStartPos;

	std::vector<XMFLOAT3> m_BackRockStartRot;
	std::vector<XMFLOAT3> m_BackBoxStartRot;
	std::vector<XMFLOAT3> m_BackTorchStartRot;
	//�Q�[���f�[�^
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;
	int m_Enemy_Num;
	int m_ThornEnemy_Num;
	int m_WingEnemy_Num;
	int m_BirdEnemy_Num;
	int m_ThornObj_Num;
	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	//���̌���

	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};

	//�Q�[���̃��[�r�[
	int m_AppTimer = 0;
	int m_BossNumber = 0;
	enum BossNumber {
		BossApp,
		BossBattle,
	};

	bool m_SceneChange = false;
	bool m_EnemyDelete = false;
	bool m_ObjDelete = false;
};