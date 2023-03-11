#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
using namespace std;         //  ���O��Ԏw��
//�U���G�t�F�N�g
class AttackEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	AttackEffect();

	void Initialize();//������
	void Update();//�X�V
	void Draw();//�`��
	void SetEffect(const XMFLOAT3& pos,int Dir);//�G�t�F�N�g�̏o��
	void EffectMove();//�G�t�F�N�g�̓���

public:
	//getter setter
	bool GetAttackAlive() { return  m_AttackAlive; }
private:
	unique_ptr<Helper> helper;
	//�U���G�t�F�N�g
	unique_ptr<IKETexture> AttackEffecttexture;
	XMFLOAT3 m_Position = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT4 m_Color = { 0.0f,0.0f,0.0f,1.0f };//�F
	XMFLOAT3 m_Scale = { 1.0f,1.0f,1.0f };//�傫��
	XMFLOAT4 m_BirthColor = { 1.0f,1.0f,1.0f,1.0f };//�a�������u�Ԃ̐F
	XMFLOAT3 m_BirthScale = { 0.5f,0.5f,0.5f };//�a�������u�Ԃ̑傫��
	float m_AddPower = 0.0f;//������
	bool m_AttackAlive = false;//�`�悷�邩
};