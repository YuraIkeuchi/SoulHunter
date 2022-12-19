#include "CompassPause.h"
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
XMFLOAT2 CompassPause::s_CompassPos = { 450.0f,548.0f };
//初期化
void CompassPause::Initialize() {
	IKESprite::LoadTexture(22, L"Resources/2d/Skill/Compass.png");
	IKESprite* CompassSprite_;
	CompassSprite_ = IKESprite::Create(22, { 0.0f,0.0f });
	CompassSprite_->SetPosition({ 500.0f,500.0f });
	CompassSprite_->SetSize(m_CompassSize);
	CompassSprite_->SetAnchorPoint({ 0.5f,0.5f });
	CompassSprite.reset(CompassSprite_);
}
//初期位置
void CompassPause::InitPos() {
	s_CompassPos = { 450.0f,548.0f };
}
//更新
void CompassPause::Update() {
	CompassSprite->SetPosition(s_CompassPos);
	CompassSprite->SetSize(m_CompassSize);
	CompassSprite->SetColor(m_Color);
}
//描画
const void CompassPause::Draw() {
	/*ImGui::Begin("Compass");
	ImGui::SliderFloat("m_CompassPos.x", &s_CompassPos.x, 0, 1000);
	ImGui::SliderFloat("m_CompassPos.y", &s_CompassPos.y, 0, 1000);
	ImGui::End();*/
	IKESprite::PreDraw();
	CompassSprite->Draw();
}
//大きさの変更の動き(sin波)
void CompassPause::ChangeSize(const int SelectDir, const int SelectNumber, XMFLOAT2 Pos) {
	if (Pos.y == s_CompassPos.y) {
		if (SelectDir == 0) {
			if (SelectNumber == 2) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_CompassSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_CompassSize = { 96.0f,96.0f };
			}
		}
		else {
			if (Pos.x == s_CompassPos.x) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//選択時サイズも少し変わる
				m_CompassSize = { (float)(sin(m_Angle2) * 16.0f) + (80.0f),
					(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
			}
			else {
				m_Angle = 0.0f;
				m_CompassSize = { 96.0f,96.0f };
			}
		}
	}
	else {
		m_Angle = 0.0f;
		m_CompassSize = { 96.0f,96.0f };
	}
}