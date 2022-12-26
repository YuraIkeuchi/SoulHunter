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
class BossAppObj {
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
	bool GetApp() { return  m_App; }
	//gettersetter
	int GetAppTimer() { return  m_AppTimer; }

	void SetApp(bool m_App) { this->m_App = m_App; }
	void SetEndApp(bool m_EndApp) { this->m_EndApp = m_EndApp; }
	void SetAppStart(bool m_AppStart) { this->m_AppStart = m_AppStart; }
	void SetAppTimer(bool m_AppTimer) { this->m_AppTimer = m_AppTimer; }
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
	bool m_AppStart = false;//�o��X�^�[�g
	int m_AppTimer = 0;//����
	bool m_EndApp = false;//�o��I��
	bool m_App = false;//�o��̊Ԃ�true
	
};