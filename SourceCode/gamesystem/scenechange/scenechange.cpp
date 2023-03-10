#include "SceneChange.h"
#include "ImageManager.h"
#include "VariableCommon.h"
using namespace std;         //  ���O��Ԏw��
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 SceneChange::s_color = {1.0f,1.0f,1.0f,0.0f};

SceneChange::SceneChange() {
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change_->SetSize({ 1280.0f,720.0f });
	change.reset(change_);
}
//�X�V
void SceneChange::Update() {
	change->SetColor(s_color);
}
//�`��
const void SceneChange::Draw() {
	IKESprite::PreDraw();
	change->Draw();
}
//�J��
void SceneChange::Finalize() {

}
//�F�����Z
bool SceneChange::AddBlack(float AddPower) {
	if (m_AddStartChange) {
		s_color.w += AddPower;
		s_color.w = min(s_color.w, m_ColorMax);
		if (s_color.w == m_ColorMax) {
			m_AddStartChange = false;
			return true;
		}
	}
	
	return false;
}
//�F�����Z
bool SceneChange::SubBlack(float SubPower) {
	if (m_SubStartChange) {
		s_color.w -= SubPower;
		s_color.w = max(s_color.w, m_ColorMin);
		if (s_color.w == m_ColorMin) {
			m_SubStartChange = false;
			return true;
		}
	}
	
	return false;
}