#include "TutorialText.h"
#include "Collision.h"
#include "Input.h"
#include <Easing.h>
#include "VariableCommon.h"
//読み込みと初期化
TutorialText::TutorialText() {
	//看板
	modelboard = ModelManager::GetInstance()->GetModel(ModelManager::Board);
	IKEObject3d* objboard_[Tutorial_Max];
	for (int i = 0; i < objboard.size(); i++) {
		objboard_[i] = new IKEObject3d();
		objboard_[i] = IKEObject3d::Create();
		objboard_[i]->SetModel(modelboard);
		m_BoardPosition[i] = {35.0f,-132.0f,7.0f};
		objboard_[i]->SetPosition(m_BoardPosition[i]);
		objboard_[i]->SetRotation({ 0.0f,180.0f,0.0f });
		objboard_[i]->SetScale({ 3.0f,3.0f,3.0f });
		objboard[i].reset(objboard_[i]);
		m_AfterPosY[i] = 0.0f;
		m_BoardState[i] = NoMove;
		m_Frame[i] = 0.0f;
	}
	////看板を読むと出てくる文字
	////データ読み込み
	//IKESprite::LoadTexture(5, L"Resources/2d/Tutorial/TutorialStick.png");
	//IKESprite::LoadTexture(6, L"Resources/2d/Tutorial/TutorialButtunB.png");
	//IKESprite::LoadTexture(7, L"Resources/2d/Tutorial/TutorialButtunA.png");
	//IKESprite::LoadTexture(8, L"Resources/2d/Tutorial/TutorialPushBack.png");
	//IKESprite::LoadTexture(9, L"Resources/2d/Tutorial/TutorialPushStart.png");
	//const int TutorialCount = 2;
	//IKESprite* TutorialSprite_[Tutorial_Max][TutorialAnime_Max];
	//for (int i = 0; i < Tutorial_Max; i++) {
	//	for (int j = 0; j < TutorialAnime_Max; j++) {
	//		TutorialSprite_[0][j] = IKESprite::Create(5, { 0.0f,0.0f });
	//		TutorialSprite_[1][j] = IKESprite::Create(6, { 0.0f,0.0f });
	//		TutorialSprite_[2][j] = IKESprite::Create(7, { 0.0f,0.0f });
	//		TutorialSprite_[3][j] = IKESprite::Create(8, { 0.0f,0.0f });
	//		TutorialSprite_[4][j] = IKESprite::Create(9, { 0.0f,0.0f });
	//		int number_index_y = j / TutorialCount;
	//		int number_index_x = j % TutorialCount;
	//		TutorialSprite_[i][j]->SetTextureRect(
	//			{ static_cast<float>(number_index_x) * TutorialWidth_Cut, static_cast<float>(number_index_y) * TutorialHeight_Cut },
	//			{ static_cast<float>(TutorialWidth_Cut), static_cast<float>(TutorialHeight_Cut) });
	//		TutorialSprite_[i][j]->SetSize({ TutorialWidth_Cut,TutorialHeight_Cut });
	//		m_TexSize[i] = { 0.0f,0.0f };
	//		TutorialSprite_[i][j]->SetSize(m_TexSize[i]);
	//		TutorialSprite_[i][j]->SetAnchorPoint({ 0.5f,1.0f });
	//		TutorialSprite_[i][j]->SetPosition({ 640,250.0f });
	//		TutorialSprite[i][j].reset(TutorialSprite_[i][j]);
	//	}
	//}
}
//更新
void TutorialText::Update() {
	//当たり判定
	Collide();
	//スプライトの出現
	SpriteAppear();
	//チュートリアル進行状況
	Mission();
	////アニメーションのタイマー
	//if (m_AnimeTimer <= 20) {
	//	m_AnimeTimer++;
	//}
	//else {
	//	m_AnimeTimer = 0;
	//	m_AnimeCount++;
	//}

	//if (m_AnimeCount == 2) {
	//	m_AnimeCount = 0;
	//}
	//
	for (int i = 0; i < objboard.size(); i++) {
		objboard[i]->SetPosition(m_BoardPosition[i]);
		objboard[i]->Update();
	}
	/*for (int i = 0; i < Tutorial_Max; i++) {
		for (int j = 0; j < TutorialAnime_Max; j++) {
			TutorialSprite[i][j]->SetSize(m_TexSize[i]);
		}
	}*/
}
//描画
const void TutorialText::Draw() {
	
	/*IKESprite::PreDraw();
	for (int i = 0; i < Tutorial_Max; i++) {
			TutorialSprite[i][m_AnimeCount]->Draw();
	}*/
	IKEObject3d::PreDraw();
	for (int i = 0; i < objboard.size(); i++) {
		objboard[i]->Draw();
		if (m_BoardAlive[i]) {
		
		}
	}
}

