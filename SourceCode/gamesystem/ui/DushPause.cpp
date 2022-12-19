#include "DushPause.h"
#include "ImageManager.h"
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//静的メンバ変数の実体
XMFLOAT2 DushPause::s_DushPos = { 300.0f,548.0f };
//初期化
void DushPause::Initialize() {
	IKESprite::LoadTexture(23, L"Resources/2d/Skill/Dush.png");
	IKESprite* DushSprite_;
	DushSprite_ = IKESprite::Create(23, { 0.0f,0.0f });
	DushSprite_->SetPosition({ 300.0f,500.0f });
	DushSprite_->SetSize(m_DushSize);
	DushSprite_->SetAnchorPoint({ 0.5f,0.5f });
	DushSprite.reset(DushSprite_);
}
//初期位置
void DushPause::InitPos() {
	s_DushPos = { 300.0f,548.0f };
}
//更新
void DushPause::Update() {
	DushSprite->SetPosition(s_DushPos);
	DushSprite->SetSize(m_DushSize);
	DushSprite->SetColor(m_Color);
}
//描画
const void DushPause::Draw() {
	IKESprite::PreDraw();
	DushSprite->Draw();
}
//大きさの変更の動き(sin波)
void DushPause::ChangeSize(const int SelectDir, const int SelectNumber, XMFLOAT2 Pos) {
	if (Pos.y == s_DushPos.y) {
		if (SelectDir == 0) {
			if (SelectNumber == 1) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_DushSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_DushSize = { 96.0f,96.0f };
			}
		}
		else {
			if (Pos.x == s_DushPos.x) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_DushSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_DushSize = { 96.0f,96.0f };
			}
		}
	}
	else {
		m_Angle = 0.0f;
		m_DushSize = { 96.0f,96.0f };
	}
}