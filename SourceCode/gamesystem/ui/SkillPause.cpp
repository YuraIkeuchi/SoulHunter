#include "SkillPause.h"
#include "ImageManager.h"
#include "Input.h"
#include <Easing.h>
#include "PlayerSkill.h"
#include "Audio.h"
#include "VolumManager.h"
using namespace std;         //  名前空間指定
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//読み込み
SkillPause::SkillPause() {
	//コンパス
	CompassPause* compasspause_;
	compasspause_ = new CompassPause();
	compasspause_->Initialize();
	compasspause_->Update();
	compasspause.reset(compasspause_);
	//ダッシュ
	DushPause* dushpause_;
	dushpause_ = new DushPause();
	dushpause_->Initialize();
	dushpause_->Update();
	dushpause.reset(dushpause_);
	//ライブラ
	LibraPause* librapause_;
	librapause_ = new LibraPause();
	librapause_->Initialize();
	librapause_->Update();
	librapause.reset(librapause_);
	//ヒール
	HealPause* healpause_;
	healpause_ = new HealPause();
	healpause_->Initialize();
	healpause_->Update();
	healpause.reset(healpause_);
	//ジャンプ
	JumpPause* jumppause_;
	jumppause_ = new JumpPause();
	jumppause_->Initialize();
	jumppause_->Update();
	jumppause.reset(jumppause_);

	IKESprite* PauseSprite_;
	PauseSprite_ = IKESprite::Create(ImageManager::PauseSkill, { 0.0f,0.0f });
	PauseSprite.reset(PauseSprite_);

	IKESprite* select_;
	select_ = IKESprite::Create(ImageManager::PauseSelect, { 0.0f,0.0f });
	select_->SetPosition({ 150.0f, 200.0f });
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

	//スキルの說明
	IKESprite* ExplainSprite_[Skill_Max];
	ExplainSprite_[0] = IKESprite::Create(ImageManager::LibraExplain, { 0.0f,0.0f });
	ExplainSprite_[1] = IKESprite::Create(ImageManager::DushExplain, { 0.0f,0.0f });
	ExplainSprite_[2] = IKESprite::Create(ImageManager::CompassExplain, { 0.0f,0.0f });
	ExplainSprite_[3] = IKESprite::Create(ImageManager::HealExplain, { 0.0f,0.0f });
	ExplainSprite_[4] = IKESprite::Create(ImageManager::JumpExplain, { 0.0f,0.0f });
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
	jumppause->InitPos();
}
//初期化
void SkillPause::Initialize() {
	//セットできるスキルの数
	NoItemSprite[0]->SetPosition({ 150.0f,200.0f });
	NoItemSprite[1]->SetPosition({ 300.0f,200.0f });
	NoItemSprite[2]->SetPosition({ 450.0f,200.0f });
	NoItemSprite[3]->SetPosition({ 150.0f,400.0f });
	NoItemSprite[4]->SetPosition({ 300.0f,400.0f });
}
//更新
void SkillPause::Update() {
	compasspause->Update();
	dushpause->Update();
	librapause->Update();
	healpause->Update();
	jumppause->Update();
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
	compasspause->SetColor(m_SkillColor);
	dushpause->SetColor(m_SkillColor);
	librapause->SetColor(m_SkillColor);
	healpause->SetColor(m_SkillColor);
	jumppause->SetColor(m_SkillColor);
	//スキル選択
	SelectSkill();
	//選択肢が合うとサイズが動く
	compasspause->ChangeSize(select->GetPosition());
	dushpause->ChangeSize(select->GetPosition());
	librapause->ChangeSize(select->GetPosition());
	healpause->ChangeSize(select->GetPosition());
	jumppause->ChangeSize(select->GetPosition());
}
//描画
const void SkillPause::Draw() {
	ImGui::Begin("Pause");
	ImGui::Text("SelectWidth:%d", m_SelectWeight);
	ImGui::Text("SelectHeight:%d", m_SelectHeight);
	ImGui::End();
	IKESprite::PreDraw();
	PauseSprite->Draw();
	
	for (int i = 0; i < Skill_Max; i++) {
		NoItemSprite[i]->Draw();
	}
	//スキル取得状況によって変わる
	if (PlayerSkill::GetInstance()->GetLibraSkill() && librapause->GetLibraPos().x != 0.0f) {
		librapause->Draw();
	}
	if (PlayerSkill::GetInstance()->GetDushSkill() && dushpause->GetDushPos().x != 0.0f) {
		dushpause->Draw();
	}
	if (PlayerSkill::GetInstance()->GetCompassSkill() && compasspause->GetCompassPos().x != 0.0f) {
		compasspause->Draw();
	}
	if (PlayerSkill::GetInstance()->GetHealSkill() && healpause->GetHealPos().x != 0.0f) {
		healpause->Draw();
	}
	if (PlayerSkill::GetInstance()->GetJumpSkill() && jumppause->GetJumpPos().x != 0.0f) {
		jumppause->Draw();
	}

	if ((select->GetPosition().x == librapause->GetLibraPos().x && select->GetPosition().y == librapause->GetLibraPos().y)
		&& PlayerSkill::GetInstance()->GetLibraSkill()) {
		ExplainSprite[0]->Draw();
	}
	else if ((select->GetPosition().x == dushpause->GetDushPos().x && select->GetPosition().y == dushpause->GetDushPos().y)
		&& PlayerSkill::GetInstance()->GetDushSkill()) {
		ExplainSprite[1]->Draw();
	}
	else if ((select->GetPosition().x == compasspause->GetCompassPos().x && select->GetPosition().y == compasspause->GetCompassPos().y)
		&& PlayerSkill::GetInstance()->GetCompassSkill()) {
		ExplainSprite[2]->Draw();
	}
	else if ((select->GetPosition().x == healpause->GetHealPos().x && select->GetPosition().y == healpause->GetHealPos().y)
		&& PlayerSkill::GetInstance()->GetHealSkill()) {
		ExplainSprite[3]->Draw();
	}
	else if ((select->GetPosition().x == jumppause->GetJumpPos().x && select->GetPosition().y == jumppause->GetJumpPos().y)
		&& PlayerSkill::GetInstance()->GetJumpSkill()) {
		ExplainSprite[4]->Draw();
	}
	select->Draw();
}
//解放
void SkillPause::Finalize() {
}
//スキルのリセット
void SkillPause::ResetSkillPause() {
	
}
//スキルの選択
void SkillPause::SelectSkill() {
	Input* input = Input::GetInstance();
	if (m_SelectHeight == Down && input->LeftTriggerStick(input->Up)) {
		m_SelectHeight = Up;
		m_SelectWeight = LeftSide;
		select->SetPosition({ 150.0f,select->GetPosition().y - 200.0f });
	}
	else if (m_SelectHeight == Up && input->LeftTriggerStick(input->Down)) {
		m_SelectHeight = Down;
		m_SelectWeight = LeftSide;
		select->SetPosition({ 150.0f,select->GetPosition().y + 200.0f });
	}
	if (m_SelectHeight == Up) {
		//選択の場所を変える
		if (m_SelectWeight < RightSide && input->LeftTriggerStick(input->Right)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectWeight++;
			select->SetPosition({ select->GetPosition().x + 150.0f,200.0f });
		}
		if (m_SelectWeight > LeftSide && input->LeftTriggerStick(input->Left)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectWeight--;
			select->SetPosition({ select->GetPosition().x - 150.0f,200.0f });
		}
	}
	else {
		//選択の場所を変える
		if (m_SelectWeight > LeftSide && input->LeftTriggerStick(input->Left)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectWeight--;
			select->SetPosition({ select->GetPosition().x - 150.0f,400.0f });
		}
		//選択の場所を変える
		if (m_SelectWeight < RightSide - 1 && input->LeftTriggerStick(input->Right)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Select.wav", VolumManager::GetInstance()->GetSEVolum());
			m_SelectWeight++;
			select->SetPosition({ select->GetPosition().x + 150.0f,200.0f });
		}
	}
}