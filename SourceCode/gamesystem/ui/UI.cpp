#include "UI.h"
#include "ImageManager.h"
#include "Easing.h"
#include "imgui.h"
//読み込み
UI::UI(Player* player, InterBoss* boss) {

	this->player.reset(player);
	this->interboss.reset(boss);
	//スプライトの宣言
	//データ読み込み
	IKESprite::LoadTexture(0, L"Resources/2d/ui/HP.png");
	IKESprite::LoadTexture(1, L"Resources/2d/ui/BossHP.png");
	IKESprite::LoadTexture(2, L"Resources/2d/ui/MP.png");
	IKESprite::LoadTexture(3, L"Resources/2d/ui/Gage.png");
	IKESprite::LoadTexture(4, L"Resources/2d/ui/Wing.png");

	//プレイヤーHP
	IKESprite* PlayerHpSprite_[HP_Max];
	for (int i = 0; i < PlayerHpSprite.size(); i++) {
		PlayerHpSprite_[i] = IKESprite::Create(0, { 0.0f,0.0f });
		PlayerHpSprite_[i]->SetPosition({ (64.0f * i) + 32.0f,24.0f });
		PlayerHpSprite[i].reset(PlayerHpSprite_[i]);
		m_HPColor[i] = {1.0f,1.0f,1.0f,1.0f};
	}

	//ボスHP
	IKESprite* BossHpSprite_;
	BossHpSprite_ = IKESprite::Create(1, { 0.0f,0.0f });
	BossHpSprite_->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	BossHpSprite_->SetPosition({ 100.0f,550.0f });
	BossHpSprite.reset(BossHpSprite_);
	//魂
		//スプライト生成
	IKESprite* SoulSprite_[72];
	//gaussian = new PostEffect();
	const int SoulCount = 72;
	m_Soul = player->GetSoulCount();
	for (int i = 0; i < SoulSprite.size(); i++) {
		SoulSprite_[i] = IKESprite::Create(2, {0.0f,0.0f});
		int number_index_y = i / SoulCount;
		int number_index_x = i % SoulCount;
		SoulSprite_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * m_CutWidth, static_cast<float>(number_index_y) * m_Soul },
			{ static_cast<float>(m_CutWidth), static_cast<float>(m_Soul) });
		SoulSprite_[i]->SetAnchorPoint({ 0.0f,0.0f });
		SoulSprite_[i]->SetPosition({ 118.0f,115.0f });
		SoulSprite_[i]->SetRotation({ 180.0f });
		SoulSprite[i].reset(SoulSprite_[i]);
	}

	//魂の枠
	IKESprite* SoulGageSprite_;
	SoulGageSprite_ = IKESprite::Create(3, { 0.0f,0.0f });
	SoulGageSprite_->SetPosition({ 32.0f,32.0f });
	SoulGageSprite.reset(SoulGageSprite_);
	
	//this->player = player;
	//ボスのHP
	if (boss) {
		m_BossHP = interboss->GetHP();
	}
}
//更新
void UI::Update(InterBoss* boss) {
	m_HP = player->GetHP();
	//魂
	m_Soul = player->GetSoulCount();

	//ボスのHP
	for (int i = 0; i < SoulSprite.size(); i++) {
		const int SoulCount = 72;
		int number_index_y = i / SoulCount;
		int number_index_x = i % SoulCount;
		SoulSprite[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * m_CutWidth, static_cast<float>(number_index_y) * m_Soul },
			{ static_cast<float>(m_CutWidth), static_cast<float>(m_Soul) });
		SoulSprite[i]->SetSize({ m_CutWidth,m_Soul });
	}
	if (boss) {
		m_BossHP = interboss->GetHP();
	}
	m_AfterBossHPSize = { (float)(m_BossHP * 50.0f), 34.0f };
	m_BossHPSize = {
	Ease(In,Quad,0.5f,(float)BossHpSprite->GetSize().x,(float)m_AfterBossHPSize.x),
	Ease(In,Quint,0.5f,(float)BossHpSprite->GetSize().y,(float)m_AfterBossHPSize.y),
	};
	BossHpSprite->SetSize(m_BossHPSize);
	for (int i = 0; i < PlayerHpSprite.size(); i++) {
		if (i >= m_HP) {
			if (m_HPColor[i].w > 0.0f) {
				m_HPColor[i].w -= 0.1f;
			}
			else {
				m_HPColor[i].w = 0.0f;
			}
		}
		else {
			if (m_HPColor[i].w < 1.0f) {
				m_HPColor[i].w += 0.1f;
			}
			else {
				m_HPColor[i].w = 1.0f;
			}
		}
		PlayerHpSprite[i]->SetColor(m_HPColor[i]);
	}
}
//描画
const void UI::Draw() {
	
	//プレイヤーのHP
	IKESprite::PreDraw();
	for (int i = 0; i < PlayerHpSprite.size(); i++) {
		PlayerHpSprite[i]->Draw();
	}
	for (int i = 0; i < SoulSprite.size(); i++) {
		if (m_Soul > i) {
			SoulSprite[i]->Draw();
		}
	}
	SoulGageSprite->Draw();

	if (interboss && playerskill->GetUseLibra() && interboss->GetAlive()) {
		BossHpSprite->Draw();
	}
}
//解放
void UI::Finalize() {
	//delete PlayerHpSprite;
	//delete BossHpSprite;
	//delete player;
	//delete interboss;
}