#include "HealPause.h"
#include "ImageManager.h"
#include "imgui.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//�ÓI�����o�ϐ��̎���
XMFLOAT2 HealPause::s_HealPos = { 150.0f,400.0f };
//������
void HealPause::Initialize() {
	IKESprite::LoadTexture(26, L"Resources/2d/Skill/Heal.png");
	IKESprite* HealSprite_;
	HealSprite_ = IKESprite::Create(26, { 0.0f,0.0f });
	HealSprite_->SetPosition({ 500.0f,500.0f });
	HealSprite_->SetSize(m_HealSize);
	HealSprite_->SetAnchorPoint({ 0.5f,0.5f });
	HealSprite.reset(HealSprite_);
}
//�����ʒu
void HealPause::InitPos() {
	s_HealPos = { 150.0f,400.0f };
}
//�X�V
void HealPause::Update() {
	HealSprite->SetPosition(s_HealPos);
	HealSprite->SetSize(m_HealSize);
	HealSprite->SetColor(m_Color);
}
//�`��
const void HealPause::Draw() {
	/*ImGui::Begin("Heal");
	ImGui::SliderFloat("m_HealSize.x", &m_HealSize.x, 0, 1000);
	ImGui::End();*/
	IKESprite::PreDraw();
	HealSprite->Draw();
}
//�傫���̕ύX�̓���(sin�g)
void HealPause::ChangeSize(XMFLOAT2 Pos) {
	if (s_HealPos.x == Pos.x && s_HealPos.y == Pos.y) {
		m_Angle += 2.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		//�I�����T�C�Y�������ς��
		m_HealSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
			(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
	}
	else {
		m_Angle = 0.0f;
		m_HealSize = { 96.0f,96.0f };
	}
}