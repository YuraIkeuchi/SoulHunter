#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <map>
#include "ParticleManager.h"

struct JsonData;

using namespace std;         //  ���O��Ԏw��
class TitleObj {
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
	void Update();
	void Finalize();
	const void BackDraw();
	const void FrontDraw();
	void BirthParticle();
public:
	
private:
	//��΂ɕK�v��OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//Json�p
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	//�N���X
	unique_ptr<ParticleManager> fire;
	
};