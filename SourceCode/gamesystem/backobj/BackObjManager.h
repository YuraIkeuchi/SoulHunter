#pragma once
#include "BackObjCommon.h"
#include "BackRock.h"
#include "BackBox.h"
#include "BackTorch.h"
#include "BackObjAlways.h"
#include "GamePlayer.h"
#include "ObjEdit.h"
#include "LightGroup.h"
#include "BackLight.h"
class BackObjManager {
public:
	BackObjManager();
protected:
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Update();
	void Draw(DirectXCommon* dxCommon);
	void AlwaysDraw(DirectXCommon* dxCommon);
	//îwåiOBjÇÃçXêV
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//îwåiOBJÇÃï`âÊ
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
	//OBJ
	//csväJÇ≠
	void OpenObjParam(const int StageNumber);
	//csvÇ©Ç´Ç±Ç›
	void SaveObjParam(const int StageNumber);
	//CSVéwíË
	void ObjSpecity(const char* vsShaderName);
	//csvÇÊÇ—ÇæÇµ
	void LoadObjParam(const int StageNumber, GamePlayer* player, LightGroup* light);
	//ã§í ÇÃîwåi
	//csväJÇ≠
	void OpenBackObjAlwaysParam(const int StageNumber);
	//csVåƒÇ—èoÇµ
	void LoadBackObjAlways(const int StageNumber);
	//îzíu
	void ObjBirth(int Type, GamePlayer* player,XMFLOAT3 pos,XMFLOAT3 rot);
	//îwåiOBJÇÃàÍóvëfçÌèú
	void DeleteObjPop(int Type);
	//ëSçÌèú
	void ObjDelete();
	void SaveNum();
	//ÉâÉCÉgÇÃÉZÉbÉg
	void LightSet(const int StageNumber,LightGroup* light);
private:
	//ÉNÉâÉX
	ObjEdit* objedit = nullptr;
	LightGroup* lightgroup = nullptr;
	BackLight* backlight = nullptr;
	//ì_åıåπ
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
	//îwåipbj
	//íå
	std::vector<BackObjCommon*> m_BackRocks;
	//ä‚
	std::vector<BackObjCommon*> m_BackBoxs;
	//èºñæ
	std::vector<BackObjCommon*> m_BackTorchs;
	//îwåiÇÃobj
	std::vector<BackObjAlways*> m_BackObjAlways;

	int m_BackObjCount = 0;//îwåiOBJÇÃêî

	//îwåiÇÃOBJ
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

	//ã§í ÇÃîwåiä‚
	std::ifstream m_AlwaysFile;
	std::stringstream m_AlwaysPopcom;
	std::string m_AlwaysLine;
	//ÉQÅ[ÉÄÉfÅ[É^
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;

	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	int m_BackAlways_Num;
};