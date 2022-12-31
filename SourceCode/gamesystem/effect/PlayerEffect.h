#pragma once
#include <DirectXMath.h>
#include "IKESprite.h"
#include "IKETexture.h"
#include "Player.h"
#include <array>   
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//Vector�Ŏ����Ȃ��Ă����v���C���[�G�t�F�N�g�̃N���X
class PlayerEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	PlayerEffect();

	void Initialize();//������
	void Update();//�X�V
	const void Draw();//�`��

public:

	bool GetDushAlive() { return  m_DushAlive; }

	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }

	void SetDushEffectPosition(const XMFLOAT3& DushEffectpos) { this->m_DushEffectpos = DushEffectpos; }

	//�Ǝ��̊֐�
	//�_�b�V���G�t�F�N�g�̈ʒu�Z�b�g
	void DushEffectSet();
	//�_���[�W���̃G�t�F�N�g�Z�b�g
	void DamageEffectSet();
	//�q�b�g�G�t�F�N�g
	void SetHitEffect();
private:
	//�萔
	static const int DamageEffect_Max = 20;//�G�t�F�N�g�̐�
private:
	//�N���X
	unique_ptr<Player> player = nullptr;
	//�G�t�F�N�g�֌W
	//�_�b�V���̃G�t�F�N�g
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	//IKETexture* ArmPlayerEffecttexture = nullptr;
	XMFLOAT3 m_DushEffectpos = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT4 m_DushEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//�F
	XMFLOAT3 m_DushEffectscale = { 0.0f,0.0f,0.0f };//�傫��
	bool m_DushAlive = false;//����
	
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
	//�U���͈�
	float m_SpecialRadius = 0.0f;
};