#pragma once
#include "DebugCamera.h"
#include "LightGroup.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "ResPornEnemy.h"
#include "ParticleManager.h"
#include "PostEffect.h"
#include "PlayerSkill.h"
#include "Save.h"
#include "UI.h"
#include "FirstBoss.h"
#include "Block.h"
#include "Pause.h"
#include "SkillPause.h"
#include "MiniMap.h"
#include "Option.h"
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"
#include "MapChange.h"
#include "BackObjAlways.h"
#include "BackLight.h"
#include "TutorialText.h"
#include "VolumManager.h"
#include "ThornObj.h"
#include "CameraWork.h"
#include "SceneChange.h"
#include "FPSManager.h"
#include "Chest.h"
#include "HitStop.h"
#include <vector>
#include <memory>
using namespace std;         //  名前空間指定
//前方宣言
class SceneManager;

//シーンインターフェース
class BaseScene
{
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//仮想デストラクタ
	virtual ~BaseScene() = default;

	//初期化
	virtual void Initialize(DirectXCommon* dxCommon) = 0;
	//開放
	virtual void Finalize() = 0;
	//更新
	virtual void Update(DirectXCommon* dxCommon) = 0;
	//描画
	virtual void Draw(DirectXCommon* dxCommon) = 0;
	//エディタシーンでもゲームシーンでも使うのでこっちにする
	void NewFinish();
	//共通初期化
	void BaseInitialize(DirectXCommon* dxCommon);
	//カメラの初期化
	void CameraInitialize();
	//プレイヤーの初期化
	void PlayerInitialize();
	//エネミーの初期化
	void EnemyInitialize();
	//ポーズ関係の初期化
	void PauseInitialize();
	//プレイヤーの手助けになるものの初期化
	void HelperInitialize();
	//背景OBJの初期化
	void BackObjInitialize();
	//ゲームの始まり
	void StartGame();
	//csv関係(敵)
	//普通の敵
	void NormalEnemySpecity(const char* vsShaderName);
	//棘の敵
	void ThornEnemySpecity(const char* vsShaderName);
	//羽の敵
	void BoundEnemySpecity(const char* vsShaderName);
	//鳥の敵
	void BirdEnemySpecity(const char* vsShaderName);
	//棘のOBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csv開く
	void OpenEnemyParam(const int StageNumber);
	//csvかきこみ
	void SaveEnemyParam(const int StageNumber);
	//csvよびだし
	void LoadEnemyParam(const int StageNumber);
	//OBJ
	//csv開く
	void OpenObjParam(const int StageNumber);
	//csvかきこみ
	void SaveObjParam(const int StageNumber);
	//CSV指定
	void ObjSpecity(const char* vsShaderName);
	//csvよびだし
	void LoadObjParam(const int StageNumber);
	//共通の背景
	//csv開く
	void OpenBackObjAlwaysParam(const int StageNumber);
	//csV呼び出し
	void LoadBackObjAlways(const int StageNumber);
	//プレイヤーとステージの読み書き
	void SaveGame();
	void LoadGame();
	void ReloadEnemy();
	//敵の更新
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys);
	//敵の描画(前
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//敵の描画(前
	void EnemyMapDraw(std::vector<InterEnemy*> m_Enemys);
	//敵の解放
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//背景OBjの更新
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//背景OBJの描画
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
	
protected:
	//定数
	static const int Soul_Max = 3;//ソウルの最大数
	static const int Enemy_Max = 20;//敵の最大数
	static const int Tutorial_Max = 5;//チュートリアルの数
