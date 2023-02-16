#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory> 
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
	void Update();//�X�V
	const void Draw();//�`��

public:
	//�_���[�W���̃G�t�F�N�g�Z�b�g
	void DamageEffectSet(const XMFLOAT3& pos);
	//�G�t�F�N�g������
	void DamageEffectMove();
	//�q�b�g�G�t�F�N�g
	void HitEffectSet(const XMFLOAT3& pos);
	//�q�b�g�G�t�F�N�g����
	void HitEffectMove();
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
	//�a�������u�Ԃ̐F
	XMFLOAT4 m_BirthColor = { 1.0f,0.9f,0.8f,1.0f };
	XMFLOAT3 m_BirthDamageScale = { 0.3f,0.3f,0.3f };
	XMFLOAT3 m_BirthHitScale = { 0.1f,0.1f,0.1f };
	XMFLOAT4 m_BirthHitColor = { 1.0f,1.0f,1.0f,1.0f };
	//�G�t�F�N�g�̐����A�폜�����̂���
	bool m_HitEffect = false;
	bool m_DeleteHitEffect = false;
	bool m_DeleteEffect = false;
};