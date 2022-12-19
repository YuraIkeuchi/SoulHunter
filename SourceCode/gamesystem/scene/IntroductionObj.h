#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
#include <map>
#include "ParticleTex.h"

struct JsonData;

using namespace std;         //  ���O��Ԏw��
class IntroductionObj {
public:
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();
	void Update(int Timer);
	void Finalize();
	const void BackDraw();
	const void FrontDraw();

public:

private:
	//��΂ɕK�v��OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//��΂ɕK�v��OBJ	//Json�p
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	std::vector<IKEObject3d*> fogobjects;
	std::vector<IKEObject3d*> groundobjects;
	
	float m_OffSet = 0.01f;
};