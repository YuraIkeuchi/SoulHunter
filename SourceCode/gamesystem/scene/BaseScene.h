#pragma once
#include "DebugCamera.h"
#include "LightGroup.h"
#include "DirectXCommon.h"
#include "PostEffect.h"
#include "ParticleManager.h"
#include "ResPornEnemy.h"
#include "Save.h"
#include "UI.h"
#include "FirstBoss.h"
#include "Block.h"
#include "Pause.h"
#include "SkillPause.h"
#include "MiniMap.h"
#include "Option.h"
#include "MapChange.h"
#include "BackLight.h"
#include "TutorialText.h"
#include "VolumManager.h"
#include "EnemyManager.h"
#include "BackObjManager.h"
#include "CameraWork.h"
#include "SceneChange.h"
#include "FPSManager.h"
#include "Chest.h"
#include <vector>
#include <memory>
using namespace std;         //  ���O��Ԏw��
//�O���錾
class SceneManager;

//�V�[���C���^�[�t�F�[�X
class BaseScene
{
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

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
	//�v���C���[�ƃX�e�[�W�̓ǂݏ���
	void SaveGame();
	void LoadGame();

protected:
	//�萔
	static const int Soul_Max = 3;//�\�E���̍ő吔
	static const int Enemy_Max = 20;//�G�̍ő吔
	static const int Tutorial_Max = 5;//�`���[�g���A���̐�
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
	
	//���C�g
	LightGroup* lightGroup = nullptr;

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

	//�Q�[���f�[�^
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;

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
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
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
	//�v���C���[�̈ʒu
	XMFLOAT3 m_PlayerPos;
	//�G�t�F�N�g�֌W
	IKESprite* BlackFilter = nullptr;
	XMFLOAT4 BlackColor = { 0.0f,0.0f,0.0f,0.0f };
	//�G���Ǘ�����N���X
	EnemyManager* enemymanager = nullptr;
	//�w�iOBJ���Ǘ�����N���X
	BackObjManager* backmanager = nullptr;
	//�G�𓮂������ǂ���
	bool m_MoveEnemy = false;

	XMFLOAT3 m_PlayerStartPos;

	int StartStage;
	//�X�e�[�W
	bool StageChange = true;
	int StageNumber = 7;

	//new���ŏ��̈�񂾂��ɂ�����
	static bool s_New;
	//BGM�X�^�[�g
	bool BGMStart = false;
	//�e�N���X
	//�v���C���[
	Player* player;
	//�{�X
	InterBoss* firstboss = nullptr;
	ResPornEnemy* respornenemy = nullptr;
	static Block* block;
	//�|�X�g�G�t�F�N�g�w��
	PostEffect* postEffect = nullptr;
	
	//�q�b�g�X�g�b�v
	//�V�[���J�ڂ̂��߂̂���
	SceneChange* scenechange = nullptr;
	MapChange* mapchange = nullptr;
	//���ʕϐ�(�N���A�������ǂ���)
	Save* save = nullptr;
	//�|�[�Y���j���[�֘A
	Pause* pause = nullptr;
	SkillPause* skillpause = nullptr;
	static MiniMap* minimap;
	Option* option = nullptr;
	//��
	Chest* chest = nullptr;

	BackLight* backlight = nullptr;
	//UI�֌W
	UI* ui = nullptr;
	//�`���[�g���A���̃e�L�X�g
	array<TutorialText*, Tutorial_Max> tutorialtext;
	array<int, Tutorial_Max> CollideCount;
	//�J�������[�N�N���X
	CameraWork* camerawork = nullptr;
	//�Z�[�u�A���h���[�h�p
	bool m_EditorSave = false;
	bool m_EditorLoad = false;
	bool m_ObjSave = false;
	bool m_ObjLoad = false;
	static bool m_GameLoad;

	//�Q�[���̃��[�r�[
	int m_AppTimer = 0;
	int m_BossNumber = 0;
	enum BossNumber {
		NoBoss,
		BossApp,
		BossBattle,
		BossEnd
	};

	bool m_SceneChange = false;
	bool m_EnemyDelete = false;
	bool m_ObjDelete = false;

	//�ǂ̃V�[���ɍs����
	int m_SceneMigration = 0;
	//�V�[����
	enum SceneMigration {
		GamePlay,
		Editor,
		Title,
	};
};