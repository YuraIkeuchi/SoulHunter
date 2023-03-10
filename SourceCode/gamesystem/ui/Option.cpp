#include "Option.h"
#include "ImageManager.h"
#include "input.h"
#include "VolumManager.h"
#include "Audio.h"
#include "VariableCommon.h"
Option::Option() {
	const int OptionCount = 2;
	IKESprite* OptionSprite_[2];
	for (int i = 0; i < OptionSprite.size(); i++) {
		OptionSprite_[i] = IKESprite::Create(ImageManager::Option1, { 0.0f,0.0f });
		int number_index_y = i / OptionCount;
		int number_index_x = i % OptionCount;
		OptionSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * FullWidth_Cut, static_cast<float>(number_index_y) * FullHeight_Cut },
			{ static_cast<float>(FullWidth_Cut), static_cast<float>(FullHeight_Cut) });
		OptionSprite_[i]->SetSize({ FullWidth_Cut,FullHeight_Cut });
		OptionSprite[i].reset(OptionSprite_[i]);
	}

	IKESprite* VolumBarSprite_[2];
	for (int i = 0; i < VolumBarSprite.size(); i++) {
		VolumBarSprite_[i] = IKESprite::Create(ImageManager::VolumBar, { 0.0f,0.0f });
		VolumBarSprite[i].reset(VolumBarSprite_[i]);
	}
}
//初期化
void Option::Initialize() {
	
	VolumBarSprite[0]->SetPosition({ 450.0f,150.0f });
	VolumBarSprite[1]->SetPosition({ 450.0f,350.0f });
	m_SEVolum = VolumManager::GetInstance()->GetSEVolum();
	m_BGMVolum = VolumManager::GetInstance()->GetBGMVolum();
}

//更新
void Option::Update() {
	float l_AddColor = 0.05f;//加わる色
	float l_AddVolum = 0.01f;//加算される音量
	Input* input = Input::GetInstance();
	//元のポーズメニューに戻る
	if (input->TriggerButton(input->Select)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
		m_ColorChangeType = Sub;
		m_VolumChange = true;
	}

	if (VolumSelect == BGM && input->LeftTriggerStick(input->Down)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
		VolumSelect = SE;
	}

	if (VolumSelect == SE && input->LeftTriggerStick(input->Up)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
		VolumSelect = BGM;
	}

	//SEとBGMの音量調整をする
	if (VolumSelect == BGM){
		if (input->LeftTiltStick(input->Left) && m_BGMVolum > 0.01f) {
			m_BGMVolum -= l_AddVolum;
		}
		else if (input->LeftTiltStick(input->Right) && m_BGMVolum < 0.5f) {
			m_BGMVolum += l_AddVolum;
		}
	}
	else if (VolumSelect == SE) {
		if (input->LeftTiltStick(input->Left) && m_SEVolum > 0.01f) {
			m_SEVolum -= l_AddVolum;
		}
		else if (input->LeftTiltStick(input->Right) && m_SEVolum < 0.5f) {
			m_SEVolum += l_AddVolum;
		}
	}
	//色の変更
	//段々と色が変わる処理
	if (m_ColorChangeType == Add) {
		m_OptionColor.w += l_AddColor;
		m_OptionColor.w = min(m_OptionColor.w, m_ColorMax);
		if (m_OptionColor.w >= m_ColorMax) {
			m_ColorChangeType = No;
		}
	}
	else if (m_ColorChangeType == Sub) {
		m_OptionColor.w -= l_AddColor;
		m_OptionColor.w = max(m_OptionColor.w, m_ColorMin);
		if (m_OptionColor.w <= m_ColorMin) {
			m_ColorChangeType = No;
			m_ReturnOption = true;
		}
	}

	VolumBarSprite[0]->SetSize({ m_BGMVolum * 800.0f,64.0f });
	VolumBarSprite[1]->SetSize({ m_SEVolum * 800.0f,64.0f });

	VolumManager::GetInstance()->SetBGMVolum(m_BGMVolum);
	VolumManager::GetInstance()->SetSEVolum(m_SEVolum);
	for (int i = 0; i < VolumBarSprite.size(); i++) {
		OptionSprite[i]->SetColor(m_OptionColor);
		VolumBarSprite[i]->SetColor(m_OptionColor);
	}
}

//描画
const void Option::Draw() {
	IKESprite::PreDraw();
	OptionSprite[VolumSelect]->Draw();
	for (int i = 0; i < VolumBarSprite.size(); i++) {
		VolumBarSprite[i]->Draw();
	}
}