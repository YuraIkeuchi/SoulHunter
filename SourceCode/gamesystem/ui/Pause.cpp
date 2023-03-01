#include "Pause.h"
#include "ImageManager.h"
#include "Input.h"
#include "imgui.h"
#include <Easing.h>
#include "VariableCommon.h"
#include "Audio.h"
#include "VolumManager.h"
#include "MiniMap.h"
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;

Pause::Pause() {
	//スプライト生成
	IKESprite* PausePartsSprite_[3];
	//gaussian = new PostEffect();
	const int PauseCount = 3;
	for (int i = 0; i < PausePartsSprite.size(); i++) {
		PausePartsSprite_[i] = IKESprite::Create(ImageManager::PauseParts, { 0.0f,0.0f });
		int number_index_y = i / PauseCount;
		int number_index_x = i % PauseCount;
		PausePartsSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * PartsWidth_Cut, static_cast<float>(number_index_y) * PartsHeight_Cut },
			{ static_cast<float>(PartsWidth_Cut), static_cast<float>(PartsHeight_Cut) });
		PausePartsSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		PausePartsSprite[i].reset(PausePartsSprite_[i]);
		m_PartsSize[i] = { PartsWidth_Cut,PartsHeight_Cut };
	}
	IKESprite* PauseSprite_;
	PauseSprite_ = IKESprite::Create(ImageManager::Pause1, { 0.0f,0.0f });
	PauseSprite.reset(PauseSprite_);
	IKESprite* PauseBack_;
	PauseBack_ = IKESprite::Create(ImageManager::PauseBack, { 0.0f,0.0f });
	PauseBack.reset(PauseBack_);
}
//初期化
void Pause::Initialize() {
	m_PartsPos[SkillPause] = { 350.0f,180.0f };
	m_PartsPos[OptionPause] = { 350.0f,380.0f };
	m_PartsPos[SelectPause] = { 350.0f,180.0f };

	MiniMap::GetInstance()->Update();
	skillpause->Update();
	option->Update();
}

//更新
void Pause::Update() {
	float l_AddColor = 0.05f;//加わる色
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Select) && (m_ReturnTimer == 0) && (!player->GetReadText())) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
		if (m_IsPause) {
			m_ColorChangeType = Sub;
		}
		else {
			m_PauseNumber = NormalPause;
			m_ColorChangeType = Add;
			m_IsPause = true;
		}
	}

	if (input->TriggerButton(input->Start) && (m_ReturnTimer == 0) && (!player->GetReadText()) && (!m_IsPause)) {
		m_PauseNumber = MiniMap;
		MiniMap::GetInstance()->SetChangeColorType(1);
		m_ColorChangeType = 2;
		m_ReturnTimer = 2;
		m_IsPause = true;
	}

	//段々と色が変わる処理
	if (m_ColorChangeType == Add) {
		m_PauseColor.w += l_AddColor;
		if (m_PauseColor.w > m_ColorMax) {
			m_PauseColor.w = m_ColorMax;
			m_ColorChangeType = No;
		}
	}
	else if (m_ColorChangeType == Sub) {
		m_PauseColor.w -= l_AddColor;
		if (m_PauseColor.w < m_ColorMin) {
			m_PauseColor.w = m_ColorMin;
			m_ColorChangeType = No;
			if (m_PauseNumber == NormalPause) {
				m_IsPause = false;
			}
		}
	}
	//選択
	PartsMove();
	//元のポーズメニューに戻る
	if (skillpause->GetReturnSkill() || option->GetReturnOption()) {
		m_PauseNumber = NormalPause;
		m_ColorChangeType = Add;
		if (m_ReturnTimer > 0) {
			m_ReturnTimer--;
		}
		else {
			m_ReturnTimer = 0;
			option->SetReturnOption(false);
			skillpause->SetReturnSkill(false);
			
		}
	}
	if (MiniMap::GetInstance()->GetReturnMap()) {
		if (m_ReturnTimer > 0) {
			m_ReturnTimer--;
		}
		else {
			m_IsPause = false;
			MiniMap::GetInstance()->SetReturnMap(false);
		}
	}
	for (int i = 0; i < PausePartsSprite.size(); i++) {
		PausePartsSprite[i]->SetPosition(m_PartsPos[i]);
		PausePartsSprite[i]->SetSize(m_PartsSize[i]);
		PausePartsSprite[i]->SetColor(m_PauseColor);
	}
	PauseSprite->SetColor(m_PauseColor);
}

