#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
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
	void Update();//�X�V
	const void Draw();//�`��

public:
	//�Ǝ��̊֐�
	//�_�b�V���G�t�F�N�g�̈ʒu�Z�b�g
	void DushEffectSet(const XMFLOAT3& pos);

	//�_�b�V���G�t�F�N�g�̓���
	void DushEffectMove();
private:
	
private:
	unique_ptr<Helper> helper;
	//�G�t�F�N�g�֌W
	//�_�b�V���̃G�t�F�N�g
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	XMFLOAT3 m_Position = {};//���W
	XMFLOAT3 m_Scale = {};//�傫��
	bool m_DushAlive = false;//����
	bool m_DeleteEffect = false;
};