public:
	///ゲームシーン用
	DebugCamera* camera = nullptr;
	ParticleManager* particleMan = nullptr;
	//ポストエフェクトをかけるか
	bool PlayPostEffect = false;
	bool m_ChangePostEffect = false;
	//ポストエフェクトの種類
	int PostType = 1;

	enum PostType {
		Stripe,
		Blur,
		Mosaic,
	};
	
	//ライト
	LightGroup* lightGroup = nullptr;

	//ザコ敵
	//エディタ関係
	std::vector<std::vector<int>> map1; //マップチップ(1マップ)
	std::vector<std::vector<int>> map2; //マップチップ(2マップ)
	std::vector<std::vector<int>> map3; //マップチップ(3マップ)
	std::vector<std::vector<int>> map4; //マップチップ(4マップ)
	std::vector<std::vector<int>> map5; //マップチップ(5マップ)
	std::vector<std::vector<int>> map6; //マップチップ(6マップ)
	std::vector<std::vector<int>> bossmap; //マップチップ(ボスマップ)
	std::vector<std::vector<int>> tutorialmap; //マップチップ(チュートリアル)

	float ambientColor0[3] = { 1,1,1 };
	// 光線方向初期値
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	//点光源
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.001f,0.001f,0.001f };
	//スポットライト
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,10,0 };
	float spotLightColor[3] = { 1,1,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 5.0f,15.0f };

	//丸影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };
	//ゲームループしたかどうか
	static bool m_GameLoop;
	//プレイヤーの位置
	XMFLOAT3 m_PlayerPos;
	//エフェクト関係
	IKESprite* BlackFilter = nullptr;
	XMFLOAT4 BlackColor = { 0.0f,0.0f,0.0f,0.0f };
	//エディタ関係

	//敵を動かすかどうか
	bool m_MoveEnemy = false;

	//ザコ敵
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_BoundEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	//敵の種類
	enum EnemyType {
		Normal,
		Thorn,
		Bound,
		Bird,
	};
	int m_NormalEnemyCount = 0;//ザコ敵の数
	int m_BoundEnemyCount = 0;//ザコ敵の数
	int m_BirdEnemyCount = 0;//ザコ敵の数
	int m_ThornObjCount = 0;//ザコ敵の数
	int m_EnemyCount = 0;
	int StartStage;
	std::vector<XMFLOAT3>m_EnemyPosition;
	std::vector<XMFLOAT3>m_ThornEnemyPosition;
	std::vector<XMFLOAT3>m_BoundEnemyPosition;
	std::vector<XMFLOAT3>m_BirdEnemyPosition;
	std::vector<XMFLOAT3>m_ThornObjPosition;
	std::vector<XMFLOAT3> m_EnemyStartPos;
	std::vector<XMFLOAT3> m_ThornEnemyStartPos;
	std::vector<XMFLOAT3> m_BoundEnemyStartPos;
	std::vector<XMFLOAT3> m_BirdEnemyStartPos;
	std::vector<XMFLOAT3>m_ThornObjStartPos;
	std::vector<float> m_EnemyAngle;
	std::vector<float> m_SetThornEnemyPosY;
	std::vector<XMFLOAT3> m_SetThornObjPos;
	std::vector<int> m_SetThornObjDir;
	std::vector<int> m_SetThornObjTargetTimer;
	XMFLOAT3 m_PlayerStartPos;

	//ステージ
	bool StageChange = true;
	int StageNumber = 7;

	//OBJ
	//背景pbj
	//柱
	std::vector<BackObjCommon*> m_BackRocks;
	//岩
	std::vector<BackObjCommon*> m_BackBoxs;
	//松明
	std::vector<BackObjCommon*> m_BackTorchs;
	//背景OBJの種類
	enum BackObjType {
		Rock,
		Box,
		Torch,
	};
	int m_BackObjCount = 0;//ザコ敵の数
	//newを最初の一回だけにしたい
	static bool s_New;
	//BGMスタート
	bool BGMStart = false;
	//各クラス
	//プレイヤー
	Player* player;
	//ボス
	InterBoss* firstboss = nullptr;
	ResPornEnemy* respornenemy = nullptr;
	static Block* block;
	//ポストエフェクト指定
	PostEffect* postEffect = nullptr;
	
	//ヒットストップ
	HitStop* hitstop = false;
	//シーン遷移のためのもの
	SceneChange* scenechange = nullptr;
	MapChange* mapchange = nullptr;
	//共通変数(クリアしたかどうか)
	Save* save = nullptr;
	//ポーズメニュー関連
	Pause* pause = nullptr;
	SkillPause* skillpause = nullptr;
	static MiniMap* minimap;
	Option* option = nullptr;
	//スキル
	PlayerSkill* playerskill = nullptr;
	//宝箱
	Chest* chest = nullptr;
	//背景のobj
	std::vector<BackObjAlways*> m_BackObjAlways;
	BackLight* backlight = nullptr;
	//UI関係
	UI* ui = nullptr;
	//チュートリアルのテキスト
	array<TutorialText*, Tutorial_Max> tutorialtext;
	array<int, Tutorial_Max> CollideCount;
	//カメラワーククラス
	CameraWork* camerawork = nullptr;
	//セーブアンドロード用
	bool m_EditorSave = false;
	bool m_EditorLoad = false;
	bool m_ObjSave = false;
	bool m_ObjLoad = false;
	static bool m_GameLoad;
	//普通の敵
	std::ifstream m_EnemyFile;
	std::stringstream m_EnemyPopcom;
	std::string m_EnemyLine;
	//棘の敵
	std::ifstream m_ThornEnemyFile;
	std::stringstream m_ThornEnemyPopcom;
	std::string m_ThornEnemyLine;
	//羽の敵
	std::ifstream m_BoundEnemyFile;
	std::stringstream m_BoundEnemyPopcom;
	std::string m_BoundEnemyLine;
	//鳥の敵
	std::ifstream m_BirdEnemyFile;
	std::stringstream m_BirdEnemyPopcom;
	std::string m_BirdEnemyLine;
	//棘のOBJ
	std::ifstream m_ThornObjFile;
	std::stringstream m_ThornObjPopcom;
	std::string m_ThornObjLine;
	//背景のOBJ
	std::ifstream m_BackObjFile;
	std::stringstream m_BackObjPopcom;
	std::string m_BackObjLine;

	std::vector<XMFLOAT3> m_BackRockStartPos;
	std::vector<XMFLOAT3> m_BackBoxStartPos;
	std::vector<XMFLOAT3> m_BackTorchStartPos;

	std::vector<XMFLOAT3> m_BackRockStartRot;
	std::vector<XMFLOAT3> m_BackBoxStartRot;
	std::vector<XMFLOAT3> m_BackTorchStartRot;

	std::vector<XMFLOAT3> m_BackAlwaysStartPos;

	//共通の背景岩
	std::ifstream m_AlwaysFile;
	std::stringstream m_AlwaysPopcom;
	std::string m_AlwaysLine;
	//ゲームデータ
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;
	int m_Enemy_Num;
	int m_ThornEnemy_Num;
	int m_BoundEnemy_Num;
	int m_BirdEnemy_Num;
	int m_ThornObj_Num;
	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	int m_BackAlways_Num;
	//棘の向き
	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};

	//ゲームのムービー
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

	//どのシーンに行くか
	int m_SceneMigration = 0;
	//シーン先
	enum SceneMigration {
		GamePlay,
		Editor,
		Title,
	};
};