#include "BossName.h"
#include "ImageManager.h"
#include "imgui.h"
BossName::BossName() {
	//���񂾂Ƃ��ɈÂ��Ȃ�悤�̂��
	IKESprite* bossname_;
	bossname_ = IKESprite::Create(ImageManager::BossName, { 0.0f,0.0f });
	bossname_->SetColor(m_color);
	bossname_->SetPosition({ 700.0f,100.0f });
	bossname.reset(bossname_);
}

void BossName::Update() {
	if (m_DrawName) {
		if (m_AddStartChange) {
			if (m_AlphaNumber == Add) {
				AddColor();
			}
			else {
				SubColor();
			}
		}
	}

	bossname->SetColor(m_color);
}

const void BossName::Draw() {
	ImGui::Begin("BossName");
	ImGui::Text("DrawName:%d", m_DrawName);
	ImGui::Text("Alpha:%d", m_AlphaNumber);
	ImGui::Text("%f", m_color.w);
	ImGui::End();
	IKESprite::PreDraw();
	if (m_DrawName) {
		bossname->Draw();
	}
}

void BossName::AddColor() {

	if (m_color.w < m_ColorMax) {
		m_color.w += m_ChangeTexFrame;
	}
	else {
		m_AlphaNumber = Sub;
		m_color.w = m_ColorMax;
	}
}

void BossName::SubColor() {
	if (m_color.w > m_ColorMin) {
		m_color.w -= m_ChangeTexFrame;
	}
	else {
		m_DrawName = false;
		m_AlphaNumber = Sub;
		m_color.w = m_ColorMin;
	}
}