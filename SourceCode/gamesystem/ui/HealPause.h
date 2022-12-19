#pragma once
#include "IKESprite.h"
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�|�[�Y��ʂ̉񕜃X�L��
class HealPause {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();
	void InitPos();
	void Update();
	const void Draw();
	void ChangeSize(const int SelectDir, const int SelectNumber, XMFLOAT2 Pos);

public:
	const XMFLOAT2& GetHealPos() { return s_HealPos; }
	void SetHealPos(XMFLOAT2 s_HealPos) { this->s_HealPos = s_HealPos; }
	void SetColor(XMFLOAT4 m_Color) { this->m_Color = m_Color; }
private:
	unique_ptr<IKESprite> HealSprite;
	static XMFLOAT2 s_HealPos;
	XMFLOAT2 m_HealSize = { 96.0f,96.0f };
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
};