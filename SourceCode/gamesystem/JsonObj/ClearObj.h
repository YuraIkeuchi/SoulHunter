#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <map>

struct JsonData;

using namespace std;         //  ���O��Ԏw��
class ClearObj {
public:
	ClearObj();
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
	//gettersetter
	const XMFLOAT3& GetTorchPos() { return  m_TorchPos; }
	void SetTorchPos(const XMFLOAT3& TorchPos) { this->m_TorchPos = TorchPos; }
private:
	//��΂ɕK�v��OBJ
	IKEModel* modeltorch = nullptr;
	unique_ptr <IKEObject3d> objtorch;
	//��΂ɕK�v��OBJ	//Json�p
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;

	//�ϐ�
	float m_OffSet = 0.01f;
	XMFLOAT3 m_TorchPos = { 0.0f,0.0f,0.0f };

};