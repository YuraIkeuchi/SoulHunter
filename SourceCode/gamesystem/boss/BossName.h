#pragma once
#include"IKESprite.h"
#include "AllArray.h"
#include "VariableCommon.h" 
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class BossName {
public:
	BossName();
	//�X�V
	void Update();
	//�`��
	const void Draw();
	//���X�ɕ������o�Ă���
	void AddColor();
	//���X�ɕ�����������
	void SubColor();

	//setter
	void SetAddStartChange(bool m_AddStartChange) { this->m_AddStartChange = m_AddStartChange; }
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	
private:
	//�X�v���C�g
	unique_ptr<IKESprite> bossname = nullptr;

	//�ϐ�
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,0.0f };//�F
	XMFLOAT2 m_pos = { 640.0f,360.0f, };//���W
	bool m_AddStartChange = false;//�F�̉��Z�t���O
	bool m_DrawName = true;//�`�悷�邩�ǂ���
	int m_AlphaNumber = 0;//���ߓx�����邩�����邩
	enum Alpha {
		Add,
		Sub,
	};

	//�}�W�b�N�i���o�[�����̂��߂̕ϐ�
	const float m_ChangeTexFrame = 0.01f;//�e�L�X�g�̓��ߓx
};

