#pragma once
#include "IKESprite.h"
#include "VolumManager.h"
#include "Audio.h"
#include "AllArray.h"
#include <array>   
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�I�v�V������ʂ̃N���X
class Option {
public:
	Option();
	void Initialize();//������
	void Update();//�X�V
	void Finalize();//���
	const void Draw();//�`��
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter
	bool GetReturnOption() { return m_ReturnOption; }
	bool GetVolumChange() { return m_VolumChange; }
	//setter
	void SetReturnOption(bool m_ReturnOption) { this->m_ReturnOption = m_ReturnOption; }
	void SetVolumChange(bool m_VolumChange) { this->m_VolumChange = m_VolumChange; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
private:
	//�N���X
	//�X�v���C�g
	array<unique_ptr<IKESprite>, Option_Max> OptionSprite;
	array<unique_ptr<IKESprite>, Option_Max> VolumBarSprite;
	//�ϐ�
	bool m_ReturnOption = false;//�I�v�V�������j���[�����
	int VolumSelect = 0;//SE��BGM��
	enum VolumSelect {
		BGM,
		SE,
	};
	//����
	float m_BGMVolum;
	float m_SEVolum;
	bool m_VolumChange = false;
	
	//�X�v���C�g�̕ϐ�
	array<XMFLOAT2,Option_Max> VolumSpriteSize;
	XMFLOAT4 m_OptionColor = { 1.0f,1.0f,1.0f,0.0f };
	int m_ColorChangeType = 0;
	enum ChangeType {
		No,
		Add,
		Sub,
	};
};