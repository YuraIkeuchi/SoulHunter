//#include "Message.h"
//#include "ImageManager.h"
//#include "Collision.h"
//#include "Easing.h"
//#include "Input.h"
//#include "imgui.h"
////モデル読み込みと初期化
//Message::Message() {
//	//手紙に近づいたときのテクスチャ
//	IKETexture* ReadTex_ = IKETexture::Create(ImageManager::ReadTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
//	ReadTex_->TextureCreate();
//	ReadTex_->SetRotation({ 0,0,0 });
//	ReadTex_->SetScale({ 0.6f,0.3f,0.3f });
//	ReadTex.reset(ReadTex_);
//
//	//手紙のテクスチャ
//	IKETexture* LetterTex_ = IKETexture::Create(ImageManager::LetterTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
//	LetterTex_->TextureCreate();
//	LetterTex_->SetRotation({ 0,0,0 });
//	LetterTex_->SetScale({ 0.5f,0.5f,0.5f });
//	LetterTex.reset(LetterTex_);
//
//	//スプライト
//	//バック
//	IKESprite* ExplainBack_;
//	ExplainBack_ = IKESprite::Create(ImageManager::ChestBack, { 0.0f,0.0f });
//	ExplainBack_->SetPosition({ 0.0f,0.0f });
//	ExplainBack.reset(ExplainBack_);
//
//	//ダッシュの手紙
//	IKESprite* LetterExplain_[DushLetter_Max];
//	for (int i = 0; i < DushLetter_Max; i++) {
//		LetterExplain_[i] = IKESprite::Create(ImageManager::LetterMessage, { 0.0f,0.0f });
//		int number_index_y = i / DushLetter_Max;
//		int number_index_x = i % DushLetter_Max;
//		LetterExplain_[i]->SetTextureRect(
//			{ static_cast<float>(number_index_x) * ExplainWidth_Cut, static_cast<float>(number_index_y) * ExplainHeight_Cut },
//			{ static_cast<float>(ExplainWidth_Cut), static_cast<float>(ExplainHeight_Cut) });
//		LetterExplain_[i]->SetSize({ ExplainWidth_Cut,ExplainHeight_Cut });
//		LetterExplain_[i]->SetAnchorPoint({ 0.5f,0.5f });
//		m_DushTexPos[i] = { 640.0f,(150.0f * i) + 150.0f };
//		LetterExplain[i].reset(LetterExplain_[i]);
//		m_DushColor[i] = { 1.0f,1.0f,1.0f,0.0f };
//		m_DushDraw[i] = false;
//	}
//
//	//エフェクト
//	MarkEffect* markEffect_ = new MarkEffect();
//	markEffect_->Initialize();
//	markEffect.reset(markEffect_);
//}
////更新
//void Message::Update() {
//	//当たり判定
//	Collide();
//	//説明文
//	Explain();
//	//宝箱を開けるテキストの動き
//	TexMove();
//	//メッセージを読む
//	ReadMessage();
//
//	LetterTex->SetPosition(m_LetterPos);
//	LetterTex->Update();
//	//色の設定
//	ExplainBack->SetColor(m_BackColor);
//	for (int i = 0; i < DushLetter_Max; i++) {
//		LetterExplain[i]->SetPosition(m_DushTexPos[i]);
//		LetterExplain[i]->SetColor(m_DushColor[i]);
//	}
//
//	markEffect->Update({ m_LetterPos.x,m_LetterPos.y,m_LetterPos.z - 3.0f});
//}
////描画
//const void Message::Draw() {
//	/*ImGui::Begin("Message");
//	ImGui::Text("m_TexPosition.y: %f", m_TexPosition.y);
//	ImGui::Text("m_ALive: %d", m_Alive);
//	ImGui::Text("m_Hit: %d", m_Hit);
//	ImGui::End();*/
//	//テキスト
//	IKETexture::PreDraw(0);
//	if (m_Alive) {
//		LetterTex->Draw();
//		markEffect->Draw();
//	}
//	if (m_Hit && m_Alive) {
//		ReadTex->Draw();
//	}
//
//	
//}
////前に書くため(主にスプライト)
//const void Message::ExplainDraw() {
//	IKESprite::PreDraw();
//	ExplainBack->Draw();
//	for (int i = 0; i < DushLetter_Max; i++) {
//		LetterExplain[i]->Draw();
//	}
//}
////ステージごとの初期化
//void Message::InitMessage(int StageNumber) {
//	m_Angle = 0.0f;
//	//ステージに手紙が有るかどうか
//	if (StageNumber == Map5 && !playerskill->GetDushSkill()) {
//		m_LetterPos = { 28.0f,-274.0f,0.0f };
//		m_Alive = true;
//	}
//	else {
//		m_LetterPos = { 0.0f,0.0f,0.0f };
//		m_Alive = false;
//	}
//}
////当たり判定
//bool Message::Collide() {
//	XMFLOAT3 l_plaPos = player->GetPosition();
//	if (Collision::CircleCollision(l_plaPos.x, l_plaPos.y, 3.0f, m_LetterPos.x, m_LetterPos.y, 3.0f) && m_Alive
//		&& player->GetAddPower() == 0.0f) {
//		m_Hit = true;
//		player->SetCollideObj(true);
//	}
//	else {
//		m_Hit = false;
//		player->SetCollideObj(false);
//	}
//	return true;
//}
////テキストが動く(sin波)
//void Message::TexMove() {
//	//sin波によって上下に動く
//	m_Angle += 1.0f;
//	m_Angle2 = m_Angle * (3.14f / 180.0f);
//	if (m_Hit) {
//		m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (m_LetterPos.y + 3.0f);
//		m_TexPosition.x = m_LetterPos.x;
//		m_TexPosition.z = m_LetterPos.z;
//	}
//
//	ReadTex->SetPosition(m_TexPosition);
//	ReadTex->Update();
//}
////手紙を読む
//void Message::ReadMessage() {
//	Input* input = Input::GetInstance();
//	//宝箱オープン
//	if (input->TriggerButton(input->Button_A) && !m_Explain && m_Alive && m_Hit) {
//		m_ReadText = true;
//	}
//
//	if (m_ReadText) {
//		m_Explain = true;
//		player->SetReadText(true);
//	}
//	else {
//		player->SetReadText(false);
//		m_Explain = false;
//	}
//}
////說明の基礎
//void Message::Explain() {
//	//段々說明の文字が出るようになる
//	if (m_Explain) {
//		if (m_BackColor.w < m_ColorMax) {
//			m_BackColor.w += m_ChangeAlpha;
//		}
//		else {
//			m_BackColor.w = m_ColorMax;
//		}
//		//テキストが出終わったら終わり
//		if (LetterExplainRead()) {
//			m_Explain = false;
//		}
//	}
//	else {
//		for (int i = 0; i < DushLetter_Max; i++) {
//			if (m_DushColor[i].w > m_ColorMin) {
//				m_DushColor[i].w -= m_ChangeAlpha;
//			}
//			else {
//				m_DushColor[i].w = m_ColorMin;
//			}
//		}
//		//色が薄くなってテキスト表示終了
//		if (m_BackColor.w > m_ColorMin) {
//			m_BackColor.w -= m_ChangeAlpha;
//		}
//		else {
//			if (!m_OpenMap) {
//
//			}
//			m_BackColor.w = m_ColorMin;
//		}
//	}
//}
////手紙のテキストの動き
//bool Message::LetterExplainRead() {
//	if (m_ReadText) {
//		m_ExplainTimer++;
//	}
//	if (m_ExplainTimer <= m_SkillTimerMax) {
//		for (int i = 0; i < DushLetter_Max; i++) {
//			if (m_ExplainTimer % 100 == 0 && m_ExplainTimer != 0) {
//				if (!m_DushDraw[i]) {
//					m_DushDraw[i] = true;
//					m_AfterDushTexPos[i] = {
//					m_DushTexPos[i].x,
//					m_DushTexPos[i].y - 20.0f
//					};
//					break;
//				}
//			}
//
//			if (m_DushDraw[i]) {
//				if (m_DushColor[i].w < m_ColorMax) {
//					m_DushColor[i].w += m_ChangeAlpha;
//				}
//				else {
//					m_DushColor[i].w = m_ColorMax;
//				}
//
//				if (m_DushTexframe[i] < m_ColorMax) {
//					m_DushTexframe[i] += m_ChangeTexFrame;
//				}
//				else {
//					m_DushTexframe[i] = m_ColorMax;
//				}
//				m_DushTexPos[i] = {
//			Ease(In,Cubic, m_DushTexframe[i],m_DushTexPos[i].x, m_AfterDushTexPos[i].x),
//			Ease(In,Cubic, m_DushTexframe[i],m_DushTexPos[i].y,m_AfterDushTexPos[i].y),
//				};
//			}
//		}
//	}
//	//一定のフレームがおわったらこの処理が終わる
//	else {
//		for (int i = 0; i < DushLetter_Max; i++) {
//			m_DushDraw[i] = false;
//		}
//		//説明文が終わると同時にマップを開く
//		minimap->SetChangeColorType(1);
//		minimap->SetMapType(0);
//		minimap->SetDushDraw(true);
//		pause->SetPauseNumber(1);
//		pause->SetIsPause(true);
//		m_ExplainTimer = 0;
//		m_ReadText = false;
//		m_Alive = false;
//		return true;
//	}
//	return false;
//}