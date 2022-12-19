#pragma once
#include <DirectXMath.h>
#include "IKESprite.h"
#include "IKETexture.h"
#include "Player.h"
#include "AllArray.h"
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

	const XMFLOAT3& GetSpecialPosition() { return  m_SpecialEffectpos; }

	bool GetSpecialAlive() { return  m_SpecialAlive; }

	float GetSpecialRadius() { return  m_SpecialRadius; }
	
	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }

	void SetDushEffectPosition(const XMFLOAT3& DushEffectpos) { this->m_DushEffectpos = DushEffectpos; }

	//�Ǝ��̊֐�
	//�_�b�V���G�t�F�N�g�̈ʒu�Z�b�g
	void DushEffectSet();
	//�_���[�W���̃G�t�F�N�g�Z�b�g
	void DamageEffectSet();
	//�q�b�g�G�t�F�N�g
	void SetHitEffect();
	//�K�E�Z���̃G�t�F�N�g�Z�b�g
	void SpecialEffectSet();

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
	
	//�K�E�Z�̃G�t�F�N�g
	unique_ptr<IKETexture> SpecialEffecttexture = nullptr;
	XMFLOAT3 m_SpecialEffectpos = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT4 m_SpecialEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//�F
	XMFLOAT3 m_SpecialEffectscale = { 0.0f,0.0f,0.0f };//�傫��
	bool m_SpecialAlive = false;//����
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