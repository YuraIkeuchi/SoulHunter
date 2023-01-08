#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include "VariableCommon.h"
#include <array>   
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class EnemyEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	EnemyEffect();

	void Initialize();
	void Finalize();
	void Update(const XMFLOAT3& pos, bool& Effect);
	void Draw();
	void SetEffect(const XMFLOAT3& pos, bool& Effect);
	void SetHitEffect(const XMFLOAT3& pos, bool& Effect);
private:
	//�萔
	static const int Effect_Max = 20;//�G�t�F�N�g�̐�
public:
	//getter setter
private:
	//�e�N�X�`��
	array<unique_ptr<IKETexture>, Effect_Max> ParticleEffect;
	unique_ptr<IKETexture> HitEffectTexture;
	//���̑��ϐ�
	//�p�[�e�B�N���ϐ�
	array<XMFLOAT3, Effect_Max> m_Pos;//���W
	array<XMFLOAT4, Effect_Max> m_Color;//�F
	array<XMFLOAT3, Effect_Max> m_Scale;//�傫��
	array<XMFLOAT3, Effect_Max> m_BoundPower;//������
	array<float, Effect_Max> m_AddScale;
	array<bool, Effect_Max> m_ScaleChange;//�傫���̕ύX
	array<bool, Effect_Max> m_Effect;//����
	bool m_DeleteEffect = false;//�G�t�F�N�g����������
	//�q�b�g�G�t�F�N�g�ϐ�
	XMFLOAT3 m_HitPos = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT3 m_HitScale = { 0.0f,0.0f,0.0f };//�傫��
	XMFLOAT4 m_HitColor = { 0.0f,0.0f,0.0f,0.0f };//�F
	bool m_HitEffect = false;//����
	bool m_DeleteHitEffect = false;//���������ǂ���
};