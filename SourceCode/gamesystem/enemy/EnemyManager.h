#pragma once
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "FollowEnemy.h"
#include "ChestEnemy.h"
#include "ThornObj.h"
#include "GamePlayer.h"
#include "Chest.h"
#include "Pause.h"
#include "EnemyEdit.h"
#include "PlayerSoul.h"
#include "LightGroup.h"
//敵の管理をまとめたクラス
class EnemyManager {
protected:
	// DirectX::を省略
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
	//普通の敵
	void NormalEnemySpecity(const char* vsShaderName);
	//棘の敵
	void ThornEnemySpecity(const char* vsShaderName);
	//羽の敵
	void BoundEnemySpecity(const char* vsShaderName);
	//鳥の敵
	void BirdEnemySpecity(const char* vsShaderName);
	//追従の敵
	void FollowEnemySpecity(const char* vsShaderName);
	//宝箱の敵
	void ChestEnemySpecity(const char* vsShaderName);
	//棘のOBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csv開く
	void OpenEnemyParam(const int StageNumber);
	//csvかきこみ
	void SaveEnemyParam(const int StageNumber);
	//csvよびだし
	void LoadEnemyParam(const int StageNumber,GamePlayer* player,LightGroup* light);
	//敵の生成(トゲ以外)
	void EnemyBirth(int EnemyType, GamePlayer* player);
	//棘生成
	void ThornBirth(bool Argment,GamePlayer* player,int Dir);
	//更新
	void Update(bool Move);
	//描画
	void Draw(DirectXCommon* dxCommon);
	void ImGuiDraw();
	void MapDraw(int MapType, XMFLOAT4 MapColor);
	//敵の更新
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys, bool Move);
	//敵の描画(前
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//敵の描画(Imgui)
	void EnemyImguiDraw(std::vector<InterEnemy*> m_Enemys);
	//敵の描画(マップ)
	void EnemyMapDraw(std::vector<InterEnemy*> m_Enemys,int MapType,XMFLOAT4 MapColor);
	//敵の解放
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//セーブした際の数合わせ
	void SaveNum();
	//敵削除
	void DeleteEnemy();
	//敵の一要素削除
	void DeleteEnemyPop(int Type);
	//棘の敵の一要素削除
	void DeleteThornPop();
	//ライトのセット
	void LightSet(const int StageNumber, LightGroup* light);
	//魂のセット
	void SoulSet(GamePlayer* player);
	//魂の更新
	void SoulUpdate();
	//魂の描画
	void SoulDraw();
protected:
	//定数
	static const int Soul_Max = 3;//ソウルの最大数
	static const int Enemy_Max = 15;//敵の最大数
private:
	//クラス
	unique_ptr<Pause> pause = nullptr;
	unique_ptr<Chest> chest = nullptr;
	EnemyEdit* enemyedit = nullptr;
	LightGroup* lightgroup = nullptr;
	//魂クラス
	array<array<PlayerSoul*,Enemy_Max>,Soul_Max> normalplayersoul;
	array<array<PlayerSoul*, Enemy_Max>,Soul_Max> boundplayersoul;
	array<array<PlayerSoul*, Enemy_Max>,Soul_Max> birdplayersoul;
	array<array<PlayerSoul*, Enemy_Max>,Soul_Max> followplayersoul;
	array<array<PlayerSoul*, Enemy_Max>,Soul_Max> chestplayersoul;
	//丸影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };
	//ザコ敵
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_BoundEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<InterEnemy*> m_FollowEnemys;
	std::vector<InterEnemy*> m_ChestEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	int m_NormalEnemyCount = 0;//ザコ敵の数
	int m_BoundEnemyCount = 0;//ザコ敵の数
	int m_BirdEnemyCount = 0;//ザコ敵の数
	int m_FollowEnemyCount = 0;//ザコ敵の数
	int m_ChestEnemyCount = 0;//ザコ敵の数
	int m_ThornObjCount = 0;//ザコ敵の数
	int m_EnemyCount = 0;
	std::vector<XMFLOAT3>m_EnemyPosition;
	std::vector<XMFLOAT3>m_ThornEnemyPosition;
	std::vector<XMFLOAT3>m_BoundEnemyPosition;
	std::vector<XMFLOAT3>m_BirdEnemyPosition;
	std::vector<XMFLOAT3>m_FollowEnemyPosition;
	std::vector<XMFLOAT3>m_ChestEnemyPosition;
	std::vector<XMFLOAT3>m_ThornObjPosition;
	std::vector<XMFLOAT3> m_EnemyStartPos;
	std::vector<XMFLOAT3> m_ThornEnemyStartPos;
	std::vector<XMFLOAT3> m_BoundEnemyStartPos;
	std::vector<XMFLOAT3> m_BirdEnemyStartPos;
	std::vector<XMFLOAT3> m_FollowEnemyStartPos;
	std::vector<XMFLOAT3> m_ChestEnemyStartPos;
	std::vector<XMFLOAT3>m_ThornObjStartPos;
	std::vector<float> m_EnemyAngle;
	std::vector<float> m_SetThornEnemyPosY;
	std::vector<XMFLOAT3> m_SetThornObjPos;
	std::vector<int> m_SetThornObjDir;
	std::vector<int> m_SetThornObjTargetTimer;

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
	//追従の敵
	std::ifstream m_FollowEnemyFile;
	std::stringstream m_FollowEnemyPopcom;
	std::string m_FollowEnemyLine;
	//宝箱の敵
	std::ifstream m_ChestEnemyFile;
	std::stringstream m_ChestEnemyPopcom;
	std::string m_ChestEnemyLine;
	//棘のOBJ
	std::ifstream m_ThornObjFile;
	std::stringstream m_ThornObjPopcom;
	std::string m_ThornObjLine;

	int m_Enemy_Num;
	int m_ThornEnemy_Num;
	int m_BoundEnemy_Num;
	int m_BirdEnemy_Num;
	int m_FollowEnemy_Num;
	int m_ChestEnemy_Num;
	int m_ThornObj_Num;

	//棘の向き
	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};
};