#pragma once
#include "IKESprite.h"
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�|�[�Y��ʂ̃_�b�V���X�L��
class DushPause {
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
	const XMFLOAT2& GetDushPos() { return s_DushPos; }
	void SetDushPos(XMFLOAT2 s_DushPos) { this->s_DushPos = s_DushPos; }
	void SetColor(XMFLOAT4 m_Color) { this->m_Color = m_Color; }
private:
	unique_ptr<IKESprite> DushSprite;
	static XMFLOAT2 s_DushPos;
	XMFLOAT2 m_DushSize = { 96.0f,96.0f };
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
};