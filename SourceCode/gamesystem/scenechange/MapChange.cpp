#include "MapChange.h"
#include "ImageManager.h"
#include "VariableCommon.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 MapChange::s_color = { 1.0f,1.0f,1.0f,0.0f };

MapChange::MapChange() {
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change_->SetSize({ 1280.0f,720.0f });
	change.reset(change_);

	helper = make_unique< Helper>();
}
//�X�V
void MapChange::Update() {
	change->SetColor(s_color);
}
//�`��
const void MapChange::Draw() {
	IKESprite::PreDraw();
	change->Draw();
}
//�J��
void MapChange::Finalize() {

}
//�Â��Ȃ鏈��
bool MapChange::AddBlack() {
	float l_AddPower = 0.08f;
	if (m_AddStartChange) {
		if (helper->CheckMin(s_color.w, m_ColorMax, l_AddPower)) {
			m_AddStartChange = false;
			return true;
		}
	}

	return false;
}
//�����邭�Ȃ鏈��
bool MapChange::SubBlack() {
	float l_SubPower = 0.08f;
	if (m_SubStartChange) {
		if (helper->CheckMax(s_color.w, m_ColorMin, -l_SubPower)) {
			m_SubStartChange = false;
			return true;
		}
	}
	return false;
}