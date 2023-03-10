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
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Update();
	void Draw(DirectXCommon* dxCommon);
	void AlwaysDraw(DirectXCommon* dxCommon);
	//背景OBjの更新
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//背景OBJの描画
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
	//OBJ
	//csv開く
	void OpenObjParam(const int StageNumber);
	//csvかきこみ
	void SaveObjParam(const int StageNumber);
	//CSV指定
	void ObjSpecity(const char* vsShaderName);
	//csvよびだし
	void LoadObjParam(const int StageNumber, GamePlayer* player, LightGroup* light);
	//共通の背景
	//csv開く
	void OpenBackObjAlwaysParam(const int StageNumber);
	//csV呼び出し
	void LoadBackObjAlways(const int StageNumber);
	//配置
	void ObjBirth(int Type, GamePlayer* player,XMFLOAT3 pos,XMFLOAT3 rot);
	//背景OBJの一要素削除
	void DeleteObjPop(int Type);
	//全削除
	void ObjDelete();
	void SaveNum();
	//ライトのセット
	void LightSet(const int StageNumber,LightGroup* light);
private:
	//クラス
	ObjEdit* objedit = nullptr;
	LightGroup* lightgroup = nullptr;
	BackLight* backlight = nullptr;
	//点光源
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
	//背景pbj
	//柱
	std::vector<BackObjCommon*> m_BackRocks;
	//岩
	std::vector<BackObjCommon*> m_BackBoxs;
	//松明
	std::vector<BackObjCommon*> m_BackTorchs;
	//背景のobj
	std::vector<BackObjAlways*> m_BackObjAlways;

	int m_BackObjCount = 0;//背景OBJの数

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

	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	int m_BackAlways_Num;
};