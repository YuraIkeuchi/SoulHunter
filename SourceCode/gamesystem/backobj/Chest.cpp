﻿#include "Chest.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "Collision.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "Audio.h"
#include "VolumManager.h"
#include "Easing.h"
#include "Input.h"
#include "ParticleEmitter.h"
//モデル読み込みと初期化
Chest::Chest() {
	helper = make_unique<Helper>();
	//スプライト読み込み
	IKESprite::LoadTexture(20, L"Resources/2d/SkillExplain/CompassExplain.png");
	IKESprite::LoadTexture(21, L"Resources/2d/SkillExplain/LibraExplain.png");
	IKESprite::LoadTexture(22, L"Resources/2d/SkillExplain/DushExplain.png");
	IKESprite::LoadTexture(23, L"Resources/2d/SkillExplain/HealExplain.png");
	IKESprite::LoadTexture(24, L"Resources/2d/SkillExplain/JumpExplain.png");
	//モデル
	modelCloseChest = ModelManager::GetInstance()->GetModel(ModelManager::CloseChest);
	modelOpenChest = ModelManager::GetInstance()->GetModel(ModelManager::OpenChest);

	IKEObject3d* objCloseChest_[Skill_Max];
	for (int i = 0; i < Skill_Max; i++) {
		objCloseChest_[i] = new IKEObject3d();
		objCloseChest_[i] = IKEObject3d::Create();
		m_CloseColor[i] = { 1.0f,1.0f,1.0f,1.0f };
		objCloseChest_[i]->SetModel(modelCloseChest);
		objCloseChest_[i]->SetScale({ 4.0f,4.0f,4.0f });
		objCloseChest_[i]->SetRotation({ 0.0f,180.0f,0.0f });
		objCloseChest[i].reset(objCloseChest_[i]);
		m_ReadText[i] = false;
	}

	IKEObject3d* objOpenChest_[Skill_Max];
	for (int i = 0; i < Skill_Max; i++) {
		objOpenChest_[i] = new IKEObject3d();
		objOpenChest_[i] = IKEObject3d::Create();
		objOpenChest_[i]->SetModel(modelOpenChest);
		m_OpenColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		objOpenChest_[i]->SetScale({ 4.0f,4.0f,4.0f });
		objOpenChest_[i]->SetRotation({ 0.0f,180.0f,0.0f });
		objOpenChest[i].reset(objOpenChest_[i]);
	}

	//スプライト
	//バック
	IKESprite* ExplainBack_;
	ExplainBack_ = IKESprite::Create(ImageManager::ChestBack, { 0.0f,0.0f });
	ExplainBack_->SetPosition({ 0.0f,0.0f });
	ExplainBack.reset(ExplainBack_);
	//ミニマップスキル
	IKESprite* miniSkill_[Skill_Max];
	for (int i = 0; i < miniSkill.size(); i++) {
		miniSkill_[i] = IKESprite::Create(ImageManager::MiniSkill, { 0.0f,0.0f });
		miniSkill_[i]->SetAnchorPoint({ 0.5f,0.5f });
		miniSkill_[i]->SetScale(0.7f);
		miniSkill[i].reset(miniSkill_[i]);
	}

	//コンパススキル
	IKESprite* CompassExplain_[CompassExplain_Max];
	for (int i = 0; i < CompassExplain.size(); i++) {
		CompassExplain_[i] = IKESprite::Create(20, { 0.0f,0.0f });
		int number_index_y = i / CompassExplain_Max;
		int number_index_x = i % CompassExplain_Max;
		CompassExplain_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		CompassExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		CompassExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
		m_CompassTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
		CompassExplain[i].reset(CompassExplain_[i]);
		m_CompassColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		m_CompassDraw[i] = false;
	}

	//ライブラ
	IKESprite* LibraExplain_[LibraExplain_Max];
	for (int i = 0; i < LibraExplain.size(); i++) {
		LibraExplain_[i] = IKESprite::Create(21, { 0.0f,0.0f });
		int number_index_y = i / LibraExplain_Max;
		int number_index_x = i % LibraExplain_Max;
		LibraExplain_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		LibraExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		LibraExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
		m_LibraTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
		//LibraExplain_[i]->SetPosition({ 640.0f,(200.0f * i) + 200.0f });
		LibraExplain[i].reset(LibraExplain_[i]);
		m_LibraColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		m_LibraDraw[i] = false;
	}

	//ダッシュスキル
	IKESprite* DushExplain_[DushExplain_Max];
	for (int i = 0; i < DushExplain.size(); i++) {
		DushExplain_[i] = IKESprite::Create(22, { 0.0f,0.0f });
		int number_index_y = i / DushExplain_Max;
		int number_index_x = i % DushExplain_Max;
		DushExplain_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		DushExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		DushExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
		m_DushTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
		DushExplain[i].reset(DushExplain_[i]);
		m_DushColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		m_DushDraw[i] = false;
	}

	//ヒール
	IKESprite* HealExplain_[HealExplain_Max];
	for (int i = 0; i < HealExplain.size(); i++) {
		HealExplain_[i] = IKESprite::Create(23, { 0.0f,0.0f });
		int number_index_y = i / HealExplain_Max;
		int number_index_x = i % HealExplain_Max;
		HealExplain_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		HealExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		HealExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
		m_HealTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
		//HealExplain_[i]->SetPosition({ 640.0f,(200.0f * i) + 200.0f });
		HealExplain[i].reset(HealExplain_[i]);
		m_HealColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		m_HealDraw[i] = false;
	}

	//ジャンプ
	IKESprite* JumpExplain_[JumpExplain_Max];
	for (int i = 0; i < JumpExplain.size(); i++) {
		JumpExplain_[i] = IKESprite::Create(24, { 0.0f,0.0f });
		int number_index_y = i / JumpExplain_Max;
		int number_index_x = i % JumpExplain_Max;
		JumpExplain_[i]->SetTextureRect(
			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
		JumpExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
		JumpExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
		m_JumpTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
		//LibraExplain_[i]->SetPosition({ 640.0f,(200.0f * i) + 200.0f });
		JumpExplain[i].reset(JumpExplain_[i]);
		m_JumpColor[i] = { 1.0f,1.0f,1.0f,0.0f };
		m_JumpDraw[i] = false;
	}
	//宝箱に近づいたときのテクスチャ
	IKETexture* chestTex_ = IKETexture::Create(ImageManager::ChestTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	chestTex_->TextureCreate();
	chestTex_->SetRotation({ 0,0,0 });
	chestTex_->SetScale({ 0.6f,0.3f,0.3f });
	chestTex.reset(chestTex_);
}
//更新
void Chest::Update() {
	//当たり判定
	Collide();
	//宝箱を開ける
	OpenChest();
	//説明文
	Explain();
	//宝箱を開けるテキストの動き
	TexMove();
	//ミニマップ時の位置
	MapSet();
	//Obj関係
	for (int i = 0; i < Skill_Max; i++) {
		objCloseChest[i]->SetPosition(m_ChestPos[i]);
		objCloseChest[i]->SetColor(m_CloseColor[i]);
		objCloseChest[i]->Update();
		objOpenChest[i]->SetPosition(m_ChestPos[i]);
		objOpenChest[i]->SetColor(m_OpenColor[i]);
		objOpenChest[i]->Update();
	}
	//パーティクル関係
	for (int i = 0; i < Skill_Max; i++) {
		if (m_Alive[i] && m_ChestState[i] == Open) {
			ParticleEmitter::GetInstance()->FireEffect(100, { m_ChestPos[i].x,m_ChestPos[i].y + 2.0f,m_ChestPos[i].z }, 2.0f, 0.0f, { 1.0f,0.9f,0.0f,1.0f }, { 1.0f,0.9f,0.0f,1.0f });
		}
	}

	//色の設定
	ExplainBack->SetColor(m_BackColor);
	for (int i = 0; i < CompassExplain.size(); i++) {
		CompassExplain[i]->SetPosition(m_CompassTexPos[i]);
		CompassExplain[i]->SetColor(m_CompassColor[i]);
	}
	for (int i = 0; i < LibraExplain.size(); i++) {
		LibraExplain[i]->SetPosition(m_LibraTexPos[i]);
		LibraExplain[i]->SetColor(m_LibraColor[i]);
	}
	for (int i = 0; i < DushExplain.size(); i++) {
		DushExplain[i]->SetPosition(m_DushTexPos[i]);
		DushExplain[i]->SetColor(m_DushColor[i]);
	}
	for (int i = 0; i < HealExplain.size(); i++) {
		HealExplain[i]->SetPosition(m_HealTexPos[i]);
		HealExplain[i]->SetColor(m_HealColor[i]);
	}
	for (int i = 0; i < JumpExplain.size(); i++) {
		JumpExplain[i]->SetPosition(m_JumpTexPos[i]);
		JumpExplain[i]->SetColor(m_JumpColor[i]);
	}
}
//描画
const void Chest::Draw() {
	//宝箱の描画
	IKEObject3d::PreDraw();
	for (int i = 0; i < Skill_Max; i++) {
		if (m_Alive[i]) {
			if (m_ChestState[i] == Close) {
				objCloseChest[i]->Draw();
			}
			else {
				objOpenChest[i]->Draw();
			}
		}
	}

	//テキスト
	IKETexture::PreDraw(1);
	for (int i = 0; i < Skill_Max; i++) {
		if (m_Hit[i] && m_ChestState[i] == Close) {
			chestTex->Draw();
		}
	}
}
//前に書くため(主にスプライト)
const void Chest::SpriteDraw() {
	IKESprite::PreDraw();
	ExplainBack->Draw();
	for (int i = 0; i < CompassExplain.size(); i++) {
		CompassExplain[i]->Draw();
	}
	for (int i = 0; i < LibraExplain.size(); i++) {
		LibraExplain[i]->Draw();
	}
	for (int i = 0; i < DushExplain.size(); i++) {
		DushExplain[i]->Draw();
	}
	for (int i = 0; i < HealExplain.size(); i++) {
		HealExplain[i]->Draw();
	}
	for (int i = 0; i < JumpExplain.size(); i++) {
		JumpExplain[i]->Draw();
	}
}
//ミニマップの描画
const void Chest::MapDraw(int MapType, XMFLOAT4 MapColor,bool Pause, int PauseNumber) {
	for (int i = 0; i < miniSkill.size(); i++) {
		miniSkill[i]->SetColor(MapColor);
		if (PauseNumber == 1 && Pause && MapType == 1 && PlayerSkill::GetInstance()->GetCompassSkill()) {
			if (m_Alive[i] && m_ChestState[i] == Close) {
				miniSkill[i]->Draw();
			}
		}
	}
}
//ステージごとの初期化
void Chest::InitChest(int StageNumber) {
	m_Angle = 0.0f;
	//ステージにスキルが有るかどうか
	//ダッシュ
	if (StageNumber == TutoRial) {
		m_ChestPos[Compass] = { 254.0f,-220.0f,5.0f };
		m_Alive[Compass] = true;
	}
	else {
		m_Alive[Compass] = false;
	}
	//ヒール
	if (StageNumber == Map1) {
		m_ChestPos[Heal] = { 170.0f,-110.0f,5.0f };
		m_Alive[Heal] = true;
	}
	else {
		m_Alive[Heal] = false;
	}
	//コンパス
	if (StageNumber == Map2) {
		m_ChestPos[Dush] = { 190.0f,-150.0f,5.0f };
		m_Alive[Dush] = true;
	}
	else {
		m_Alive[Dush] = false;
	}
	//ライブラ
	if (StageNumber == Map3) {
		m_ChestPos[Libra] = { 277.0f,-265.5f,5.0f };
		m_Alive[Libra] = true;
	}
	else {
		m_Alive[Libra] = false;
	}
	//ジャンプ
	if (StageNumber == Map6) {
		m_ChestPos[Jump] = { 18.0f,-240.0f,5.0f };
		m_Alive[Jump] = true;
	}
	else {
		m_Alive[Jump] = false;
	}
	for (int i = 0; i < Skill_Max; i++) {
		objCloseChest[i]->SetPosition(m_ChestPos[i]);
		objOpenChest[i]->SetPosition(m_ChestPos[i]);
	}
	
}
//当たり判定
bool Chest::Collide() {
	XMFLOAT3 l_plaPos = player->GetPosition();
	for (int i = 0; i < Skill_Max; i++) {
		if (Collision::CircleCollision(l_plaPos.x, l_plaPos.y, 3.0f, m_ChestPos[i].x, m_ChestPos[i].y, 3.0f) && m_Alive[i]
			&& m_ChestState[i] == Close && player->GetAddPower() == 0.0f) {
			m_Hit[i] = true;
			player->SetCollideChest(true);
			break;
		}
		else {
			m_Hit[i] = false;
			player->SetCollideChest(false);
		}
	}

	return true;
}
//テキストが動く(sin波)
void Chest::TexMove() {
	//sin波によって上下に動く
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);

	for (int i = 0; i < Skill_Max; i++) {
		if (m_Hit[i]) {
			m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (objCloseChest[i]->GetPosition().y + 7.0f);
			m_TexPosition.x = objCloseChest[i]->GetPosition().x;
			m_TexPosition.z = objCloseChest[i]->GetPosition().z;
		}
	}

	chestTex->SetPosition(m_TexPosition);
	chestTex->Update();
}
//宝箱を開ける
void Chest::OpenChest() {
	Input* input = Input::GetInstance();
	float l_AddColor = 0.1f;
	//宝箱オープン
	if (input->TriggerButton(input->Button_A) && !m_Explain) {
		if (m_Hit[Compass] && m_ChestState[Compass] == Close) {
			m_ReadText[Compass] = true;
			m_ChestState[Compass] = Open;
			PlayerSkill::GetInstance()->SetCompassSkill(true);
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/takarabako.wav", VolumManager::GetInstance()->GetSEVolum());
		}
		else if (m_Hit[Libra] && m_ChestState[Libra] == Close) {
			m_ReadText[Libra] = true;
			m_ChestState[Libra] = Open;
			PlayerSkill::GetInstance()->SetLibraSkill(true);
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/takarabako.wav", VolumManager::GetInstance()->GetSEVolum());
		}
		else if (m_Hit[Dush] && m_ChestState[Dush] == Close) {
			m_ReadText[Dush] = true;
			m_ChestState[Dush] = Open;
			PlayerSkill::GetInstance()->SetDushSkill(true);
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/takarabako.wav", VolumManager::GetInstance()->GetSEVolum());
		}
		else if (m_Hit[Heal] && m_ChestState[Heal] == Close) {
			m_ReadText[Heal] = true;
			m_ChestState[Heal] = Open;
			PlayerSkill::GetInstance()->SetHealSkill(true);
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/takarabako.wav", VolumManager::GetInstance()->GetSEVolum());
		}
		else if (m_Hit[Jump] && m_ChestState[Jump] == Close) {
			m_ReadText[Jump] = true;
			m_ChestState[Jump] = Open;
			PlayerSkill::GetInstance()->SetJumpSkill(true);
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/takarabako.wav", VolumManager::GetInstance()->GetSEVolum());
		}
	}

	//説明が入るようになる
	for (int i = 0; i < Skill_Max; i++) {
		if (m_ReadText[i]) {
			m_Explain = true;
			player->SetReadText(true);
			break;
		}
		else {
			player->SetReadText(false);
			m_Explain = false;
		}
	}

	//ロードしたときにスキル持ってたら箱開けていたい
	if (PlayerSkill::GetInstance()->GetCompassSkill()) {
		m_ChestState[Compass] = Open;
	}

	if (PlayerSkill::GetInstance()->GetLibraSkill()) {
		m_ChestState[Libra] = Open;
	}

	if (PlayerSkill::GetInstance()->GetDushSkill()) {
		m_ChestState[Dush] = Open;
	}

	if (PlayerSkill::GetInstance()->GetHealSkill()) {
		m_ChestState[Heal] = Open;
	}

	if (PlayerSkill::GetInstance()->GetJumpSkill()) {
		m_ChestState[Jump] = Open;
	}

	//宝箱の形態が変わる
	for (int i = 0; i < Skill_Max; i++) {
		if (m_ChestState[i] == Open) {
			helper->CheckMax(m_CloseColor[i].w, m_ColorMin, -l_AddColor);
			helper->CheckMin(m_OpenColor[i].w, m_ColorMax, l_AddColor);
		}
	}
}
//マップの位置調整
void Chest::MapSet() {
	XMFLOAT2 l_LimitPos = { 4.5f,-2.4f };
	for (int i = 0; i < miniSkill.size(); i++) {	
		//敵の座標
		m_MapPos[i].x = m_ChestPos[i].x * l_LimitPos.x;
		m_MapPos[i].y = m_ChestPos[i].y * l_LimitPos.y;

		miniSkill[i]->SetPosition(m_MapPos[i]);
	}
}
//說明文の流れ
void Chest::Explain() {
	//段々說明の文字が出るようになる
	if (m_Explain) {
		helper->CheckMin(m_BackColor.w, m_ColorMax, m_ChangeAlpha);
		//テキストが出終わったら終わり
		if (CompassText() || LibraText() || DushText() || HealText() || JumpText()) {
			m_Explain = false;
		}
	}
	else {
		//表示が薄くなる
		for (int i = 0; i < CompassExplain.size(); i++) {
			helper->CheckMax(m_CompassColor[i].w, m_ColorMin, -m_ChangeAlpha);
		}

		for (int i = 0; i < LibraExplain.size(); i++) {
			helper->CheckMax(m_LibraColor[i].w, m_ColorMin, -m_ChangeAlpha);
		}

		for (int i = 0; i < DushExplain.size(); i++) {
			helper->CheckMax(m_DushColor[i].w, m_ColorMin, -m_ChangeAlpha);
		}

		for (int i = 0; i < HealExplain.size(); i++) {
			helper->CheckMax(m_HealColor[i].w, m_ColorMin, -m_ChangeAlpha);
		}

		for (int i = 0; i < JumpExplain.size(); i++) {
			helper->CheckMax(m_JumpColor[i].w, m_ColorMin, -m_ChangeAlpha);
		}
		helper->CheckMax(m_BackColor.w, m_ColorMin, -m_ChangeAlpha);
	}
}
//コンパススキルの説明文が出る
bool Chest::CompassText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Compass]) {
		m_CompassTimer++;
		if (input->TriggerButton(input->Button_A) && m_CompassTimer >= 10) {
			for (int i = 0; i < CompassExplain.size(); i++) {
				m_CompassDraw[i] = false;
			}
			m_CompassTimer = 0;
			m_ReadText[Compass] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_CompassTimer <= m_SkillTimerMax) {
		for (int i = 0; i < CompassExplain.size(); i++) {
			if (m_CompassTimer % 30 == 0 && m_CompassTimer != 0) {
				if (!m_CompassDraw[i]) {
					m_CompassDraw[i] = true;
					m_CompassTexframe[i] = 0.0f;
					m_AfterCompassTexPos[i] = {
						m_CompassTexPos[i].x,
						m_CompassTexPos[i].y - 20.0f
					};
					break;
				}
			}

			if (m_CompassDraw[i]) {
				//a値とフレームを一定数まで
				helper->CheckMin(m_CompassColor[i].w, m_ColorMax, m_ChangeAlpha);
				helper->CheckMin(m_CompassTexframe[i], m_FrameMax, m_ChangeTexFrame);
			
				m_CompassTexPos[i] = {
			Ease(In,Cubic, m_CompassTexframe[i],m_CompassTexPos[i].x, m_AfterCompassTexPos[i].x),
			Ease(In,Cubic, m_CompassTexframe[i],m_CompassTexPos[i].y,m_AfterCompassTexPos[i].y),
				};
			}
		}
	}
	return false;
}
//ライブラスキルの説明文が出る
bool Chest::LibraText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Libra]) {
		m_LibraTimer++;
		if (input->TriggerButton(input->Button_A) && m_LibraTimer >= 10) {
			for (int i = 0; i < LibraExplain.size(); i++) {
				m_LibraDraw[i] = false;
			}
			m_LibraTimer = 0;
			m_ReadText[Libra] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_LibraTimer <= m_LibraTimerMax) {
		for (int i = 0; i < LibraExplain.size(); i++) {
			if (m_LibraTimer % 30 == 0 && m_LibraTimer != 0) {
				if (!m_LibraDraw[i]) {
					m_LibraDraw[i] = true;
					m_AfterLibraTexPos[i] = {
					m_LibraTexPos[i].x,
					m_LibraTexPos[i].y - 20.0f
					};
					break;
				}
				else {

				}
			}

			if (m_LibraDraw[i]) {
				//a値とフレームを一定数まで
				helper->CheckMin(m_LibraColor[i].w, m_ColorMax, m_ChangeAlpha);
				helper->CheckMin(m_LibraTexframe[i], m_FrameMax, m_ChangeTexFrame);
				m_LibraTexPos[i] = {
			Ease(In,Cubic, m_LibraTexframe[i],m_LibraTexPos[i].x, m_AfterLibraTexPos[i].x),
			Ease(In,Cubic, m_LibraTexframe[i],m_LibraTexPos[i].y,m_AfterLibraTexPos[i].y),
				};
			}
		}
	}
	return false;
}
//ダッシュスキルの説明文が出る
bool Chest::DushText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Dush]) {
		m_DushTimer++;
		if (input->TriggerButton(input->Button_A) && m_DushTimer >= 10) {
			for (int i = 0; i < DushExplain.size(); i++) {
				m_DushDraw[i] = false;
			}
			m_DushTimer = 0;
			m_ReadText[Dush] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_DushTimer <= m_SkillTimerMax) {
		for (int i = 0; i < DushExplain.size(); i++) {
			if (m_DushTimer % 30 == 0 && m_DushTimer != 0) {
				if (!m_DushDraw[i]) {
					m_DushDraw[i] = true;
					m_AfterDushTexPos[i] = {
					m_DushTexPos[i].x,
					m_DushTexPos[i].y - 20.0f
					};
					break;
				}
			}

			if (m_DushDraw[i]) {
				//a値とフレームを一定数まで
				helper->CheckMin(m_DushColor[i].w, m_ColorMax, m_ChangeAlpha);
				helper->CheckMin(m_DushTexframe[i], m_FrameMax, m_ChangeTexFrame);
				m_DushTexPos[i] = {
			Ease(In,Cubic, m_DushTexframe[i],m_DushTexPos[i].x, m_AfterDushTexPos[i].x),
			Ease(In,Cubic, m_DushTexframe[i],m_DushTexPos[i].y,m_AfterDushTexPos[i].y),
				};
			}
		}
	}
	return false;
}
//ヒールスキルの説明文が出る
bool Chest::HealText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Heal]) {
		m_HealTimer++;
		if (input->TriggerButton(input->Button_A) && m_HealTimer >= 10) {
			for (int i = 0; i < HealExplain.size(); i++) {
				m_HealDraw[i] = false;
			}
			m_HealTimer = 0;
			m_ReadText[Heal] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_HealTimer <= m_SkillTimerMax) {
		for (int i = 0; i < HealExplain.size(); i++) {
			if (m_HealTimer % 30 == 0 && m_HealTimer != 0) {
				if (!m_HealDraw[i]) {
					m_HealDraw[i] = true;
					m_AfterHealTexPos[i] = {
					m_HealTexPos[i].x,
					m_HealTexPos[i].y - 20.0f
					};
					break;
				}
			}

			if (m_HealDraw[i]) {
				//a値とフレームを一定数まで
				helper->CheckMin(m_HealColor[i].w, m_ColorMax, m_ChangeAlpha);
				helper->CheckMin(m_HealTexframe[i], m_FrameMax, m_ChangeTexFrame);
				m_HealTexPos[i] = {
			Ease(In,Cubic, m_HealTexframe[i],m_HealTexPos[i].x, m_AfterHealTexPos[i].x),
			Ease(In,Cubic, m_HealTexframe[i],m_HealTexPos[i].y,m_AfterHealTexPos[i].y),
				};
			}
		}
	}
	return false;
}
//ジャンプスキルの説明文が出る
bool Chest::JumpText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Jump]) {
		m_JumpTimer++;
		if (input->TriggerButton(input->Button_A) && m_JumpTimer >= 10) {
			for (int i = 0; i < JumpExplain.size(); i++) {
				m_JumpDraw[i] = false;
			}
			m_JumpTimer = 0;
			m_ReadText[Jump] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_JumpTimer <= m_LibraTimerMax) {
		for (int i = 0; i < JumpExplain.size(); i++) {
			if (m_JumpTimer % 30 == 0 && m_JumpTimer != 0) {
				if (!m_JumpDraw[i]) {
					m_JumpDraw[i] = true;
					m_AfterJumpTexPos[i] = {
					m_JumpTexPos[i].x,
					m_JumpTexPos[i].y - 20.0f
					};
					break;
				}
				else {

				}
			}

			if (m_JumpDraw[i]) {
				//a値とフレームを一定数まで
				helper->CheckMin(m_JumpColor[i].w, m_ColorMax, m_ChangeAlpha);
				helper->CheckMin(m_JumpTexframe[i], m_FrameMax, m_ChangeTexFrame);
				m_JumpTexPos[i] = {
			Ease(In,Cubic, m_JumpTexframe[i],m_JumpTexPos[i].x, m_AfterJumpTexPos[i].x),
			Ease(In,Cubic, m_JumpTexframe[i],m_JumpTexPos[i].y,m_AfterJumpTexPos[i].y),
				};
			}
		}
	}
	return false;
}