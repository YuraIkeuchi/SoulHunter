#include "SceneChange.h"
#include "ImageManager.h"
#include "VariableCommon.h"
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 SceneChange::s_color = {1.0f,1.0f,1.0f,0.0f};

SceneChange::SceneChange() {
	//死んだときに暗くなるようのやつ
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change_->SetSize({ 1280.0f,720.0f });
	change.reset(change_);
}
//更新
void SceneChange::Update() {
	change->SetColor(s_color);
}
//描画
const void SceneChange::Draw() {
	IKESprite::PreDraw();
	change->Draw();
}
//開放
void SceneChange::Finalize() {

}
//色を加算
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
//色を減算
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