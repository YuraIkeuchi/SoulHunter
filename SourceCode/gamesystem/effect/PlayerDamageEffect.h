#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//Vector�Ŏ����Ȃ��Ă����v���C���[�G�t�F�N�g�̃N���X
class PlayerDamageEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	PlayerDamageEffect();

	void Initialize();//������
	void Update(const XMFLOAT3& pos, bool& Effect);//�X�V
	const void Draw();//�`��

public:
	//�_���[�W���̃G�t�F�N�g�Z�b�g
	void DamageEffectSet(const XMFLOAT3& pos, bool& Effect);
	//�q�b�g�G�t�F�N�g
	void SetHitEffect(const XMFLOAT3& pos, bool& Effect);
private:
	//�萔
	static const int DamageEffect_Max = 20;//�G�t�F�N�g�̐�
private:
	//�_���[�W��
	array<unique_ptr<IKETexture>, DamageEffect_Max> damagetex;
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectpos;//���W
	array<XMFLOAT4, DamageEffect_Max> m_DamageEffectcolor;//�F
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectscale;//�傫��
	array<XMFLOAT3, DamageEffect_Max> m_BoundPower;//������
	array<bool, DamageEffect_Max> m_DamageAlive;//����
	//�q�b�g�G�t�F�N�g
	unique_ptr<IKETexture> HitEffectTexture;
	//�q�b�g�G�t�F�N�g�ϐ�
	XMFLOAT3 m_HitPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HitScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
	bool m_HitEffect = false;
	bool m_DeleteHitEffect = false;
	bool m_DeleteEffect = false;
};