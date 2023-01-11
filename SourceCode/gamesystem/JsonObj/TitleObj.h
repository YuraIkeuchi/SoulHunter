#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
#include <map>
#include "ParticleTex.h"

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

public:
	//gettersetter
	const bool& GetStopParticle() { return m_StopParticle; }
	void SetStopParticle(bool m_StopParticle) { this->m_StopParticle = m_StopParticle; }

private:
	//��΂ɕK�v��OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//Json�p
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	//�N���X
	unique_ptr<ParticleTex> particletex = nullptr;
	//�p�[�e�B�N��
	XMFLOAT3 m_ParticlePos = { 0.0f,22.0f,0.0f };
	int m_ParticleCount = 0;
	bool m_StopParticle = false;
};