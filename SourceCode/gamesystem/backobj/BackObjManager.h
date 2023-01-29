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
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Update();
	void Draw(DirectXCommon* dxCommon);
	void AlwaysDraw(DirectXCommon* dxCommon);
	//�w�iOBj�̍X�V
	void BackObjUpdate(std::vector<BackObjCommon*> objs);
	//�w�iOBJ�̕`��
	void BackObjDraw(std::vector<BackObjCommon*> objs, DirectXCommon* dxCommon);
	//OBJ
	//csv�J��
	void OpenObjParam(const int StageNumber);
	//csv��������
	void SaveObjParam(const int StageNumber);
	//CSV�w��
	void ObjSpecity(const char* vsShaderName);
	//csv��т���
	void LoadObjParam(const int StageNumber, Player* player, LightGroup* light);
	//���ʂ̔w�i
	//csv�J��
	void OpenBackObjAlwaysParam(const int StageNumber);
	//csV�Ăяo��
	void LoadBackObjAlways(const int StageNumber);
	//�z�u
	void ObjBirth(int Type, Player* player,XMFLOAT3 pos,XMFLOAT3 rot);
	//�w�iOBJ�̈�v�f�폜
	void DeleteObjPop(int Type);
	//�S�폜
	void ObjDelete();
	void SaveNum();
	//���C�g�̃Z�b�g
	void LightSet(const int StageNumber,LightGroup* light);
private:
	//�N���X
	ObjEdit* objedit = nullptr;
	LightGroup* lightgroup = nullptr;
	BackLight* backlight = nullptr;
	//�_����
	float pointLightPos[3] = { 0,0,0 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 15.0f,15.0f,15.0f };
	float pointLightPower[3] = { 20.0f,20.0f,20.0f };
	//�w�ipbj
	//��
	std::vector<BackObjCommon*> m_BackRocks;
	//��
	std::vector<BackObjCommon*> m_BackBoxs;
	//����
	std::vector<BackObjCommon*> m_BackTorchs;
	//�w�i��obj
	std::vector<BackObjAlways*> m_BackObjAlways;

	int m_BackObjCount = 0;//�w�iOBJ�̐�

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

	std::vector<XMFLOAT3> m_BackAlwaysStartPos;

	//���ʂ̔w�i��
	std::ifstream m_AlwaysFile;
	std::stringstream m_AlwaysPopcom;
	std::string m_AlwaysLine;
	//�Q�[���f�[�^
	std::ifstream m_GameFile;
	std::stringstream m_GamePopcom;
	std::string m_GameLine;

	int m_BackObj_Num;
	int m_BackRock_Num;
	int m_BackBox_Num;
	int m_BackTorch_Num;
	int m_BackAlways_Num;
};