#pragma once
#include"IKESprite.h"
#include<fstream>
#include<string>
#include<sstream>
#include<ostream>
#include <iostream>
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�V�[����ς���Ƃ��̃N���X
class BossSceneChange {
public:
	BossSceneChange();
	void Update();//�X�V
	void Finalize();//���
	const void Draw();//�`��

	//void EaseScale();

	bool AddBlack(float AddPower);//�Â��Ȃ�

	bool SubBlack(float SubPower);//���邭�Ȃ�

	const float& GetScale() { return m_scale; }

	const int& GetTimer() { return m_Timer; }
	const bool& GetAddStartChange() { return m_AddStartChange; }
	const bool& GetSubStartChange() { return m_SubStartChange; }

	void SetAddStartChange(const bool& m_AddStartChange) { this->m_AddStartChange = m_AddStartChange; }
	void SetSubStartChange(const bool& m_SubStartChange) { this->m_SubStartChange = m_SubStartChange; }
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private://�ÓI�����o�ϐ�
	static XMFLOAT4 s_color;
private:
	//�V�[���؂�ւ�(�k���̕�)
	unique_ptr<IKESprite> change = nullptr;
	XMFLOAT2 m_pos = { 640.0f,360.0f, };

	float m_scale = 1.0f;
	bool m_AddStartChange = false;
	bool m_SubStartChange = false;
	int m_Timer = 0;

	int m_BlackNumber = 0;
	enum BlackColor {
		Add,
		Sub,
	};
};