//描画
const void Pause::Draw() {
	IKESprite::PreDraw();
	//メニューによって描画クラスが変わる
	if (m_IsPause) {
		PauseBack->Draw();
		if (m_PauseNumber == MiniMap) {
			MiniMap::GetInstance()->Draw();
		}
		else if (m_PauseNumber == SkillSet) {
			skillpause->Draw();
		}
		else if (m_PauseNumber == Option) {
			option->Draw();
		}
		else {
			PauseSprite->Draw();
			PausePartsSprite[2]->Draw();
			for (int i = 0; i < 2; i++) {
				PausePartsSprite[i]->Draw();
			}

		}
	}
}

void Pause::Finalize() {
}

void Pause::ResetPause() {
}
void Pause::PartsMove() {
	Input* input = Input::GetInstance();
	//どのメニューを選んだかで更新するクラスが変わる
	if (m_IsPause) {
		if (m_PauseNumber == NormalPause) {
			if (m_MenuNumber < 1 && input->LeftTriggerStick(input->Down)) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
				m_MenuNumber++;
			}

			if (m_MenuNumber > 0 && input->LeftTriggerStick(input->Up)) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
				m_MenuNumber--;
			}

			if (m_MenuNumber == 0 && input->TriggerButton(input->Button_A)) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
				m_PauseNumber = SkillSet;
				skillpause->SetChangeColorType(1);
				m_ColorChangeType = 2;
				m_ReturnTimer = 2;
			}

			else if (m_MenuNumber == 1 && input->TriggerButton(input->Button_A)) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
				m_PauseNumber = Option;
				option->SetChangeColorType(1);
				m_ColorChangeType = 2;
				m_ReturnTimer = 2;
			}
		}
		if (m_PauseNumber == MiniMap) {
			MiniMap::GetInstance()->Update();
		}
		else if (m_PauseNumber == SkillSet) {
			skillpause->Update();
		}
		else if (m_PauseNumber == Option) {
			option->Update();
		}
	}

	//選択されているものは座標やサイズが変わる
	if (m_MenuNumber == SkillPause) {
		m_Angle[SkillPause] += 2.0f;
		m_Angle2[SkillPause] = m_Angle[SkillPause] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_PartsPos[SelectPause] = m_PartsPos[SkillPause];
		
		//サイズが変わる
		m_PartsSize[SkillPause] = { (sin(m_Angle2[SkillPause]) * 32.0f - 32.0f) + (640.0f),
			(sin(m_Angle2[SkillPause]) * 16.0f - 16.0f) + (128.0f) };
		m_PartsSize[SelectPause] = m_PartsSize[SkillPause];
		m_PartsSize[OptionPause] = { 640.0f,128.0f };
		m_Angle[OptionPause] = 0.0f;
	}
	else {
		m_Angle[OptionPause] += 2.0f;
		m_Angle2[OptionPause] = m_Angle[OptionPause] * (3.14f / 180.0f);
		//選択時座標が上下に動く
		m_PartsPos[SelectPause] = m_PartsPos[OptionPause];
		//サイズが変わる
		m_PartsSize[OptionPause] = { (sin(m_Angle2[OptionPause]) * 32.0f - 32.0f) + (640.0f),
			(sin(m_Angle2[OptionPause]) * 16.0f - 16.0f) + (128.0f) };
		m_PartsSize[SelectPause] = m_PartsSize[OptionPause];
		m_PartsSize[SkillPause] = { 640.0f,128.0f };
		m_Angle[SkillPause] = 0.0f;
	}
}