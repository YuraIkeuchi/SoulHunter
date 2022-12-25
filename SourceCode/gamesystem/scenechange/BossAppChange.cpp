#include "BossAppChange.h"
#include "ImageManager.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 BossAppChange::s_color = { 1.0f,1.0f,1.0f,0.0f };

BossAppChange::BossAppChange() {
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change.reset(change_);
}

void BossAppChange::Update() {
	change->SetColor(s_color);
}

const void BossAppChange::Draw() {
	ImGui::Begin("filter");
	ImGui::Text("%d", m_AddStartChange);
	ImGui::Text("%d", m_SubStartChange);
	ImGui::Text("%f", s_color.w);
	ImGui::End();
	IKESprite::PreDraw();
	change->Draw();
}

void BossAppChange::Finalize() {

}

bool BossAppChange::AddBlack(float AddPower) {
	if (m_AddStartChange) {
		if (s_color.w < 1.0f) {
			s_color.w += AddPower;
		}
		else {
			m_AddStartChange = false;
			s_color.w = 1.0f;
			return true;
		}
	}

	return false;
}

bool BossAppChange::SubBlack(float SubPower) {
	if (m_SubStartChange) {
		if (s_color.w > 0.0f) {
			s_color.w -= SubPower;
		}
		else {
			m_SubStartChange = false;
			s_color.w = 0.0f;
			return true;
		}
	}

	return false;
}