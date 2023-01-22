#pragma once
#include "IKEObject3d.h"
#include "IKEModel.h"
#include <memory>
#include <array>
using namespace std;         //  ���O��Ԏw��
//�Q�[���Ŏg��ImGui�̃N���X
class ImGuiEditor {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ImGuiEditor();
public:
	void Update(const XMFLOAT3& pos);
	const void ObjDraw();
	//�G�֌W��ImGui
	const void EditorImGuiDraw();
private:
	//�萔
	static const int BackObj_Max = 3;//�X�L���̐�

public://setter getter�i�����j
	//getter
	const XMFLOAT3& GetPosition() { return  m_Pos; }
	const XMFLOAT3& GetRotation() { return  m_Rot; }
	bool GetEnemyArgment() { return  m_EnemyArgment; }
	bool GetEnemyDelete() { return  m_DeleteEnemy; }
	bool GetThornObjArgment() { return  m_ThornObjArgment; }
	bool GetDeleteThornObj() { return  m_DeleteThornObj; }
	bool GetBackObjArgment() { return  m_BackObjArgment; }
	bool GetBackObjDelete() { return  m_BackObjDelete; }

	int GetEnemyType() { return   m_EnemyType; }
	int GetBackObjType() { return   m_BackObjType; }
	int GetThornDir() { return   m_ThornDir; }
	/// setter
	void SetEnemyArgment(bool m_EnemyArgment) { this->m_EnemyArgment = m_EnemyArgment; }
	void SetEnemyDelete(bool m_DeleteEnemy) { this->m_DeleteEnemy = m_DeleteEnemy; }
	void SetThornObjArgment(bool m_ThornObjArgment) { this->m_ThornObjArgment = m_ThornObjArgment; }
	void SetDeleteThornObj(bool m_DeleteThornObj) { this->m_DeleteThornObj = m_DeleteThornObj; }
	void SetBackObjArgment(bool m_BackObjArgment) { this->m_BackObjArgment = m_BackObjArgment; }
	void SetBackObjDelete(bool m_BackObjDelete) { this->m_BackObjDelete = m_BackObjDelete; }

private:
	//Obj
	IKEModel* modelRock = nullptr;
	IKEModel* modelBox = nullptr;
	IKEModel* modelTorch = nullptr;
	IKEModel* modelArg = nullptr;
	array<unique_ptr <IKEObject3d>, BackObj_Max> backobj;

	unique_ptr<IKEObject3d> argobj;
	//�ϐ�
	XMFLOAT3 m_Pos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_Rot = { 0.0f,0.0f,0.0f };

	float m_Distance = 0.0f;
	//�G�̐���
	bool m_EnemyArgment = false;
	bool m_ThornObjArgment = false;
	//�G�̍폜
	bool m_DeleteEnemy = false;
	bool m_DeleteThornObj = false;
	//�G�̎��
	int m_EnemyType = 0;
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
	};
	//�G�f�B�^�̃^�C�v
	int m_EditorType = 0;
	enum EditorType {
		EnemySet,
		ObjSet,
		EnemyObjSet,
	};

	//�w�ipbj
	bool m_BackObjArgment = false;
	bool m_BackObjDelete = false;

	//�w�iOBJ�̎��
	int m_BackObjType = 0;
	enum BackObjType {
		Rock,
		Box,
		Torch
	};
	
	//���̌���
	int m_ThornDir = 0;
	enum ThornDir {
		Up,
		Down,
		Right,
		Left
	};

	int m_DrawObjType = 0;
	enum DrawObjType {
		DrawRock,
		DrawBox,
		DrawTorch
	};
};