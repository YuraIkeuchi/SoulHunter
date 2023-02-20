#pragma once
#include "IKESprite.h"
#include <memory> 
using namespace std;         //  ���O��Ԏw��
//�|�[�Y��ʂ̃R���p�X�X�L��
class JumpPause {
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
	void ChangeSize(XMFLOAT2 Pos);

public:
	const XMFLOAT2& GetJumpPos() { return s_JumpPos; }
	void SetJumpPos(XMFLOAT2 s_JumpPos) { this->s_JumpPos = s_JumpPos; }
	void SetColor(XMFLOAT4 m_Color) { this->m_Color = m_Color; }
private:
	unique_ptr<IKESprite> JumpSprite;
	static XMFLOAT2 s_JumpPos;
	XMFLOAT2 m_JumpSize = { 96.0f,96.0f };
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
};