void TutorialText::ImGuiDraw() {
	ImGui::Begin("Tutorial");
	ImGui::Text("Alive[Move]:%d",m_BoardAlive[Move]);
	ImGui::Text("Alive[Rolling]:%d", m_BoardAlive[Rolling]);
	ImGui::Text("Pos[Move]:%f", m_BoardPosition[Move].y);
	ImGui::Text("Pos[Rolling]:%f", m_BoardPosition[Rolling].y);
	ImGui::Text("Alive[Map]:%d", m_BoardAlive[Map]);
	ImGui::Text("Alive[Attack]:%d", m_BoardAlive[Attack]);
	ImGui::Text("Pos[Map]:%f", m_BoardPosition[Map].y);
	ImGui::Text("Pos[Attack]:%f", m_BoardPosition[Attack].y);
	ImGui::End();
}
//当たり判定
bool TutorialText::Collide() {
	/*XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_BoardPosition.x, m_BoardPosition.y, 2.5f, m_PlayerPos.x, m_PlayerPos.y, 2.5f) && m_BoardAlive) {
		m_InCount[0] = true;
		m_OutCount[0] = false;
		m_TexAlive = true;
		return true;
	}
	else {
		m_OutCount[0] = true;
		m_InCount[0] = false;
		m_TexAlive = false;
		return false;
	}*/

	return true;
}
//マップごとの看板の位置
void TutorialText::InitBoard(int StageNumber) {
	for (int i = 0; i < objboard.size(); i++) {
		if (StageNumber == TutoRial) {
			m_BoardAlive[i] = false;
			m_BoardPosition[Move] = { 20.0f,-280.0f,7.0f };
			m_BoardPosition[Rolling] = { 20.0f,-290.0f,7.0f };
			m_BoardPosition[Jump] = { 35.0f,-290.0f,7.0f };
			m_BoardPosition[Pause] = { 50.0f,-290.0f,7.0f };
			m_BoardPosition[Map] = { 66.0f,-290.0f,7.0f };
			m_BoardPosition[Attack] = { 66.0f,-290.0f,7.0f };
		}

		else {
			m_BoardAlive[i] = false;
		}
	}
}
//スプライトの出現
void TutorialText::SpriteAppear() {
	////チュートリアルのスプライトの出現
	//if (m_InCount[TexNumber] == true && m_OutCount[TexNumber] == false) {
	//	if (!m_ReadTex[m_TextNumber]) {
	//		m_TextNumber = TexNumber;
	//		m_ReadTex[m_TextNumber] = true;
	//		m_Frame[m_TextNumber] = 0.0f;
	//	}
	//}
	//else if (m_InCount[TexNumber] == false && m_OutCount[TexNumber] == true) {
	//	if (m_ReadTex[m_TextNumber]) {
	//		m_ReadTex[m_TextNumber] = false;
	//		m_Frame[m_TextNumber] = 0.0f;
	//	}
	//}

	////イージングで出現する
	//if (m_ReadTex[m_TextNumber]) {
	//	m_TexSize[m_TextNumber] = {
	//		Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].x,256.0f),
	//		Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].y,128.0f)
	//	};

	//	if (m_Frame[m_TextNumber] >= 1.0f) {
	//		m_Frame[m_TextNumber] = 1.0f;
	//	}
	//	else {
	//		m_Frame[m_TextNumber] += 0.01f;
	//	}
	//}
	//else {
	//	m_TexSize[m_TextNumber] = {
	//		Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].x,0.0f),
	//		Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].y,0.0f)
	//	};

	//	if (m_Frame[m_TextNumber] >= 1.0f) {
	//		m_Frame[m_TextNumber] = 1.0f;
	//	}
	//	else {
	//		m_Frame[m_TextNumber] += 0.01f;
	//	}
	//}
}
//チュートリアルの状況
void TutorialText::Mission() {
	Input* input = Input::GetInstance();
	if (m_TutorialMission == FirstMission) {
		m_BoardAlive[Move] = true;
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left))) {
			m_MoveCount++;
		}

		if (m_MoveCount == 100) {
			m_MoveCount = 0;
			m_BoardAlive[Move] = false;
			m_BoardState[Move] = DownBoard;
			for (int i = Rolling; i < Attack; i++) {
				m_BoardAlive[i] = true;
				m_BoardState[i] = UpBoard;
			}
			m_TutorialMission = SecondMission;
		}
	}
	else if (m_TutorialMission == SecondMission) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left))) {
			m_MoveCount++;
		}
		if (m_MoveCount == 100) {
			m_MoveCount = 0;
			for (int i = Rolling; i < Attack; i++) {
				m_BoardAlive[i] = false;
				m_BoardState[i] = DownBoard;
				m_TutorialMission = ThirdMission;
			}
		}
	}
	else {
		m_BoardAlive[Attack] = true;
		m_BoardState[Attack] = UpBoard;
	}

	MoveBoard();
}

void TutorialText::MoveBoard() {
	for (int i = 0; i < objboard.size(); i++) {
		if (m_BoardState[i] == UpBoard) {
			m_AfterPosY[i] = -280.0f;
			if (m_Frame[i] < m_FrameMax) {
				m_Frame[i] += 0.01f;
			}
			else {
				m_BoardState[i] = NoMove;
				m_Frame[i] = m_FrameMin;
			}
		}
		else if(m_BoardState[i] == DownBoard) {
			m_AfterPosY[i] = -290.0f;
			if (m_Frame[i] < m_FrameMax) {
				m_Frame[i] += 0.01f;
			}
			else {
				m_BoardState[i] = NoMove;
				m_Frame[i] = m_FrameMin;
			}
		}
		m_BoardPosition[i].y = Ease(In, Cubic, m_Frame[i], m_BoardPosition[i].y, m_AfterPosY[i]);
	}
}