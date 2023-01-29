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
//“G‚ÌŠÇ—‚ğ‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
class EnemyManager {
protected:
	// DirectX::‚ğÈ—ª
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
	//•’Ê‚Ì“G
	void NormalEnemySpecity(const char* vsShaderName);
	//™‚Ì“G
	void ThornEnemySpecity(const char* vsShaderName);
	//‰H‚Ì“G
	void BoundEnemySpecity(const char* vsShaderName);
	//’¹‚Ì“G
	void BirdEnemySpecity(const char* vsShaderName);
	//’Ç]‚Ì“G
	void FollowEnemySpecity(const char* vsShaderName);
	//™‚ÌOBJ
	void ThornObjSpecity(const char* vsShaderName);
	//csvŠJ‚­
	void OpenEnemyParam(const int StageNumber);
	//csv‚©‚«‚±‚İ
	void SaveEnemyParam(const int StageNumber);
	//csv‚æ‚Ñ‚¾‚µ
	void LoadEnemyParam(const int StageNumber,Player* player,Block* block, LightGroup* light);
	//“G‚Ì¶¬(ƒgƒQˆÈŠO)
	void EnemyBirth(int EnemyType, Player* player, Block* block);
	//™¶¬
	void ThornBirth(bool Argment,Player* player,int Dir);
	//XV
	void Update(bool Move);
	//•`‰æ
	void Draw(DirectXCommon* dxCommon);
	void ImGuiDraw();
	void MapDraw(int MapType, XMFLOAT4 MapColor);
	//“G‚ÌXV
	void EnemyUpdate(std::vector<InterEnemy*> m_Enemys, bool Move);
	//“G‚Ì•`‰æ(‘O
	void EnemyDraw(std::vector<InterEnemy*> m_Enemys, DirectXCommon* dxCommon);
	//“G‚Ì•`‰æ(Imgui)
	void EnemyImguiDraw(std::vector<InterEnemy*> m_Enemys);
	//“G‚Ì•`‰æ(ƒ}ƒbƒv)
	void EnemyMapDraw(std::vector<InterEnemy*> m_Enemys,int MapType,XMFLOAT4 MapColor);
	//“G‚Ì‰ğ•ú
	void EnemyFinalize(std::vector<InterEnemy*> m_Enemys);
	//ƒZ[ƒu‚µ‚½Û‚Ì”‡‚í‚¹
	void SaveNum();
	//“Gíœ
	void DeleteEnemy();
	//“G‚Ìˆê—v‘fíœ
	void DeleteEnemyPop(int Type);
	//™‚Ì“G‚Ìˆê—v‘fíœ
	void DeleteThornPop();
	//ƒ‰ƒCƒg‚ÌƒZƒbƒg
	void LightSet(const int StageNumber, LightGroup* light);
	//°‚ÌƒZƒbƒg
	void SoulSet(Player* player, Block* block);
	//°‚ÌXV
	void SoulUpdate();
	//°‚Ì•`‰æ
	void SoulDraw();
protected:
	//’è”
	static const int Soul_Max = 3;//ƒ\ƒEƒ‹‚ÌÅ‘å”
	static const int Enemy_Max = 20;//“G‚ÌÅ‘å”
private:
	//ƒNƒ‰ƒX
	unique_ptr<Pause> pause = nullptr;
	unique_ptr<Chest> chest = nullptr;
	EnemyEdit* enemyedit = nullptr;
	LightGroup* lightgroup = nullptr;
	//°ƒNƒ‰ƒX
	PlayerSoul* normalplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* boundplayersoul[Soul_Max][Enemy_Max];
	PlayerSoul* birdplayersoul[Soul_Max][Enemy_Max];
	//ŠÛ‰e
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,2,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.8f };
	//ƒUƒR“G
	std::vector<InterEnemy*> m_Enemys;
	std::vector<InterEnemy*> m_ThornEnemys;
	std::vector<InterEnemy*> m_BoundEnemys;
	std::vector<InterEnemy*> m_BirdEnemys;
	std::vector<InterEnemy*> m_FollowEnemys;
	std::vector<ThornObj*> m_ThornObjs;

	int m_NormalEnemyCount = 0;//ƒUƒR“G‚Ì”
	int m_BoundEnemyCount = 0;//ƒUƒR“G‚Ì”
	int m_BirdEnemyCount = 0;//ƒUƒR“G‚Ì”
	int m_FollowEnemyCount = 0;//ƒUƒR“G‚Ì”
	int m_ThornObjCount = 0;//ƒUƒR“G‚Ì”
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

	//•’Ê‚Ì“G
	std::ifstream m_EnemyFile;
	std::stringstream m_EnemyPopcom;
	std::string m_EnemyLine;
	//™‚Ì“G
	std::ifstream m_ThornEnemyFile;
	std::stringstream m_ThornEnemyPopcom;
	std::string m_ThornEnemyLine;
	//‰H‚Ì“G
	std::ifstream m_BoundEnemyFile;
	std::stringstream m_BoundEnemyPopcom;
	std::string m_BoundEnemyLine;
	//’¹‚Ì“G
	std::ifstream m_BirdEnemyFile;
	std::stringstream m_BirdEnemyPopcom;
	std::string m_BirdEnemyLine;
	//’Ç]‚Ì“G
	std::ifstream m_FollowEnemyFile;
	std::stringstream m_FollowEnemyPopcom;
	std::string m_FollowEnemyLine;
	//™‚ÌOBJ
	std::ifstream m_ThornObjFile;
	std::stringstream m_ThornObjPopcom;
	std::string m_ThornObjLine;

	int m_Enemy_Num;
	int m_ThornEnemy_Num;
	int m_BoundEnemy_Num;
	int m_BirdEnemy_Num;
	int m_FollowEnemy_Num;
	int m_ThornObj_Num;

	//™‚ÌŒü‚«
	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};
};