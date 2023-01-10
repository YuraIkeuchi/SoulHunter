#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//Vector�Ŏ����Ȃ��Ă����v���C���[�G�t�F�N�g�̃N���X
class PlayerDushEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	PlayerDushEffect();

	void Initialize();//������
	void Update(const XMFLOAT3& pos, bool& Effect);//�X�V
	const void Draw();//�`��

public:

	bool GetDushAlive() { return  m_DushAlive; }

	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }

	void SetDushEffectPosition(const XMFLOAT3& DushEffectpos) { this->m_DushEffectpos = DushEffectpos; }

	//�Ǝ��̊֐�
	//�_�b�V���G�t�F�N�g�̈ʒu�Z�b�g
	void DushEffectSet(const XMFLOAT3& pos, bool& Effect);
private:
	
private:
	//�G�t�F�N�g�֌W
	//�_�b�V���̃G�t�F�N�g
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	//IKETexture* ArmPlayerEffecttexture = nullptr;
	XMFLOAT3 m_DushEffectpos = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT4 m_DushEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//�F
	XMFLOAT3 m_DushEffectscale = { 0.0f,0.0f,0.0f };//�傫��
	bool m_DushAlive = false;//����
	bool m_DeleteEffect = false;
};