#pragma once
#include "IKETexture.h"
#include <memory>
using namespace std;         //  ���O��Ԏw��
//�w�i�̌��e�N�X�`���p�̃N���X
class BackLight {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();//������
	void Update();//�X�V
	const void Draw();//�`��

private:
	//�e�N�X�`��
	unique_ptr<IKETexture> backlightTex = nullptr;
	//�ϐ�
	XMFLOAT3 m_BackLightPos = { 139.0f,-120.0f,200.0f };
	XMFLOAT3 m_BackLightScale = { 15.0f,70.0f,1.0f };
};