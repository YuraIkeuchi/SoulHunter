#pragma once
#include "LightGroup.h"
#include "DirectXCommon.h"
#include "PostEffect.h"
#include "ParticleManager.h"
#include "ResPornEnemy.h"
#include "Save.h"
#include "UI.h"
#include "FirstBoss.h"
#include "Pause.h"
#include "SkillPause.h"
#include "Option.h"
#include "MapChange.h"
#include "TutorialText.h"
#include "VolumManager.h"
#include "EnemyManager.h"
#include "BackObjManager.h"
#include "CameraWork.h"
#include "SceneChange.h"
#include "FPSManager.h"
#include "Chest.h"
using namespace std;         //  名前空間指定
//Actorクラスの既定
class BaseActor
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
	virtual ~BaseActor() = default;

	//初期化
	virtual void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) = 0;
	//開放
	virtual void Finalize() = 0;
	//更新
	virtual void Update(DirectXCommon* dxCommon, DebugCamera* camera,LightGroup* lightgroup) = 0;
	//描画
	virtual void Draw(DirectXCommon* dxCommon) = 0;
	//共通初期化
	void BaseInitialize(DirectXCommon* dxCommon);

	//エディタシーンでもゲームシーンでも使うのでこっちにする
	void NewFinish();
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
	void StartGame(LightGroup* lightgroup);
	//プレイヤーとステージの読み書き
	void SaveGame();
	void LoadGame();
protected:

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
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
	//丸影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };


	//エディタ関係
	std::vector<std::vector<int>> map1; //マップチップ(1マップ)
	std::vector<std::vector<int>> map2; //マップチップ(2マップ)
	std::vector<std::vector<int>> map3; //マップチップ(3マップ)
	std::vector<std::vector<int>> map4; //マップチップ(4マップ)
	std::vector<std::vector<int>> map5; //マップチップ(5マップ)
	std::vector<std::vector<int>> map6; //マップチップ(6マップ)
	std::vector<std::vector<int>> bossmap; //マップチップ(ボスマップ)
	std::vector<std::vector<int>> tutorialmap; //マップチップ(チュートリアル)

	//ゲームデータ
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;

		//ゲームループしたかどうか
	static bool m_GameLoop;
	//プレイヤーの位置
	XMFLOAT3 m_PlayerPos;
	//エフェクト関係
	IKESprite* BlackFilter = nullptr;
	XMFLOAT4 BlackColor = { 0.0f,0.0f,0.0f,0.0f };
	//敵を管理するクラス
	EnemyManager* enemymanager = nullptr;
	//背景OBJを管理するクラス
	BackObjManager* backmanager = nullptr;
	//敵を動かすかどうか
	bool m_MoveEnemy = false;
	XMFLOAT3 m_PlayerStartPos;
	int StartStage;
	//ステージ
	bool StageChange = true;
	int StageNumber = 7;
	//newを最初の一回だけにしたい
	static bool s_New;
	//BGMスタート
	bool BGMStart = false;
	//各クラス
	//プレイヤー
	GamePlayer* player;
	//ボス
	InterBoss* firstboss = nullptr;
	ResPornEnemy* respornenemy = nullptr;
	//ポストエフェクト指定
	unique_ptr<PostEffect> postEffect = nullptr;
	//シーン遷移のためのもの
	SceneChange* scenechange = nullptr;
	MapChange* mapchange = nullptr;
	//共通変数(クリアしたかどうか)
	unique_ptr<Save> save = nullptr;
	//ポーズメニュー関連
	Pause* pause = nullptr;
	SkillPause* skillpause = nullptr;
	Option* option = nullptr;
	//宝箱
	Chest* chest = nullptr;
	//UI関係
	UI* ui = nullptr;
	//チュートリアルのテキスト
	TutorialText* tutorialtext = nullptr;
	//カメラワーククラス
	CameraWork* camerawork = nullptr;
	//セーブアンドロード用
	bool m_EditorSave = false;
	bool m_EditorLoad = false;
	bool m_ObjSave = false;
	bool m_ObjLoad = false;
	static bool m_GameLoad;
	static bool m_NormalMode;

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
	bool PlayPostEffect = false;


	//どのシーンに行くか
	int m_SceneMigration = 0;
	//シーン先
	enum SceneMigration {
		GamePlay,
		Editor,
		Title,
	};
};