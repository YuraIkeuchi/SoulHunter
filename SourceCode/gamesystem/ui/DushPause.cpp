#include "DushPause.h"
#include "ImageManager.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//�ÓI�����o�ϐ��̎���
XMFLOAT2 DushPause::s_DushPos = { 300.0f,200.0f };
//������
void DushPause::Initialize() {
	IKESprite::LoadTexture(26, L"Resources/2d/Skill/Dush.png");
	IKESprite* DushSprite_;
	DushSprite_ = IKESprite::Create(26, { 0.0f,0.0f });
	DushSprite_->SetPosition({ 300.0f,500.0f });
	DushSprite_->SetSize(m_DushSize);
	DushSprite_->SetAnchorPoint({ 0.5f,0.5f });
	DushSprite.reset(DushSprite_);
}
//�����ʒu
void DushPause::InitPos() {
	s_DushPos = { 300.0f,200.0f };
}
//�X�V
void DushPause::Update() {
	DushSprite->SetPosition(s_DushPos);
	DushSprite->SetSize(m_DushSize);
	DushSprite->SetColor(m_Color);
}
//�`��
const void DushPause::Draw() {
	IKESprite::PreDraw();
	DushSprite->Draw();
}
//�傫���̕ύX�̓���(sin�g)
void DushPause::ChangeSize(XMFLOAT2 Pos) {
	if (s_DushPos.x == Pos.x && s_DushPos.y == Pos.y) {
		m_Angle += 2.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		//�I�����T�C�Y�������ς��
		m_DushSize = { (float)(sin(m_Angle2) * (16.0f)) + (80.0f),
			(float)(sin(m_Angle2) * 16.0f) + (80.0f) };
	}
	else {
		m_Angle = 0.0f;
		m_DushSize = { 96.0f,96.0f };
	}
}