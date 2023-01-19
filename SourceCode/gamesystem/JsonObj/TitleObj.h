#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <map>
#include "ParticleManager.h"

struct JsonData;

using namespace std;         //  名前空間指定
class TitleObj {
public:
protected:
	// DirectX::を省略
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
	//絶対に必要なOBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//Json用
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	//クラス
	unique_ptr<ParticleManager> fire;
	
};