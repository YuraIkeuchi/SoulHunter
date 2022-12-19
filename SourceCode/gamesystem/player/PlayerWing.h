#pragma once
#include "IKEFBXObject3d.h"
#include"IKEFBXModel.h"
#include "ObjCommon.h"
#include "VariableCommon.h"
#include "DirectXCommon.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

class PlayerWing :
public ObjCommon {
public:
	PlayerWing();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	bool Initialize() override;//������
	void Update();//�X�V
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void WingMove();
	void WingBirth();
public:

	void SetDir(int Dir) { this->m_WingDir = Dir; }
	void SetAfterScale(XMFLOAT3 m_AfterScale) { this->m_AfterScale = m_AfterScale; }
	void SetAnimation(bool m_Animation) { this->m_Animation = m_Animation; }
	void SetEaseStart(bool m_EaseStart) { this->m_EaseStart = m_EaseStart; }
	void SetFrame(float m_Frame) { this->m_Frame = m_Frame; }
private:

	bool m_EaseStart = false;
	float m_Frame = 0.0f;
	bool m_Stop = true;//�A�j���[�V�������X�g�b�v���邩
	bool m_Animation = false;
	int m_WingDir = 0;
	XMFLOAT3 m_AfterScale = { 0.0f,0.0f,0.0f };
	enum WingDir {
		LeftWing,
		RightWing,
	};
};