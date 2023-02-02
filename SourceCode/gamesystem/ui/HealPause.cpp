#include "HealPause.h"
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
XMFLOAT2 HealPause::s_HealPos = { 600.0f,548.0f };
//初期化
void HealPause::Initialize() {
	IKESprite::LoadTexture(25, L"Resources/2d/Skill/Heal.png");
	IKESprite* HealSprite_;
	HealSprite_ = IKESprite::Create(25, { 0.0f,0.0f });
	HealSprite_->SetPosition({ 500.0f,500.0f });
	HealSprite_->SetSize(m_HealSize);
	HealSprite_->SetAnchorPoint({ 0.5f,0.5f });
	HealSprite.reset(HealSprite_);
}
//初期位置
void HealPause::InitPos() {
	s_HealPos = { 600.0f,548.0f };
}
//更新
void HealPause::Update() {
	HealSprite->SetPosition(s_HealPos);
	HealSprite->SetSize(m_HealSize);
	HealSprite->SetColor(m_Color);
}
//描画
const void HealPause::Draw() {
	/*ImGui::Begin("Heal");
	ImGui::SliderFloat("m_HealSize.x", &m_HealSize.x, 0, 1000);
	ImGui::End();*/
	IKESprite::PreDraw();
	HealSprite->Draw();
}
//大きさの変更の動き(sin波)
void HealPause::ChangeSize(const int SelectDir, const int SelectNumber, XMFLOAT2 Pos) {
	if (Pos.y == s_HealPos.y) {
		if (SelectDir == 0) {
			if (SelectNumber == 3) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_HealSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_HealSize = { 96.0f,96.0f };
			}
		}
		else {
			if (Pos.x == s_HealPos.x) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_HealSize = { (float)(sin(m_Angle2) * 16.0f) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_HealSize = { 96.0f,96.0f };
			}
		}
	}
	else {
		m_Angle = 0.0f;
		m_HealSize = { 96.0f,96.0f };
	}
}