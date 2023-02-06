#pragma once
#include "IKESprite.h"
#include <memory> 
using namespace std;         //  名前空間指定
//ポーズ画面のダッシュスキル
class DushPause {
private:
	// DirectX::を省略
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