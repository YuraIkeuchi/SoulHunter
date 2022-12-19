#include "CompassPause.h"
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
XMFLOAT2 CompassPause::s_CompassPos = { 450.0f,548.0f };
//������
void CompassPause::Initialize() {
	IKESprite::LoadTexture(22, L"Resources/2d/Skill/Compass.png");
	IKESprite* CompassSprite_;
	CompassSprite_ = IKESprite::Create(22, { 0.0f,0.0f });
	CompassSprite_->SetPosition({ 500.0f,500.0f });
	CompassSprite_->SetSize(m_CompassSize);
	CompassSprite_->SetAnchorPoint({ 0.5f,0.5f });
	CompassSprite.reset(CompassSprite_);
}
//�����ʒu
void CompassPause::InitPos() {
	s_CompassPos = { 450.0f,548.0f };
}
//�X�V
void CompassPause::Update() {
	CompassSprite->SetPosition(s_CompassPos);
	CompassSprite->SetSize(m_CompassSize);
	CompassSprite->SetColor(m_Color);
}
//�`��
const void CompassPause::Draw() {
	/*ImGui::Begin("Compass");
	ImGui::SliderFloat("m_CompassPos.x", &s_CompassPos.x, 0, 1000);
	ImGui::SliderFloat("m_CompassPos.y", &s_CompassPos.y, 0, 1000);
	ImGui::End();*/
	IKESprite::PreDraw();
	CompassSprite->Draw();
}
//�傫���̕ύX�̓���(sin�g)
void CompassPause::ChangeSize(const int SelectDir, const int SelectNumber, XMFLOAT2 Pos) {
	if (Pos.y == s_CompassPos.y) {
		if (SelectDir == 0) {
			if (SelectNumber == 2) {
				m_Angle += 2.0f;
				m_Angle2 = m_Angle * (3.14f / 180.0f);
				//�I�����T�C�Y�������ς��
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
				//�I�����T�C�Y�������ς��
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