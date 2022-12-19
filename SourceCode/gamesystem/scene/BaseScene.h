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
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class CollisionManager;
class Player;
class TouchableObject;
//前方宣言
class SceneManager;

//シーンインターフェース
class BaseScene
{
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
	// //CSV指定
	//普通の敵
	void NormalEnemySpecity(const char* vsShaderName);
	//棘の敵
	void ThornEnemySpecity(const char* vsShaderName);
	//羽の敵
	void WingEnemySpecity(const char* vsShaderName);
	//鳥の敵
	void BirdEnemySpecity(const char* vsShaderName);
	//棘のOBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csv開く
	void OpenEnemyParam(const int& StageNumber);
	//csvかきこみ
	void SaveEnemyParam(const int& StageNumber);
	//csvよびだし
	void LoadEnemyParam(const int& StageNumber);
	//OBJ
	//csv開く
	void OpenObjParam(const int& StageNumber);
	//csvかきこみ
	void SaveObjParam(const int& StageNumber);
	//CSV指定
	void ObjSpecity(const char* vsShaderName);
	//csvよびだし
	void LoadObjParam(const int& StageNumber);
	//プレイヤーとステージの読み書き
	void SaveGame();
	void LoadGame();
	//敵の更新
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys);
	//敵の描画(前
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//敵の解放
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//背景OBjの更新
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//背景OBJの描画
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
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
	//当たり判定 レイ
	Ray ray;
	IKETexture* titleTexture = nullptr;
	//当たり判定
	LightGroup* lightGroup = nullptr;
	XMFLOAT3 m_EyePos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m_TargetPos = { 0.0f,0.0f,0.0f };
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
	//Player* player = nullptr;
	CollisionManager* collsionManager = nullptr;
	
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
	XMFLOAT3 m_PlayerPos;
	//エフェクト関係
	IKESprite* BlackFilter = nullptr;
	XMFLOAT4 BlackColor = { 0.0f,0.0f,0.0f,0.0f };
	//魂クラス
	PlayerSoul* normalplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* wingplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* birdplayersoul[Soul_Max][Enemy_Max];
	//エディタ関係
	//エディタのタイプ

	int EditorType = 0;
	enum EditorType {
		EnemySet,
		ObjSet,
		EnemyObjSet,
	};
	
	//OBJをどの距離に置くか
	enum m_Distance {
		NearDis,
		NormalDis,
		FarDis,
	};

	//ザコ敵
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_WingEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	//敵の種類
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
	};
	int m_NormalEnemyCount = 0;//ザコ敵の数
	int m_WingEnemyCount = 0;//ザコ敵の数
	int m_BirdEnemyCount = 0;//ザコ敵の数
	int m_ThornObjCount = 0;//ザコ敵の数
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

	//ステージ
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
	//エディタ
	unique_ptr<ImGuiEditor> imguieditor;
	EnemyEdit* enemyedit = nullptr;
	ObjEdit* objedit = nullptr;
	//プレイヤー
	Player* player;
	//ボス
	InterBoss* firstboss = nullptr;
	ResPornEnemy* respornenemy = nullptr;
	static Block* block;
	//ポストエフェクト指定
	PostEffect* postEffect = nullptr;
	PlayerEffect* playereffect = nullptr;
	PlayerBullet* playerbullet = nullptr;
	//ヒットストップ
	HitStop* hitstop = false;
	//シーン遷移のためのもの
	SceneChange* scenechange = nullptr;
	MapChange* mapchange = nullptr;
	//共通変数(クリアしたかどうか)
	Save* save = nullptr;
	//ポーズメニュー関連
	Pause* pause;
	SkillPause* skillpause = nullptr;
	static MiniMap* minimap;
	Option* option = nullptr;
	//スキル
	PlayerSkill* playerskill = nullptr;
	//宝箱
	Chest* chest = nullptr;
	//背景のobj
	BackObjAlways* backobjalways = nullptr;
	BackLight* backlight = nullptr;
	//UI関係
	UI* ui = nullptr;
	//チュートリアルのテキスト
	array<TutorialText*, Tutorial_Max> tutorialtext;
	array<int, Tutorial_Max> CollideCount;
	//手紙クラス
	Message* message = nullptr;
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
	std::ifstream m_WingEnemyFile;
	std::stringstream m_WingEnemyPopcom;
	std::string m_WingEnemyLine;
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
	//ゲームデータ
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
		BossApp,
		BossBattle,
	};

	bool m_SceneChange = false;
	bool m_EnemyDelete = false;
	bool m_ObjDelete = false;
};