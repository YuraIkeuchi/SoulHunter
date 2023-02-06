#include "TutorialText.h"
#include "Collision.h"
#include "Input.h"
#include <Easing.h>
#include "VariableCommon.h"
#include "ParticleEmitter.h"
//�ǂݍ��݂Ə�����
TutorialText::TutorialText() {
	//�Ŕ�
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
		m_BoardDraw[i] = false;
	}

	modelblock = ModelManager::GetInstance()->GetModel(ModelManager::BackRock);
	IKEObject3d* objblock_ = new IKEObject3d();
	objblock_ = IKEObject3d::Create();
	objblock_->SetModel(modelblock);
	objblock_->SetPosition(m_blockPosition);
	objblock_->SetScale(m_blockScale);
	objblock_->SetColor(m_blockColor);
	objblock_->SetTiling(20.0f);
	objblock.reset(objblock_);

	////�Ŕ�ǂނƏo�Ă��镶��
	////�f�[�^�ǂݍ���
	IKESprite::LoadTexture(5, L"Resources/2d/Tutorial/TutorialStickL.png");
	IKESprite::LoadTexture(6, L"Resources/2d/Tutorial/TutorialStickR.png");
	IKESprite::LoadTexture(7, L"Resources/2d/Tutorial/TutorialButtunB.png");
	IKESprite::LoadTexture(8, L"Resources/2d/Tutorial/TutorialRB.png");
	IKESprite::LoadTexture(9, L"Resources/2d/Tutorial/TutorialPushBack.png");
	IKESprite::LoadTexture(10, L"Resources/2d/Tutorial/TutorialPushStart.png");
	IKESprite::LoadTexture(11, L"Resources/2d/Tutorial/TutorialButtunA.png");
	
	IKESprite* TutorialSprite_[Tutorial_Max];
	for (int i = 0; i < TutorialSprite.size(); i++) {
		TutorialSprite_[i] = IKESprite::Create(i + 5, { 0.0f,0.0f });
		TutorialSprite_[i]->SetPosition({ 640.0f,200.0f });
		//TutorialSprite_[i]->SetSize({0.0f,0.0f});
		TutorialSprite_[i]->SetAnchorPoint({ 0.5f,0.5f });
		TutorialSprite[i].reset(TutorialSprite_[i]);
		m_SpriteState[i] = NoSize;
		m_TexSize[i] = { 0.0f,0.0f };
		m_AfterTexSize[i] = { 0.0f,0.0f };
	}
}
//�X�V
void TutorialText::Update() {
	//�����蔻��
	Collide();
	//��̏��
	RockState();
	//�`���[�g���A���i�s��
	Mission();
	//�p�[�e�B�N��
	BirthParticle();
	for (int i = 0; i < objboard.size(); i++) {
		objboard[i]->SetPosition(m_BoardPosition[i]);
		objboard[i]->Update();
	}
	for (int i = 0; i < TutorialSprite.size(); i++) {
		TutorialSprite[i]->SetSize(m_TexSize[i]);
	}

	objblock->SetColor(m_blockColor);
	if (m_blockColor.w != 0.0f) {
		objblock->Update();
	}

	//�G�t�F�N�g�X�V
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Update();
		}
	}

}
//�`��
const void TutorialText::Draw() {
	IKEObject3d::PreDraw();
	//�G�t�F�N�g�̕`��
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Draw();
		}
	}
	for (int i = 0; i < objboard.size(); i++) {
		if (m_BoardDraw[i]) {
			objboard[i]->Draw();
		}
	}
	if (m_blockColor.w != 0.0f) {
		objblock->Draw();
	}
}
//�X�v���C�g�̕`��
const void TutorialText::SpriteDraw() {
	IKESprite::PreDraw();
	for (int i = 0; i < TutorialSprite.size(); i++) {
		if (m_BoardDraw[i]) {
			TutorialSprite[i]->Draw();
		}
	}
}
void TutorialText::ImGuiDraw() {
	/*ImGui::Begin("Tutorial");
	ImGui::Text("MoveCount%d", m_MoveCount);
	ImGui::Text("m_BoardAlive[CameraMove]%d", m_BoardAlive[CameraMove]);
	ImGui::End();*/
}
//�����蔻��
bool TutorialText::Collide() {
	XMFLOAT3 l_plaPos = player->GetPosition();
	for (int i = 0; i < TutorialSprite.size(); i++) {
		if (Collision::CircleCollision(l_plaPos.x, l_plaPos.y, 2.5f, m_BoardPosition[i].x, m_BoardPosition[i].y, 2.5f) && m_BoardAlive[i]
			) {
			m_SpriteState[i] = WideSprite;
			break;
		}
		else {
			m_SpriteState[i] = ShrinkSprite;
		}
	}

	//�����������ǂ����ŕ`��T�C�Y�ς��
	ChangeSprite();
	return true;
}
//�}�b�v���Ƃ̊Ŕ̈ʒu
void TutorialText::InitBoard(int StageNumber) {
	effects.clear();
	for (int i = 0; i < objboard.size(); i++) {
		if (StageNumber == TutoRial) {
			m_BoardAlive[i] = false;
			m_BoardPosition[Move] = { 20.0f,-280.0f,7.0f };
			m_BoardPosition[CameraMove] = { 35.0f,-280.0f,7.0f };
			m_BoardPosition[Jump] = { 20.0f,-290.0f,7.0f };
			m_BoardPosition[Rolling] = { 35.0f,-290.0f,7.0f };
			m_BoardPosition[Pause] = { 50.0f,-290.0f,7.0f };
			m_BoardPosition[Map] = { 66.0f,-290.0f,7.0f };
			m_BoardPosition[Attack] = { 70.0f,-290.0f,7.0f };
			m_BoardDraw[i] = true;
			m_BoardAlive[Move] = true;
			m_BoardAlive[CameraMove] = true;
		}

		else {
			m_BoardAlive[i] = false;
			m_BoardDraw[i] = false;
		}
	}
}
//�`���[�g���A���̏�
void TutorialText::Mission() {
	Input* input = Input::GetInstance();
	if (m_TutorialMission == FirstMission) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left))) {
			m_MoveCount++;
		}

		if ((input->RightTiltStick(input->Up) || input->RightTiltStick(input->Down)) && (player->GetAddPower() == 0.0f) && (player->GetVelosity() == 0.0f)) {
			
		}

		m_BoardAlive[CameraMove] = false;

		if (m_MoveCount >= 100 && !m_BoardAlive[CameraMove]) {
			m_ClearCount++;
			m_MoveCount = 0;
			m_Frame[Move] = 0.0f;
			m_Frame[CameraMove] = 0.0f;
			m_BoardAlive[Move] = false;
			m_BoardState[Move] = DownBoard;
			m_BoardState[CameraMove] = DownBoard;
			for (int i = Jump; i < Attack; i++) {
				m_BoardAlive[i] = true;
				m_BoardState[i] = UpBoard;
			}
			m_TutorialMission = SecondMission;
		}
	}
	else if (m_TutorialMission == SecondMission) {
		//���ꂼ��̃^�X�N���N���A����ƃN���A�J�E���g�����Z�����
		//�W�����v
		if ((m_SpriteState[Jump] == WideSprite) && (m_BoardAlive[Jump]) && input->TriggerButton(input->Button_B)) {
			m_ClearCount++;
			m_Frame[Jump] = 0.0f;
			m_BoardAlive[Jump] = false;
		}
		//���[�����O
		if ((m_SpriteState[Rolling] == WideSprite) && (m_BoardAlive[Rolling]) && input->TriggerButton(input->Button_RB)) {
			m_ClearCount++;
			m_Frame[Rolling] = 0.0f;
			m_BoardAlive[Rolling] = false;
		}
		//�|�[�Y
		if ((m_SpriteState[Pause] == WideSprite) && (m_BoardAlive[Pause]) && input->TriggerButton(input->Select)) {
			m_ClearCount++;
			m_Frame[Pause] = 0.0f;
			m_BoardAlive[Pause] = false;
		}
		//�~�j�}�b�v
		if ((m_SpriteState[Map] == WideSprite) && (m_BoardAlive[Map]) && input->TriggerButton(input->Start)) {
			m_ClearCount++;
			m_Frame[Map] = 0.0f;
			m_BoardAlive[Map] = false;
		}


		for (int i = Jump; i < Attack; i++) {
			if (!m_BoardAlive[i]) {
				m_BoardState[i] = DownBoard;
			}
		}

		if (m_ClearCount == 5) {
			m_TutorialMission = ThirdMission;
		}
	}
	else if(m_TutorialMission == ThirdMission) {
		m_BoardAlive[Attack] = true;
		m_BoardState[Attack] = UpBoard;
	}
	else {
		player->SetTutorialFinish(true);
		for (int i = 0; i < objboard.size(); i++) {
			m_BoardAlive[i] = false;
			m_BoardState[i] = DownBoard;
		}
	}

	//�Ŕ�����
	MoveBoard();
}
//�{�[�h������
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
		else if (m_BoardState[i] == DownBoard) {
			m_AfterPosY[i] = -290.0f;
			if (m_Frame[i] < m_FrameMax) {
				m_Frame[i] += 0.01f;
			}
			else {
				m_BoardState[i] = NoMove;
				m_BoardDraw[i] = false;
				m_Frame[i] = m_FrameMin;
			}
		}
		m_BoardPosition[i].y = Ease(In, Cubic, m_Frame[i], m_BoardPosition[i].y, m_AfterPosY[i]);
	}
}
//�X�v���C�g�̑傫���ύX
void TutorialText::ChangeSprite() {
	for (int i = 0; i < TutorialSprite.size(); i++) {
		if (m_SpriteState[i] == WideSprite) {
			m_AfterTexSize[i] = {64.0f,64.0f};
		}
		else if (m_SpriteState[i] == ShrinkSprite) {
			m_AfterTexSize[i] = { 0.0f,0.0f };
		}
		m_TexSize[i] = { Ease(In, Cubic,0.5f, m_TexSize[i].x,  m_AfterTexSize[i].x),
			Ease(In, Cubic, 0.5f, m_TexSize[i].y, m_AfterTexSize[i].y),
		};
	}
}
//��̏��
void TutorialText::RockState() {
	//�ʒu�t���[�����̂ݓ����蔻������
	if (m_Damage) {
		m_DamageTimer--;
		if (m_DamageTimer < 0) {
			m_Damage = false;
			m_DamageTimer = 0;
		}
	}

	//�U���J�E���g��3�ɂȂ�����₪������
	if (m_AttackCount == 1) {
		m_blockColor.w -= 0.05f;

		if (m_blockColor.w < 0.0f) {
			m_blockColor.w = 0.0f;
			m_TutorialMission = FinishMission;
		}
	}

	//�����蔻��
	RockCollide();
}
//��̓����蔻��
bool TutorialText::RockCollide() {
	OBB1.SetParam_Pos(m_blockPosition);
	OBB1.SetParam_Scl({5.0f,5.0f,10.0f});
	OBB1.SetParam_Rot(objblock->GetMatrot());
	OBB2.SetParam_Pos(player->GetSwordPosition());
	OBB2.SetParam_Scl(player->GetSwordScale());
	OBB2.SetParam_Rot(player->GetSwordMatrot());

	//OBB�ƌ����Ŕ�����
	if (player->GetRotation().y == 90.0f) {
		if (Collision::OBBCollision(OBB1, OBB2) && (player->CheckAttack()) && (player->GetPosition().x < m_blockPosition.x) && (!m_Damage) && (m_AttackCount < 3)) {
			m_Damage = true;
			m_DamageTimer = 10;
			m_AttackCount++;
			m_Frame[Attack] = 0.0f;
			//�G�t�F�N�g�̔���
			PlayerEffect* newEffect;
			newEffect = new PlayerEffect();
			newEffect->CreateEffect("Wall", { m_blockPosition.x - 2.0f,m_blockPosition.y,0.0f }, 0);
			newEffect->Initialize();
			effects.push_back(newEffect);
			return true;
		}
		else {
			return false;
		}
	}

	return true;
}
//���[�h�Q�[����
void TutorialText::LoadGame() {
	m_TutorialMission = ThirdMission;
	for (int i = 0; i < objboard.size(); i++) {
		m_BoardDraw[i] = false;
		m_BoardAlive[i] = false;
		m_BoardState[i] = NoMove;
	}

	m_blockColor.w = 0.0f;
}
//�p�[�e�B�N��
void TutorialText::BirthParticle() {
	XMFLOAT4 s_color = { 0.8f,0.8f,0.8f,0.3f };
	XMFLOAT4 e_color = { 0.8f,0.8f,0.8f,0.3f };
	float s_scale = 3.0f;
	float e_scale = 0.0f;

	for (int i = 0; i < objboard.size(); i++) {
		if (m_BoardPosition[i].y != -280.0f && m_BoardPosition[i].y != -290.0f && m_BoardDraw[i]) {
			ParticleEmitter::GetInstance()->BoardEffect(50, { m_BoardPosition[i].x,-282.0f,m_BoardPosition[i].z}, s_scale, e_scale, s_color, e_color);
		}
	}
}