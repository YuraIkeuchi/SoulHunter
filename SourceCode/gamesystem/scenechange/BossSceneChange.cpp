#include "BossSceneChange.h"
#include "ImageManager.h"
#include "VariableCommon.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 BossSceneChange::s_color = { 1.0f,1.0f,1.0f,0.0f };

BossSceneChange::BossSceneChange() {
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change_->SetSize({ 1280.0f,720.0f });
	change.reset(change_);
}
//�X�V
void BossSceneChange::Update() {
	change->SetColor(s_color);
}
//�`��
const void BossSceneChange::Draw() {
	IKESprite::PreDraw();
	change->Draw();
}
//�J��
void BossSceneChange::Finalize() {

}
//�Â��Ȃ鏈��
bool BossSceneChange::AddBlack(float AddPower) {
	if (m_AddStartChange) {
		if (s_color.w < m_ColorMax) {
			s_color.w += AddPower;
		}
		else {
			m_AddStartChange = false;
			s_color.w = m_ColorMax;
			return true;
		}
	}

	return false;
}
//���邭�Ȃ鏈��
bool BossSceneChange::SubBlack(float SubPower) {
	if (m_SubStartChange) {
		if (s_color.w > m_ColorMin) {
			s_color.w -= SubPower;
		}
		else {
			m_SubStartChange = false;
			s_color.w = m_ColorMin;
			return true;
		}
	}

	return false;
}