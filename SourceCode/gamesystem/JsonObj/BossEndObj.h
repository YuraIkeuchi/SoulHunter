#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
#include <map>
#include "ParticleTex.h"
#include "IKESprite.h"
struct JsonData;

using namespace std;         //  ���O��Ԏw��
class BossEndObj {
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
	bool GetEnd() { return  m_End; }
	//gettersetter
	int GetEndTimer() { return  m_EndTimer; }

	void SetEnd(bool m_End) { this->m_End = m_End; }
	void SetEndEnd(bool m_EndEnd) { this->m_EndEnd = m_EndEnd; }
	void SetEndStart(bool m_EndStart) { this->m_EndStart = m_EndStart; }
	void SetEndTimer(bool m_EndTimer) { this->m_EndTimer = m_EndTimer; }
private:
	//��΂ɕK�v��OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	//Json�p
	JsonData* jsonData = nullptr;
	std::map<std::string, IKEModel*> models;
	std::vector<IKEObject3d*> objects;
	//�X�v���C�g
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	//���̑��ϐ�
	bool m_EndStart = false;//�o��X�^�[�g
	int m_EndTimer = 0;//����
	bool m_EndEnd = false;//�o��I��
	bool m_End = false;//�o��̊Ԃ�true

};