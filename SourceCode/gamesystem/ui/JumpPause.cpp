#include "JumpPause.h"
#include "ImageManager.h"
#include "imgui.h"
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//静的メンバ変数の実体
XMFLOAT2 JumpPause::s_JumpPos = { 300.0f,400.0f };
//初期化
void JumpPause::Initialize() {
	IKESprite::LoadTexture(27, L"Resources/2d/Skill/Jump.png");
	IKESprite* JumpSprite_;
	JumpSprite_ = IKESprite::Create(27, { 0.0f,0.0f });
	JumpSprite_->SetPosition({ 500.0f,500.0f });
	JumpSprite_->SetSize(m_JumpSize);
	JumpSprite_->SetAnchorPoint({ 0.5f,0.5f });
	JumpSprite.reset(JumpSprite_);
}
//初期位置
void JumpPause::InitPos() {
	s_JumpPos = { 300.0f,400.0f };
}
//更新
void JumpPause::Update() {
	JumpSprite->SetPosition(s_JumpPos);
	JumpSprite->SetSize(m_JumpSize);
	JumpSprite->SetColor(m_Color);
}
//描画
const void JumpPause::Draw() {
	/*ImGui::Begin("Jump");
	ImGui::SliderFloat("m_JumpSize.x", &m_JumpSize.x, 0, 1000);
	ImGui::End();*/
	IKESprite::PreDraw();
	JumpSprite->Draw();
}
//大きさの変更の動き(sin波)
void JumpPause::ChangeSize(XMFLOAT2 Pos) {
	if (s_JumpPos.x == Pos.x && s_JumpPos.y == Pos.y) {
		m_Angle += 2.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		//選択時サイズも少し変わる
		m_JumpSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
			(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
	}
	else {
		m_Angle = 0.0f;
		m_JumpSize = { 96.0f,96.0f };
	}
}