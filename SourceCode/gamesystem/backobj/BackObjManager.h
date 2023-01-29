#pragma once
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"
#include "BackObjAlways.h"
#include "Player.h"
#include "ObjEdit.h"
#include "LightGroup.h"
#include "BackLight.h"
class BackObjManager {
public:
	BackObjManager();
protected:
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Update();
	void Draw(DirectXCommon* dxCommon);
	void AlwaysDraw(DirectXCommon* dxCommon);
	//”wŒiOBj‚ÌXV
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//”wŒiOBJ‚Ì•`‰æ
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
	//OBJ
	//csvŠJ‚­
	void OpenObjParam(const int StageNumber);
	//csv‚©‚«‚±‚İ
	void SaveObjParam(const int StageNumber);
	//CSVw’è
	void ObjSpecity(const char* vsShaderName);
	//csv‚æ‚Ñ‚¾‚µ
	void LoadObjParam(const int StageNumber, Player* player, LightGroup* light);
	//‹¤’Ê‚Ì”wŒi
	//csvŠJ‚­
	void OpenBackObjAlwaysParam(const int StageNumber);
	//csVŒÄ‚Ño‚µ
	void LoadBackObjAlways(const int StageNumber);
	//”z’u
	void ObjBirth(int Type, Player* player,XMFLOAT3 pos,XMFLOAT3 rot);
	//”wŒiOBJ‚Ìˆê—v‘fíœ
	void DeleteObjPop(int Type);
	//‘Síœ
	void ObjDelete();
	void SaveNum();
	//ƒ‰ƒCƒg‚ÌƒZƒbƒg
	void LightSet(const int StageNumber,LightGroup* light);
private:
	//ƒNƒ‰ƒX
	ObjEdit* objedit = nullptr;
	LightGroup* lightgroup = nullptr;
	BackLight* backlight = nullptr;
	//“_ŒõŒ¹
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
	//”wŒipbj
	//’Œ
	std::vector<BackObjCommon*> m_BackRocks;
	//Šâ
	std::vector<BackObjCommon*> m_BackBoxs;
	//¼–¾
	std::vector<BackObjCommon*> m_BackTorchs;
	//”wŒi‚Ìobj
	std::vector<BackObjAlways*> m_BackObjAlways;

	int m_BackObjCount = 0;//”wŒiOBJ‚Ì”

	//”wŒi‚ÌOBJ
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

	//‹¤’Ê‚Ì”wŒiŠâ
	std::ifstream m_AlwaysFile;
	std::stringstream m_AlwaysPopcom;
	std::string m_AlwaysLine;
	//ƒQ[ƒ€ƒf[ƒ^
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;

	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	int m_BackAlways_Num;
};