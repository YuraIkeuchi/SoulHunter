#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
using namespace std;         //  ���O��Ԏw��
//�U���G�t�F�N�g
class PlayerHealEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlayerHealEffect();

	void Initialize();//������
	void Update();//�X�V
	void Draw();//�`��
	void SetEffect(const XMFLOAT3& StartPos);//�񕜂����u�Ԃ̃G�t�F�N�g
	void EffectMove();//�G�t�F�N�g�̓���
public:
private:
	unique_ptr<Helper> helper;
	unique_ptr<IKETexture> healeffecttex;
	//�L����G�t�F�N�g
	bool m_HealStart = false;
	bool m_DeleteEffect = false;
	XMFLOAT3 m_HealPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HealColor = { 1.0f,1.0f,1.0f,0.0f };
	enum HealEffectNumber {
		Appear,
		Disappear
	};
	HealEffectNumber m_HealEffectNumber;
};