#include "LibraPause.h"
#include "ImageManager.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//�ÓI�����o�ϐ��̎���
XMFLOAT2 LibraPause::s_LibraPos = { 150.0f,200.0f };
//������
void LibraPause::Initialize() {
	IKESprite::LoadTexture(27, L"Resources/2d/Skill/Libra.png");
	IKESprite* LibraSprite_;
	LibraSprite_ = IKESprite::Create(27, { 0.0f,0.0f });
	LibraSprite_->SetSize(m_LibraSize);
	LibraSprite_->SetPosition({ 100.0f,500.0f });
	LibraSprite_->SetAnchorPoint({ 0.5f,0.5f });
	LibraSprite.reset(LibraSprite_);
}
//�����ʒu
void LibraPause::InitPos() {
	s_LibraPos = { 150.0f,200.0f };
}
//�X�V
void LibraPause::Update() {
	LibraSprite->SetPosition(s_LibraPos);
	LibraSprite->SetSize(m_LibraSize);
	LibraSprite->SetColor(m_Color);
}
//�`��
const void LibraPause::Draw() {
	IKESprite::PreDraw();
	LibraSprite->Draw();
}
//�傫���̕ύX�̓���(sin�g)
void LibraPause::ChangeSize(XMFLOAT2 Pos) {
	if (s_LibraPos.x == Pos.x && s_LibraPos.y == Pos.y) {
		m_Angle += 2.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		//�I�����T�C�Y�������ς��
		m_LibraSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
			(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
	}
	else {
		m_Angle = 0.0f;
		m_LibraSize = { 96.0f,96.0f };
	}
}