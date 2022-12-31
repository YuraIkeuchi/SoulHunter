#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�w�i�̊�Ȃǋ��ʔw�i�̃N���X
class BackObjAlways {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();//������
	void Update();//�X�V
	const void Draw();//�`��
	void InitRock(int StageNumber);//�X�e�[�W���Ƃ̔z�u
private:
	//�萔
	static const int BackRock_Max = 11;//OBJ�̐�
private:
	//OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	IKEModel* modelground = nullptr;
	unique_ptr <IKEObject3d> objground[BackRock_Max];
	
};