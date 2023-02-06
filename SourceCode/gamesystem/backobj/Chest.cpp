#include "Chest.h"
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
	//スプライト読み込み
	IKESprite::LoadTexture(20, L"Resources/2d/SkillExplain/CompassExplain.png");
	IKESprite::LoadTexture(21, L"Resources/2d/SkillExplain/LibraExplain.png");
	IKESprite::LoadTexture(22, L"Resources/2d/SkillExplain/DushExplain.png");
	IKESprite::LoadTexture(23, L"Resources/2d/SkillExplain/HealExplain.png");
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
	//コンパススキル
	IKESprite* CompassExplain_[CompassExplain_Max];
	for (int i = 0; i < CompassExplain_Max; i++) {
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
	for (int i = 0; i < LibraExplain_Max; i++) {
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
	for (int i = 0; i < DushExplain_Max; i++) {
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
	for (int i = 0; i < HealExplain_Max; i++) {
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
	for (int i = 0; i < CompassExplain_Max; i++) {
		CompassExplain[i]->SetPosition(m_CompassTexPos[i]);
		CompassExplain[i]->SetColor(m_CompassColor[i]);
	}
	for (int i = 0; i < LibraExplain_Max; i++) {
		LibraExplain[i]->SetPosition(m_LibraTexPos[i]);
		LibraExplain[i]->SetColor(m_LibraColor[i]);
	}
	for (int i = 0; i < DushExplain_Max; i++) {
		DushExplain[i]->SetPosition(m_DushTexPos[i]);
		DushExplain[i]->SetColor(m_DushColor[i]);
	}
	for (int i = 0; i < HealExplain_Max; i++) {
		HealExplain[i]->SetPosition(m_HealTexPos[i]);
		HealExplain[i]->SetColor(m_HealColor[i]);
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
const void Chest::ExplainDraw() {
	IKESprite::PreDraw();
	ExplainBack->Draw();
	for (int i = 0; i < CompassExplain_Max; i++) {
		CompassExplain[i]->Draw();
	}
	for (int i = 0; i < LibraExplain_Max; i++) {
		LibraExplain[i]->Draw();
	}
	for (int i = 0; i < DushExplain_Max; i++) {
		DushExplain[i]->Draw();
	}
	for (int i = 0; i < DushExplain_Max; i++) {
		HealExplain[i]->Draw();
	}
}
//ステージごとの初期化
void Chest::InitChest(int StageNumber) {
	m_Angle = 0.0f;
	//ステージにスキルが有るかどうか
	//コンパス
	if (StageNumber == TutoRial) {
		m_ChestPos[Dush] = { 230.0f,-190.0f,5.0f };
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
	//ダッシュ
	if (StageNumber == Map6) {
		m_ChestPos[Compass] = { 18.0f,-240.0f,5.0f };
		m_Alive[Compass] = true;
	}
	else {
		m_Alive[Compass] = false;
	}
	//ヒール
	if (StageNumber == Map1) {
		m_ChestPos[Heal] = { 167.0f,-75.0f,5.0f };
		m_Alive[Heal] = true;
	}
	else {
		m_Alive[Heal] = false;
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

	//宝箱の形態が変わる
	for (int i = 0; i < Skill_Max; i++) {
		if (m_ChestState[i] == Open) {
			if (m_CloseColor[i].w > m_ColorMin) {
				m_CloseColor[i].w -= 0.1f;
			}
			else {
				if (m_OpenColor[i].w < m_ColorMax) {
					m_OpenColor[i].w += 0.1f;
				}
			}
		}
	}
}
//說明文の流れ
void Chest::Explain() {
	//段々說明の文字が出るようになる
	if (m_Explain) {
		if (m_BackColor.w < m_ColorMax) {
			m_BackColor.w += m_ChangeAlpha;
		}
		else {
			m_BackColor.w = m_ColorMax;
		}
		//テキストが出終わったら終わり
		if (CompassText() || LibraText() || DushText() || HealText()) {
			m_Explain = false;
		}
	}
	else {
		for (int i = 0; i < CompassExplain_Max; i++) {
			if (m_CompassColor[i].w > m_ColorMin) {
				m_CompassColor[i].w -= m_ChangeAlpha;
			}
			else {
				m_CompassColor[i].w = m_ColorMin;
			}
		}

		for (int i = 0; i < LibraExplain_Max; i++) {
			if (m_LibraColor[i].w > m_ColorMin) {
				m_LibraColor[i].w -= m_ChangeAlpha;
			}
			else {
				m_LibraColor[i].w = m_ColorMin;
			}
		}

		for (int i = 0; i < DushExplain_Max; i++) {
			if (m_DushColor[i].w > m_ColorMin) {
				m_DushColor[i].w -= m_ChangeAlpha;
			}
			else {
				m_DushColor[i].w = m_ColorMin;
			}
		}

		for (int i = 0; i < HealExplain_Max; i++) {
			if (m_HealColor[i].w > m_ColorMin) {
				m_HealColor[i].w -= m_ChangeAlpha;
			}
			else {
				m_HealColor[i].w = m_ColorMin;
			}
		}
		//色が薄くなってテキスト表示終了
		if (m_BackColor.w > m_ColorMin) {
			m_BackColor.w -= m_ChangeAlpha;
		}
		else {
			m_BackColor.w = m_ColorMin;
		}
	}
}
//コンパススキルの説明文が出る
bool Chest::CompassText() {
	Input* input = Input::GetInstance();
	if (m_ReadText[Compass]) {
		m_CompassTimer++;
		if (input->TriggerButton(input->Button_A) && m_CompassTimer >= 10) {
			for (int i = 0; i < CompassExplain_Max; i++) {
				m_CompassDraw[i] = false;
			}
			m_CompassTimer = 0;
			m_ReadText[Compass] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_CompassTimer <= m_SkillTimerMax) {
		for (int i = 0; i < CompassExplain_Max; i++) {
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
				if (m_CompassColor[i].w < m_ColorMax) {
					m_CompassColor[i].w += m_ChangeAlpha;
				}
				else {
					m_CompassColor[i].w = m_ColorMax;
				}

				if (m_CompassTexframe[i] < m_ColorMax) {
					m_CompassTexframe[i] += m_ChangeTexFrame;
				}
				else {
					m_CompassTexframe[i] = m_ColorMax;
				}
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
			for (int i = 0; i < LibraExplain_Max; i++) {
				m_LibraDraw[i] = false;
			}
			m_LibraTimer = 0;
			m_ReadText[Libra] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_LibraTimer <= m_LibraTimerMax) {
		for (int i = 0; i < LibraExplain_Max; i++) {
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
				if (m_LibraColor[i].w < m_ColorMax) {
					m_LibraColor[i].w += m_ChangeAlpha;
				}
				else {
					m_LibraColor[i].w = m_ColorMax;
				}

				if (m_LibraTexframe[i] < m_ColorMax) {
					m_LibraTexframe[i] += m_ChangeTexFrame;
				}
				else {
					m_LibraTexframe[i] = m_ColorMax;
				}
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
			for (int i = 0; i < DushExplain_Max; i++) {
				m_DushDraw[i] = false;
			}
			m_DushTimer = 0;
			m_ReadText[Dush] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_DushTimer <= m_SkillTimerMax) {
		for (int i = 0; i < DushExplain_Max; i++) {
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
				if (m_DushColor[i].w < m_ColorMax) {
					m_DushColor[i].w += m_ChangeAlpha;
				}
				else {
					m_DushColor[i].w = m_ColorMax;
				}

				if (m_DushTexframe[i] < m_ColorMax) {
					m_DushTexframe[i] += m_ChangeTexFrame;
				}
				else {
					m_DushTexframe[i] = m_ColorMax;
				}
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
			for (int i = 0; i < HealExplain_Max; i++) {
				m_HealDraw[i] = false;
			}
			m_HealTimer = 0;
			m_ReadText[Heal] = false;
			return true;
		}
	}
	//徐々に説明文が出る
	if (m_HealTimer <= m_SkillTimerMax) {
		for (int i = 0; i < HealExplain_Max; i++) {
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
				if (m_HealColor[i].w < m_ColorMax) {
					m_HealColor[i].w += m_ChangeAlpha;
				}
				else {
					m_HealColor[i].w = m_ColorMax;
				}

				if (m_HealTexframe[i] < m_ColorMax) {
					m_HealTexframe[i] += m_ChangeTexFrame;
				}
				else {
					m_HealTexframe[i] = m_ColorMax;
				}
				m_HealTexPos[i] = {
			Ease(In,Cubic, m_HealTexframe[i],m_HealTexPos[i].x, m_AfterHealTexPos[i].x),
			Ease(In,Cubic, m_HealTexframe[i],m_HealTexPos[i].y,m_AfterHealTexPos[i].y),
				};
			}
		}
	}
	return false;
}