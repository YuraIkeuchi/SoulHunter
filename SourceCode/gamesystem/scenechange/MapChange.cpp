#include "MapChange.h"
#include "ImageManager.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
XMFLOAT4 MapChange::s_color = { 1.0f,1.0f,1.0f,0.0f };

MapChange::MapChange() {
	//死んだときに暗くなるようのやつ
	IKESprite* change_;
	change_ = IKESprite::Create(ImageManager::BlackFilter, { 0.0f,0.0f });
	change_->SetColor(s_color);
	change.reset(change_);
}

void MapChange::Update() {
	change->SetColor(s_color);
}

const void MapChange::Draw() {
	ImGui::Begin("mapfilter");
	ImGui::Text("%d", m_AddStartChange);
	ImGui::Text("%d", m_SubStartChange);
	ImGui::Text("%f", s_color.w);
	ImGui::End();
	IKESprite::PreDraw();
	change->Draw();
}

void MapChange::Finalize() {

}

bool MapChange::AddBlack() {
	if (m_AddStartChange) {
		if (s_color.w < 1.2f) {
			s_color.w += 0.08f;
		}
		else {
			m_AddStartChange = false;
			s_color.w = 1.2f;
			return true;
		}
	}

	return false;
}

bool MapChange::SubBlack() {
	if (m_SubStartChange) {
		if (s_color.w > 0.0f) {
			s_color.w -= 0.08f;
		}
		else {
			m_SubStartChange = false;
			s_color.w = 0.0f;
			return true;
		}
	}

	return false;
}