#include "TutorialText.h"
#include "Collision.h"
#include <Easing.h>
#include "VariableCommon.h"
//�ǂݍ��݂Ə�����
TutorialText::TutorialText() {
	//�Ŕ�
	modelboard = ModelManager::GetInstance()->GetModel(ModelManager::Board);
	IKEObject3d* objboard_ = new IKEObject3d();
	objboard_ = IKEObject3d::Create();
	objboard_->SetModel(modelboard);
	m_BoardPosition = {35.0f,-132.0f,7.0f};
	/*m_BoardPosition = { 41.0f,-132.0f,7.0f };
	m_BoardPosition = { 29.0f,-132.0f,7.0f };*/
	objboard_->SetPosition(m_BoardPosition);
	objboard_->SetRotation({ 0.0f,180.0f,0.0f });
	objboard_->SetScale({ 3.0f,3.0f,3.0f });
	objboard.reset(objboard_);

	//�Ŕ�ǂނƏo�Ă��镶��
	//�f�[�^�ǂݍ���
	IKESprite::LoadTexture(5, L"Resources/2d/Tutorial/TutorialStick.png");
	IKESprite::LoadTexture(6, L"Resources/2d/Tutorial/TutorialButtunB.png");
	IKESprite::LoadTexture(7, L"Resources/2d/Tutorial/TutorialButtunA.png");
	IKESprite::LoadTexture(8, L"Resources/2d/Tutorial/TutorialPushBack.png");
	IKESprite::LoadTexture(9, L"Resources/2d/Tutorial/TutorialPushStart.png");
	const int TutorialCount = 2;
	IKESprite* TutorialSprite_[Tutorial_Max][TutorialAnime_Max];
	for (int i = 0; i < Tutorial_Max; i++) {
		for (int j = 0; j < TutorialAnime_Max; j++) {
			TutorialSprite_[0][j] = IKESprite::Create(5, { 0.0f,0.0f });
			TutorialSprite_[1][j] = IKESprite::Create(6, { 0.0f,0.0f });
			TutorialSprite_[2][j] = IKESprite::Create(7, { 0.0f,0.0f });
			TutorialSprite_[3][j] = IKESprite::Create(8, { 0.0f,0.0f });
			TutorialSprite_[4][j] = IKESprite::Create(9, { 0.0f,0.0f });
			int number_index_y = j / TutorialCount;
			int number_index_x = j % TutorialCount;
			TutorialSprite_[i][j]->SetTextureRect(
				{ static_cast<float>(number_index_x) * TutorialWidth_Cut, static_cast<float>(number_index_y) * TutorialHeight_Cut },
				{ static_cast<float>(TutorialWidth_Cut), static_cast<float>(TutorialHeight_Cut) });
			TutorialSprite_[i][j]->SetSize({ TutorialWidth_Cut,TutorialHeight_Cut });
			m_TexSize[i] = { 0.0f,0.0f };
			TutorialSprite_[i][j]->SetSize(m_TexSize[i]);
			TutorialSprite_[i][j]->SetAnchorPoint({ 0.5f,1.0f });
			TutorialSprite_[i][j]->SetPosition({ 640,250.0f });
			TutorialSprite[i][j].reset(TutorialSprite_[i][j]);
		}
	}
}
//�X�V
void TutorialText::Update(int TexNumber) {
	//�����蔻��
	Collide(TexNumber);
	//�X�v���C�g�̏o��
	SpriteAppear(TexNumber);
	//�A�j���[�V�����̃^�C�}�[
	if (m_AnimeTimer <= 20) {
		m_AnimeTimer++;
	}
	else {
		m_AnimeTimer = 0;
		m_AnimeCount++;
	}

	if (m_AnimeCount == 2) {
		m_AnimeCount = 0;
	}
	
	objboard->SetPosition(m_BoardPosition);
	objboard->Update();
	for (int i = 0; i < Tutorial_Max; i++) {
		for (int j = 0; j < TutorialAnime_Max; j++) {
			TutorialSprite[i][j]->SetSize(m_TexSize[i]);
		}
	}
}
//�`��
const void TutorialText::Draw() {
	
	IKESprite::PreDraw();
	for (int i = 0; i < Tutorial_Max; i++) {
			TutorialSprite[i][m_AnimeCount]->Draw();
	}
	IKEObject3d::PreDraw();
	if (m_BoardAlive) {
		objboard->Draw();
	}


}
//�����蔻��
bool TutorialText::Collide(int TexNumber) {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_BoardPosition.x, m_BoardPosition.y, 2.5f, m_PlayerPos.x, m_PlayerPos.y, 2.5f) && m_BoardAlive) {
		m_InCount[TexNumber] = true;
		m_OutCount[TexNumber] = false;
		m_TexAlive = true;
		return true;
	}
	else {
		m_OutCount[TexNumber] = true;
		m_InCount[TexNumber] = false;
		m_TexAlive = false;
		return false;
	}

	return true;
}
//�}�b�v���Ƃ̊Ŕ̈ʒu
void TutorialText::InitBoard(int StageNumber, int TexNumber) {
	if (StageNumber == TutoRial) {
		if (TexNumber == 0) {
			m_BoardAlive = true;
			m_BoardPosition = { 19.0f,-281.0f,7.0f };
		}
		else if (TexNumber == 1) {
			m_BoardAlive = true;
			m_BoardPosition = { 95.0f,-281.0f,7.0f };
		}
		else if (TexNumber == 2) {
			m_BoardAlive = true;
			m_BoardPosition = { 155.0f,-241.0f,7.0f };
		}
		else if (TexNumber == 3) {
			m_BoardAlive = true;
			m_BoardPosition = { 215.0f,-191.0f,7.0f };
		}
		else if (TexNumber == 4) {
			m_BoardAlive = true;
			m_BoardPosition = { 55.0f,-281.0f,7.0f };
		}
	}
	else {
		m_BoardAlive = false;
	}
}
//�e�N�X�`���̓���
void TutorialText::MoveTex() {
	//sin�g�ɂ���ď㉺�ɓ���
	m_Angle += 1.0f;
	m_Angle2 = m_Angle * (3.14f / 180.0f);
	m_TexPosition.y = (sin(m_Angle2) * 1.0f + 1.0f) + (m_BoardPosition.y + 7.0f);
	m_TexPosition.x = m_BoardPosition.x;
	m_TexPosition.z = m_BoardPosition.z;
}
//�X�v���C�g�̏o��
void TutorialText::SpriteAppear(int TexNumber) {
	//�`���[�g���A���̃X�v���C�g�̏o��
	if (m_InCount[TexNumber] == true && m_OutCount[TexNumber] == false) {
		if (!m_ReadTex[m_TextNumber]) {
			m_TextNumber = TexNumber;
			m_ReadTex[m_TextNumber] = true;
			m_Frame[m_TextNumber] = 0.0f;
		}
	}
	else if (m_InCount[TexNumber] == false && m_OutCount[TexNumber] == true) {
		if (m_ReadTex[m_TextNumber]) {
			m_ReadTex[m_TextNumber] = false;
			m_Frame[m_TextNumber] = 0.0f;
		}
	}

	//�C�[�W���O�ŏo������
	if (m_ReadTex[m_TextNumber]) {
		m_TexSize[m_TextNumber] = {
			Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].x,256.0f),
			Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].y,128.0f)
		};

		if (m_Frame[m_TextNumber] >= 1.0f) {
			m_Frame[m_TextNumber] = 1.0f;
		}
		else {
			m_Frame[m_TextNumber] += 0.01f;
		}
	}
	else {
		m_TexSize[m_TextNumber] = {
			Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].x,0.0f),
			Ease(In,Quad,m_Frame[m_TextNumber],m_TexSize[m_TextNumber].y,0.0f)
		};

		if (m_Frame[m_TextNumber] >= 1.0f) {
			m_Frame[m_TextNumber] = 1.0f;
		}
		else {
			m_Frame[m_TextNumber] += 0.01f;
		}
	}
}
