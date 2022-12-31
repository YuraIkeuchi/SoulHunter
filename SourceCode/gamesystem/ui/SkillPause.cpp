#include "SkillPause.h"
#include "ImageManager.h"
#include "Input.h"
#include "imgui.h"
#include <Easing.h>
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//静的メンバ変数の実態
bool SkillPause::m_SetSkill[Set_Max] = { false };
XMFLOAT2 SkillPause::m_SkillPos[Skill_Max] = {};
XMFLOAT2 SkillPause::m_SetSkillPos[Set_Max] = {};
int SkillPause::m_SkillName[Set_Max] = { 0 };
//読み込み
SkillPause::SkillPause() {
	CompassPause* compasspause_;
	compasspause_ = new CompassPause();
	compasspause_->Initialize();
	compasspause_->Update();
	compasspause.reset(compasspause_);
	DushPause* dushpause_;
	dushpause_ = new DushPause();
	dushpause_->Initialize();
	dushpause_->Update();
	dushpause.reset(dushpause_);
	LibraPause* librapause_;
	librapause_ = new LibraPause();
	librapause_->Initialize();
	librapause_->Update();
	librapause.reset(librapause_);

	HealPause* healpause_;
	healpause_ = new HealPause();
	healpause_->Initialize();
	healpause_->Update();
	healpause.reset(healpause_);

	IKESprite* PauseSprite_;
	PauseSprite_ = IKESprite::Create(ImageManager::PauseSkill, { 0.0f,0.0f });
	PauseSprite.reset(PauseSprite_);

	IKESprite* select_;
	select_ = IKESprite::Create(ImageManager::PauseSelect, { 0.0f,0.0f });
	select_->SetPosition({ 150.0f, 548.0f });
	select_->SetAnchorPoint({ 0.5f,0.5f });
	select_->SetSize({ 96.0f,96.0f });
	select.reset(select_);
	//手に入るスキルの数
	IKESprite* NoItemSprite_[Skill_Max];
	for (int i = 0; i < Skill_Max; i++) {
		NoItemSprite_[i] = IKESprite::Create(ImageManager::NoItem, { 0.0f,0.0f });
		NoItemSprite_[i]->SetSize({ 48.0f,48.0f });
		NoItemSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
	}
	
	for (int i = 0; i < Skill_Max; i++) {
		NoItemSprite[i].reset(NoItemSprite_[i]);
	}

	IKESprite* SetSkillSprite_[Set_Max];
	for (std::size_t i = 0; i < SetSkillSprite.size(); i++) {
		SetSkillSprite_[i] = IKESprite::Create(ImageManager::NoItem, { 0.0f,0.0f });
		SetSkillSprite_[i]->SetSize({ 48.0f,48.0f });
		SetSkillSprite_[i]->SetPosition(m_SetSkillPos[i]);
		SetSkillSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		SetSkillSprite[i].reset(SetSkillSprite_[i]);
	}

	//スキルの說明
	IKESprite* ExplainSprite_[Skill_Max];
	ExplainSprite_[0] = IKESprite::Create(ImageManager::LibraExplain, { 0.0f,0.0f });
	ExplainSprite_[1] = IKESprite::Create(ImageManager::DushExplain, { 0.0f,0.0f });
	ExplainSprite_[2] = IKESprite::Create(ImageManager::CompassExplain, { 0.0f,0.0f });
	ExplainSprite_[3] = IKESprite::Create(ImageManager::HealExplain, { 0.0f,0.0f });
	for (int i = 0; i < Skill_Max; i++) {
		ExplainSprite_[i]->SetPosition({ 770.0f,200.0f });
		ExplainSprite[i].reset(ExplainSprite_[i]);
	}
}
//位置の初期化
void SkillPause::InitPos() {
	compasspause->InitPos();
	dushpause->InitPos();
	librapause->InitPos();
	healpause->InitPos();
}
//初期化
void SkillPause::Initialize() {
	//セットできるスキルの数
	m_SetSkillPos[0] = { 148.0f,188.0f };
	m_SetSkillPos[1] = { 348.0f,188.0f };
	NoItemSprite[0]->SetPosition({ 150.0f,548.0f });
	NoItemSprite[1]->SetPosition({ 300.0f,548.0f });
	NoItemSprite[2]->SetPosition({ 450.0f,548.0f });
	NoItemSprite[3]->SetPosition({ 600.0f,548.0f });
	for (std::size_t i = 0; i < SetSkillSprite.size(); i++) {
		SetSkillSprite[i]->SetPosition(m_SetSkillPos[i]);
	}
}
//更新
void SkillPause::Update() {
	compasspause->Update();
	dushpause->Update();
	librapause->Update();
	healpause->Update();
	Input* input = Input::GetInstance();
	//元のポーズメニューに戻る
	if (input->TriggerButton(input->Select)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Menu.wav", VolumManager::GetInstance()->GetSEVolum());
		m_ColorChangeType = Sub;
	}
	//段々と色が変わる処理
	if (m_ColorChangeType == Add) {
		m_SkillColor.w += 0.05f;
		if (m_SkillColor.w > 1.0f) {
			m_SkillColor.w = 1.0f;
			m_ColorChangeType = No;
		}
	}
	else if (m_ColorChangeType == Sub) {
		m_SkillColor.w -= 0.05f;
		if (m_SkillColor.w < 0.0f) {
			m_SkillColor.w = 0.0f;
			m_ColorChangeType = No;
			m_ReturnSkill = true;
		}
	}

	//色指定
	PauseSprite->SetColor(m_SkillColor);
	select->SetColor(m_SkillColor);
	for (int i = 0; i < Skill_Max; i++) {
		NoItemSprite[i]->SetColor(m_SkillColor);
		ExplainSprite[i]->SetColor(m_SkillColor);
	}
	for (std::size_t i = 0; i < SetSkillSprite.size(); i++) {
		SetSkillSprite[i]->SetColor(m_SkillColor);
	}
	compasspause->SetColor(m_SkillColor);
	dushpause->SetColor(m_SkillColor);
	librapause->SetColor(m_SkillColor);
	healpause->SetColor(m_SkillColor);
	//スキル選択
	SelectSkill();
	//選択肢が合うとサイズが動く
	compasspause->ChangeSize(m_SelectDir,m_SelectNumber,select->GetPosition());
	dushpause->ChangeSize(m_SelectDir, m_SelectNumber, select->GetPosition());
	librapause->ChangeSize(m_SelectDir, m_SelectNumber, select->GetPosition());
	healpause->ChangeSize(m_SelectDir, m_SelectNumber, select->GetPosition());
}
//描画
const void SkillPause::Draw() {
	/*ImGui::Begin("Skill");
	ImGui::Text(" m_SkillColor.w::%f", m_SkillColor.w);
	ImGui::End();*/
	IKESprite::PreDraw();
	PauseSprite->Draw();
	for (std::size_t i = 0; i < SetSkillSprite.size(); i++) {
		SetSkillSprite[i]->Draw();
	}

	for (int i = 0; i < Skill_Max; i++) {
		NoItemSprite[i]->Draw();
	}
	//スキル取得状況によって変わる
	if (playerskill->GetLibraSkill() && librapause->GetLibraPos().x != 0.0f) {
		librapause->Draw();
		//SkillSprite[0]->Draw();
	}

	if (playerskill->GetDushSkill() && dushpause->GetDushPos().x != 0.0f) {
		dushpause->Draw();
		//SkillSprite[1]->Draw();
	}

	if (playerskill->GetCompassSkill() && compasspause->GetCompassPos().x != 0.0f) {
		compasspause->Draw();
		//SkillSprite[2]->Draw();
	}
	//後々直す(ヒールスキル)
	if (playerskill->GetHealSkill() && healpause->GetHealPos().x != 0.0f) {
		healpause->Draw();
		//SkillSprite[2]->Draw();
	}

	if (m_SelectDir == Down) {
		if (m_SelectNumber == 0 && playerskill->GetLibraSkill() && !playerskill->GetUseLibra()) {
			ExplainSprite[0]->Draw();
		}
		else if (m_SelectNumber == 1 && playerskill->GetDushSkill() && !playerskill->GetUseDush()) {
			ExplainSprite[1]->Draw();
		}
		else if (m_SelectNumber == 2 && playerskill->GetCompassSkill() && !playerskill->GetUseCompass()) {
			ExplainSprite[2]->Draw();
		}
		else if (m_SelectNumber == 3 && playerskill->GetHealSkill() && !playerskill->GetUseHeal()) {
			ExplainSprite[3]->Draw();
		}
	}
	else {
		if (m_SelectNumber == 3) {
			if (m_SetSkill[0] && m_SkillName[0] == Libra && playerskill->GetUseLibra()) {
				ExplainSprite[0]->Draw();
			}
			else if (m_SetSkill[0] && m_SkillName[0] == Dush && playerskill->GetUseDush()) {
				ExplainSprite[1]->Draw();
			}
			else if (m_SetSkill[0] && m_SkillName[0] == Compass && playerskill->GetUseCompass()) {
				ExplainSprite[2]->Draw();
			}
			else if (m_SetSkill[0] && m_SkillName[0] == Heal && playerskill->GetUseHeal()) {
				ExplainSprite[3]->Draw();
			}
		}

		else if (m_SelectNumber == 4) {
			if (m_SetSkill[1] && m_SkillName[1] == Libra && playerskill->GetUseLibra()) {
				ExplainSprite[0]->Draw();
			}
			else if (m_SetSkill[1] && m_SkillName[1] == Dush && playerskill->GetUseDush()) {
				ExplainSprite[1]->Draw();
			}
			else if (m_SetSkill[1] && m_SkillName[1] == Compass && playerskill->GetUseCompass()) {
				ExplainSprite[2]->Draw();
			}
			else if (m_SetSkill[1] && m_SkillName[1] == Heal && playerskill->GetUseHeal()) {
				ExplainSprite[3]->Draw();
			}
		}
	}
	select->Draw();
}
//解放
void SkillPause::Finalize() {
	//delete PauseSprite;
	//delete select;
	//for (int i = 0; i < Skill_Max; i++) {
	//	delete SkillSprite[i];
	//}
	//for (std::size_t i = 0; i < SetSkillSprite.size(); i++) {
	//	delete SetSkillSprite[i];
	//}
}
//スキルのリセット
void SkillPause::ResetSkillPause() {
	for (int i = 0; i < Set_Max; i++) {
		m_SetSkill[i] = false;
		m_SkillName[i] = None;
	}
}
//スキルの選択
void SkillPause::SelectSkill() {
	Input* input = Input::GetInstance();
	if (m_SelectDir == Down && input->LeftTriggerStick(input->Up)) {
		m_SelectDir = Up;
		m_SelectNumber = 3;
		select->SetPosition({ 148.0f,188.0f });
	}
	else if (m_SelectDir == Up && input->LeftTriggerStick(input->Down)) {
		m_SelectDir = Down;
		m_SelectNumber = 0;
		select->SetPosition({ 150.0f,548.0f });
	}
	//スキル選択中
	if (m_SelectDir == Down) {
		//選択の場所を変える
		if (m_SelectNumber < 3 && input->LeftTriggerStick(input->Right)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectNumber++;
			select->SetPosition({ select->GetPosition().x + 150.0f,548.0f });
		}

		else if (m_SelectNumber > 0 && input->LeftTriggerStick(input->Left)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectNumber--;
			select->SetPosition({ select->GetPosition().x - 150.0f,548.0f });
		}

		//スキルをセットする
		if (input->TriggerButton(input->Button_A) && m_SkillColor.w == 1.0f) {
			//ライブラスキル
			if (m_SelectNumber == 0 && playerskill->GetLibraSkill() && !playerskill->GetUseLibra()) {
				for (int i = 0; i < Set_Max; i++) {
					if (!m_SetSkill[i]) {
						Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillSet.wav", VolumManager::GetInstance()->GetSEVolum());
						m_SetSkill[i] = true;
						librapause->SetLibraPos(m_SetSkillPos[i]);
						m_SkillName[i] = Libra;
						playerskill->UseLibraSkill();
						player->SetUseLibra(true);
						break;
					}
				}
			}
			//ダッシュスキル
			if (m_SelectNumber == 1 && playerskill->GetDushSkill() && !playerskill->GetUseDush()) {
				for (int i = 0; i < Set_Max; i++) {
					if (!m_SetSkill[i]) {
						Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillSet.wav", VolumManager::GetInstance()->GetSEVolum());
						m_SetSkill[i] = true;
						dushpause->SetDushPos(m_SetSkillPos[i]);
						m_SkillName[i] = Dush;
						playerskill->UseDushSkill();
						player->SetUseDush(true);
						break;
					}
				}
			}
			//コンパススキル
			else if (m_SelectNumber == 2 && playerskill->GetCompassSkill() && !playerskill->GetUseCompass()) {
				for (int i = 0; i < Set_Max; i++) {
					if (!m_SetSkill[i]) {
						Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillSet.wav", VolumManager::GetInstance()->GetSEVolum());
						m_SetSkill[i] = true;
						compasspause->SetCompassPos(m_SetSkillPos[i]);
						m_SkillName[i] = Compass;
						playerskill->UseCompassSkill();
						player->SetUseCompass(true);
						break;
					}
				}
			}
			//ヒールスキル
			else if (m_SelectNumber == 3 && playerskill->GetHealSkill() && !playerskill->GetUseHeal()) {
				for (int i = 0; i < Set_Max; i++) {
					if (!m_SetSkill[i]) {
						Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillSet.wav", VolumManager::GetInstance()->GetSEVolum());
						m_SetSkill[i] = true;
						healpause->SetHealPos(m_SetSkillPos[i]);
						m_SkillName[i] = Heal;
						playerskill->UseHealSkill();
						player->SetUseHeal(true);
						break;
					}
				}
			}
		}
	}
	else {
		if (m_SelectNumber < 4 && input->LeftTriggerStick(input->Right)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectNumber++;
			select->SetPosition({ select->GetPosition().x + 200.0f,188.0f });
		}

		if (m_SelectNumber > 3 && input->LeftTriggerStick(input->Left)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectNumber--;
			select->SetPosition({ select->GetPosition().x - 200.0f,188.0f });
		}
		//スキルを外す
		if (input->TriggerButton(input->Button_A) && m_SkillColor.w == 1.0f) {
			//	一番左
			if (m_SelectNumber == 3) {
				if (m_SetSkill[0] && m_SkillName[0] == Libra && playerskill->GetUseLibra()) {//ライブラ
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[0] = { 150.0f,548.0f };
					m_SetSkill[0] = false;
					playerskill->SetUseLibra(false);
					player->SetUseLibra(false);
					m_SkillName[0] = None;
					librapause->SetLibraPos(m_SkillPos[0]);
				}
				else if (m_SetSkill[0] && m_SkillName[0] == Dush && playerskill->GetUseDush()) {//ダッシュ
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[1] = { 300.0f,548.0f };
					m_SetSkill[0] = false;
					playerskill->SetUseDush(false);
					player->SetUseDush(false);
					m_SkillName[0] = None;
					dushpause->SetDushPos(m_SkillPos[1]);
				}
				else if (m_SetSkill[0] && m_SkillName[0] == Compass && playerskill->GetUseCompass()) {//コンパス
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[2] = { 450.0f,548.0f };
					m_SetSkill[0] = false;
					playerskill->SetUseCompass(false);
					player->SetUseCompass(false);
					m_SkillName[0] = None;
					compasspause->SetCompassPos(m_SkillPos[2]);
				}
				else if (m_SetSkill[0] && m_SkillName[0] == Heal && playerskill->GetUseHeal()) {//ヒール
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[3] = { 600.0f,548.0f };
					m_SetSkill[0] = false;
					playerskill->SetUseHeal(false);
					player->SetUseHeal(false);
					m_SkillName[0] = None;
					healpause->SetHealPos(m_SkillPos[3]);
				}
			}
			//2番め
			else if (m_SelectNumber == 4) {
				if (m_SetSkill[1] && m_SkillName[1] == Libra && playerskill->GetUseLibra()) {
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[0] = { 150.0f,548.0f };
					m_SetSkill[1] = false;
					playerskill->ResetLibraSkill();
					player->SetUseLibra(false);
					m_SkillName[1] = None;
					librapause->SetLibraPos(m_SkillPos[0]);
				}
				else if (m_SetSkill[1] && m_SkillName[1] == Dush && playerskill->GetUseDush()) {
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[1] = { 300.0f,548.0f };
					m_SetSkill[1] = false;
					playerskill->ResetDushSkill();
					player->SetUseDush(false);
					m_SkillName[1] = None;
					dushpause->SetDushPos(m_SkillPos[1]);
				}
				else if (m_SetSkill[1] && m_SkillName[1] == Compass && playerskill->GetUseCompass()) {
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[2] = { 450.0f,548.0f };
					m_SetSkill[1] = false;
					playerskill->ResetCompassSkill();
					player->SetUseCompass(false);
					m_SkillName[1] = None;
					compasspause->SetCompassPos(m_SkillPos[2]);
				}
				else if (m_SetSkill[1] && m_SkillName[1] == Heal && playerskill->GetUseHeal()) {
					Audio::GetInstance()->PlayWave("Resources/Sound/SE/SkillNo.wav", VolumManager::GetInstance()->GetSEVolum());
					m_SkillPos[3] = { 600.0f,548.0f };
					m_SetSkill[1] = false;
					playerskill->ResetHealSkill();
					player->SetUseHeal(false);
					m_SkillName[1] = None;
					healpause->SetHealPos(m_SkillPos[3]);
				}
			}
		}
	}
}