#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory> 
using namespace std;         //  ���O��Ԏw��

//�莆��Z�[�u�|�C���g�Ȃǖڗ����������ꏊ�ɏo���G�t�F�N�g
class MarkEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	MarkEffect();

	void Initialize();//������
	void Finalize();//���
	void Update(XMFLOAT3 StartPos);//�X�V
	void Draw();//�`��
	void EffectMove(XMFLOAT3 StartPos);//�G�t�F�N�g�̓���
private:
	//�e�N�X�`��
	unique_ptr<IKETexture> markEffect;
	//�ϐ�
	XMFLOAT3 m_Position = { 0.0f,0.0f,0.0f };//���W
	XMFLOAT3 m_Scale = { 0.0f,0.0f,0.0f };//�傫��
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };//�F

	float m_Frame = 0.0f;//�t���[��
	bool a = true;
};