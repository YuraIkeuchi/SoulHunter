#pragma once
#include <DirectXMath.h>
#include "IKEModel.h"
#include "IkeObject3d.h"
#include <array>   
#include <memory> 
using namespace std;         //  ���O��Ԏw��
class WallAttackEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	WallAttackEffect();

	void Initialize();
	void Finalize();
	void Update(const XMFLOAT3& pos, int HitDir);
	void Draw();
	void SetEffect(const XMFLOAT3& pos,int HitDir);
private:
	//�萔
	static const int Effect_Max = 5;//�G�t�F�N�g�̐�
public:
	//getter setter
private:
	array<unique_ptr <IKEObject3d>, Effect_Max> particleobj;
	IKEModel* model = nullptr;
	//���̑��ϐ�
	//�p�[�e�B�N���ϐ�
	array<XMFLOAT3, Effect_Max> m_Pos;//���W
	array<XMFLOAT4, Effect_Max> m_Color;//�F
	array<XMFLOAT3, Effect_Max> m_Scale;//�傫��
	array<XMFLOAT3, Effect_Max> m_BoundPower;//������
	array<float, Effect_Max> m_AddScale;
	array<bool, Effect_Max> m_ScaleChange;//�傫���̕ύX
	array<bool, Effect_Max> m_Effect;//����
	array<float, Effect_Max> m_Gravity;//�d��
	bool m_DeleteEffect = false;//�G�t�F�N�g����������
};