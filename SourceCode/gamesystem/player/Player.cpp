#include "Player.h"
#include "Input.h"
#include "ModelManager.h"
#include "ParticleManager.h"
#include "PlayerSkill.h"
#include "VariableCommon.h"
#include "VolumManager.h"
#include "ParticleEmitter.h"
#include "Audio.h"
#include <Easing.h>
using namespace DirectX;
//�ǂݍ���
Player::Player() {
	m_FollowModel = ModelManager::GetInstance()->GetModel(ModelManager::Sword);
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}
//������
bool Player::Initialize()
{
	IKEObject3d* m_FollowObject_ = new IKEObject3d();
	m_FollowObject_ = IKEObject3d::Create();
	m_FollowObject_->SetModel(m_FollowModel);
	m_FollowObject_->SetScale(m_SwordScale);
	m_FollowObject.reset(m_FollowObject_);

	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	SwordParticle* swordparticle_ = new SwordParticle();
	swordparticle_->Initialize();
	swordparticle.reset(swordparticle_);

	Shake* shake_ = new Shake();
	shake.reset(shake_);

	return true;
}
//csv���J��
void Player::OpenCsv() {
	m_PlayerFile.open("Resources/player_state/Player_State.csv");

	m_PlayerPopcom << m_PlayerFile.rdbuf();

	m_PlayerFile.close();
}
//CSV�̃��[�h
void Player::LoadCsv() {

	while (getline(m_PlayerPopcom,m_PlayerLine)) {
		//��͂��₷������
		std::istringstream line_stream(m_PlayerLine);

		std::string word;
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//��΂�
			continue;
		}
		//�e�R�}���h
		if (word.find("SCALE") == 0) {

			getline(line_stream, word, ',');
			m_Scale.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Scale.y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Scale.z = (float)std::atof(word.c_str());
		}
		else if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			m_Position.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Position.y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Position.z = (float)std::atof(word.c_str());
		}
		else if (word.find("ROT") == 0) {
			getline(line_stream, word, ',');
			m_Rotation.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Rotation.y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Rotation.z = (float)std::atof(word.c_str());
		}
		else if (word.find("DISOLVE") == 0) {
			getline(line_stream, word, ',');
			m_AddDisolve = (float)std::atof(word.c_str());
		}
		else if (word.find("ADDCOLOR") == 0) {
			getline(line_stream, word, ',');
			m_Addcolor.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Addcolor.y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Addcolor.z = (float)std::atof(word.c_str());
			m_Addcolor.w = 1.0f;
		}
		else if (word.find("HP") == 0) {
			getline(line_stream, word, ',');
			m_HP = (int)std::atof(word.c_str());
		}
		else if (word.find("INTERVAL") == 0) {
			getline(line_stream, word, ',');
			m_Interval = (int)std::atof(word.c_str());
		}
		else if (word.find("FLASH") == 0) {

			getline(line_stream, word, ',');
			m_FlashCount = (int)std::atof(word.c_str());
		}
		else if (word.find("DEATH") == 0) {
			getline(line_stream, word, ',');
			m_Death = (bool)std::atof(word.c_str());
		}
		else if (word.find("RESTIMER") == 0) {
			getline(line_stream, word, ',');
			m_RespornTimer = (int)std::atof(word.c_str());
		}
		else if (word.find("ALIVE") == 0) {
			getline(line_stream, word, ',');
			m_Alive = (bool)std::atof(word.c_str());
		}
		else if (word.find("OLDPOP") == 0) {
			getline(line_stream, word, ',');
			m_OldPos.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_OldPos.y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_OldPos.z = (float)std::atof(word.c_str());
		}
		else if (word.find("RAD") == 0) {
			getline(line_stream, word, ',');
			m_Radius.x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			m_Radius.y = (float)std::atof(word.c_str());
		}
		else if (word.find("JUMP") == 0) {
			getline(line_stream, word, ',');
			m_Jump = (bool)std::atof(word.c_str());
		}
		else if (word.find("ADDPOWER") == 0) {
			getline(line_stream, word, ',');
			m_AddPower = (float)std::atof(word.c_str());
		}
		else if (word.find("GRAVITY") == 0) {
			getline(line_stream, word, ',');
			m_Gravity = (float)std::atof(word.c_str());
			break;
		}
	}
}
//�ϐ��̏�����(�K�v�ȕ��̂�)
void Player::StateInitialize() {
	//CSV���J��
	OpenCsv();
	//CSV����l�ǂݍ���
	LoadCsv();
}
//�X�V
void Player::Update()
{
	//��̃{�[���擾
	m_HandMat = m_fbxObject->GetWorldMat();
	//m_Object->Update();
	m_OldPos = m_Position;
	
	//���[�r�[���͈ꕔ�����͏o���Ȃ�
	if (!m_Movie) {
		if (m_GoalDir == No && !m_Death && m_Alive) {
			//�ړ�
			PlayerMove();
			//�W�����v
			PlayerJump();
			//�_�b�V��
			PlayerDush();
			//���[�����O
			PlayerRolling();
			//�U��(��)
			if (!m_CollideObj) {
				PlayerAttack();
			}
			//HP��
			PlayerHeal();
		}
		else {
			//�S�[����̓���
			GoalMove();
		}
	}
	if (m_GoalDir == No && !m_Death) {
		//�_���[�W
		PlayerDamage();
		//��������
		ResPornPlayer();
	}
	//��������
	PlayerFall();

	//���̍X�V
	SwordUpdate();
	
	//�v���C���[�h
	m_PlayMode = true;
	//�S�[�������Ƃ��̏���(�܂��S�[�����Ȃ��悤��)
	if (m_ChangeInterVal) {
		m_GoalIntervalTimer++;
		if (m_GoalIntervalTimer == 120) {
			m_GoalIntervalTimer = 0;
			m_ChangeInterVal = false;
		}
	}

	//�v���C���[�����Ă鍰�̍ő��
	if (m_SoulCount >= 72.0f) {
		m_SoulCount = 72.0f;
	}

	// �s��̍X�V�Ȃ�
	//Obj_SetParam();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
	m_fbxObject->SetDisolve(Disolve);

	//�G�t�F�N�g�̍X�V
	EffectUpdate();

}
//�`��
void Player::Draw(DirectXCommon* dxCommon) {	
	//�G�t�F�N�g�̕`��
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Draw();
		}
	}
	//�_�ł��Ă邩�ǂ����ŕ`�悪�ς��
	if (m_FlashCount % 2 == 0 && m_PlayMode) {
		if (m_SwordColor.w >= 0.1f && m_HP != 0) {
			FollowObj_Draw();
		}
		if (m_AddDisolve <= 1.5f) {
			Fbx_Draw(dxCommon);
		}
	}
	//�p�[�e�B�N���̕`��
	if (m_HP != 0) {
		swordparticle->Draw();
	}
}
//Imgui
void Player::ImGuiDraw() {
	ImGui::Begin("player");
	ImGui::Text("m_PosX:%f", m_Position.x);
	ImGui::Text("m_PosY:%f", m_Position.y);
	ImGui::Text("m_PosZ:%f", m_Position.z);
	ImGui::Text("SaveTimer:%d", m_SaveTimer);
	ImGui::Text("ResTimer:%d", m_RespornTimer);
	ImGui::Text("Alive:%d", m_Alive);
	ImGui::Text("ThornHit:%d", block->GetThornHit());
	ImGui::Text("ThornDir:%d", block->GetThornDir());
	ImGui::End();
}
//���̍X�V
void Player::SwordUpdate() {
	XMVECTOR l_VectorSwordPos;
	//�s������߂�
	l_VectorSwordPos.m128_f32[0] = m_HandMat.r[3].m128_f32[0];
	l_VectorSwordPos.m128_f32[1] = m_HandMat.r[3].m128_f32[1];
	l_VectorSwordPos.m128_f32[2] = m_HandMat.r[3].m128_f32[2];
	//�ϊ�
	m_SwordPos.x = l_VectorSwordPos.m128_f32[0];
	m_SwordPos.y = l_VectorSwordPos.m128_f32[1];
	m_SwordPos.z = l_VectorSwordPos.m128_f32[2];
	
	m_SwordMatRot = m_FollowObject->GetMatrot();
	if (m_SwordEase) {
		if (m_SwordFrame < m_FrameMax) {
			m_SwordFrame += 0.1f;
		}
		else {
			m_SwordFrame = 0.0f;
			m_SwordEase = false;
			m_SwordType = NoSword;
		}
		m_SwordColor.w = Ease(In, Cubic, m_SwordFrame, m_SwordColor.w, m_SwordAfterAlpha);
	}
	m_FollowObject->SetRotation(m_SwordRotation);
	m_FollowObject->SetScale(m_SwordScale);
	m_FollowObject->SetColor(m_SwordColor);
	m_FollowObject->FollowUpdate(m_HandMat);
}
//�G�t�F�N�g�̍X�V
void Player::EffectUpdate() {
	//�p�[�e�B�N������
	BirthParticle();
	DeathBirthParticle();
	HealParticle();

	//���̃p�[�e�B�N���̏ꏊ�����߂�
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };

	//�G�t�F�N�g�X�V
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Update();
		}
	}
	swordparticle->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	for (int i = 0; i < m_SwordParticleNum; i++) {
		swordparticle->SetParticle(m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	}
	swordparticle->Update(m_SwordParticlePos, m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
}
//�v���C���[�̈ړ�
void Player::PlayerMove() {
	Input* input = Input::GetInstance();
	//�����蔻��𐸖��Ɏ�邽��
	m_LimitLeftPos = { m_Position.x - 1.3f,m_Position.y,m_Position.z };
	m_LimitRightPos = { m_Position.x + 1.3f,m_Position.y,m_Position.z };

	//�����蔻��
	if (block->LimitMapCollideCommon(m_LimitLeftPos, { 3.0f,1.0f }, m_LimitLeftPos)) {
		m_LeftLimit = true;
	}
	else {
		m_LeftLimit = false;
	}

	if (block->LimitMapCollideCommon(m_LimitRightPos, { 3.0f,1.0f }, m_LimitRightPos)) {
		m_RightLimit = true;
	}
	else {
		m_RightLimit = false;
	}

	//�`���[�g���A�����ړ������Ɍ��E������
	if (!m_TutorialFinish && m_Position.x >= 73.0f) {
		m_Position.x = 73.0f;
	}
	//�n�ʂɂ���Ԃ͍U�����[�V�����œ����~�܂�
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			//������W�����v
			if (input->LeftTiltStick(input->Right) && (!m_Dush)) {
				if (!m_RightLimit) {
					MoveCommon(0.3f, Right, 90.0f);
				}
				else {
					MoveCommon(0.0f, Right, 90.0f);
				}
			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush)) {
				if (!m_LeftLimit) {
					MoveCommon(-0.3f, Left, 270.0f);
				}
				else {
					MoveCommon(0.0f, Left, 270.0f);
				}

			}
		}
		else {
			m_Velocity = 0.0f;
			if (m_FootParticleCount == 5) {
				m_FootParticleCount = 0;
			}
		}
	}
	else {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal)) {
			//������W�����v
			if (input->LeftTiltStick(input->Right) && (!m_Dush)) {
				MoveCommon(0.3f, Right, 90.0f);

			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush)) {
				MoveCommon(-0.3f, Left, 270.0f);

			}
		}
		else {
			m_Velocity = 0.0f;
			m_FootParticleCount = 0;
		}
	}
	m_Position.x += m_Velocity;
	//�����A�j���[�V����
	WalkAnimation();

}
//�����A�j���[�V����
void Player::WalkAnimation() {
	Input* input = Input::GetInstance();
	//�������[�V����
	if (input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left) && (m_HealType == NoHeal) && (m_AddPower == 0.0f)) {
		if ((m_AnimationTimer.MoveAnimation < 3) && (m_JumpCount == 0) && (!m_AnimationStop)) {
			m_AnimationTimer.MoveAnimation++;
			m_AnimationTimer.NotAnimation = 0;
		}
		if (m_AnimationTimer.MoveAnimation == 1) {
			//�A�j���[�V�����̂��߂̂��
			m_AnimeLoop = true;
			m_AnimationType = Walk;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_AnimationType);
		}
	}
	//�~�܂��Ă���
	else {
		m_AnimationTimer.MoveAnimation = 0;
		if (m_AddPower == 0.0f) {
			m_AnimationTimer.NotAnimation++;
		}
		if (m_AnimationTimer.NotAnimation == 1 && !m_AnimationStop) {
			m_AnimeLoop = true;
			m_AnimeSpeed = 1;
			m_AnimationType = Wait;
			m_fbxObject->PlayAnimation(m_AnimationType);
		}
	}
}
//�ړ��̋��ʏ���
void Player::MoveCommon(float Velocity, int Dir, float RotationY) {
	m_Velocity = Velocity;
	m_PlayerDir = Dir;
	m_Rotation.y = RotationY;
	if (!m_Jump && m_AddPower == 0.0f) {
		m_FootParticleCount += 1;
	}
}
//�v���C���[�̃W�����v
void Player::PlayerJump() {
	Input* input = Input::GetInstance();
	//�v���C���[�W�����v����
	if (input->TriggerButton(input->Button_B) && (m_JumpCount < 3) && (m_AddPower <= 0.3f)
		&& (m_HealType == NoHeal) && (!m_Attack)) {
		m_JumpCount++;
		m_Jump = true;
		m_AddPower = 0.8f;
	
		if (m_JumpCount == 1) {
			PlayerAnimetion(FirstJump, 2);
		}
		else if (m_JumpCount == 2) {
			PlayerAnimetion(SecondJump, 2);
		}
		else if (m_JumpCount == 3) {
			PlayerAnimetion(FinalJump, 2);
			m_JumpRot = true;
			m_RotFrame = 0.0f;
		}
	}

	//�l��ڂ̓W�����v����]����
	if (m_JumpRot) {
		if (m_RotFrame < 1.0f) {
			m_RotFrame += 0.025f;
		}
		else {
			m_Rotation.x = 0.0f;
			m_RotFrame = 0.0f;
			m_JumpRot = false;
		}
		m_Rotation.x = Ease(In, Cubic, m_RotFrame, m_Rotation.x, 360.0f);
	}
	//�G�t�F�N�g�̔���
}
//�v���C���[�̗���
void Player::PlayerFall() {
	if (m_HP != 0) {
		m_Gravity = 0.02f;
	}
	else {
		m_Gravity = 0.001f;
	}
	if (m_Jump) {
		//�W�����v����
	//�_�b�V�����̂Ƃ��͏d�͂��Ȃ�
		if (!m_Dush) {
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
		}

		//�ǂƂ̓����蔻��
		if (block->PlayerMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump,
			m_AddPower) && m_Alive)
		{
			//������
			m_Jump = false;
			m_AddPower = 0.0f;
		}
	}
	else {
		m_Jump = true;
	}
	
	//�������x�̌��E
	if (m_AddPower < -1.0f) {
		m_AddPower = -1.0f;
	}
	
	//�W�����v�񐔂̃��Z�b�g
	if (m_AddPower == 0.0f && block->GetHitDown()) {
		m_JumpCount = 0;
	}
}
//�v���C���[�̍U��
void Player::PlayerAttack() {
	Input* input = Input::GetInstance();
	//�U��
	if (input->TriggerButton(input->Button_A) && !m_Attack && (m_HealType == NoHeal)) {
		if (!m_CollideChest) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Sword.wav", VolumManager::GetInstance()->GetSEVolum());
			m_Attack = true;
			//�U���񐔂ɂ���ē������ς��
			m_AttackCount++;
			if (m_AttackCount == 1) {
				m_SwordRotation = { 32.0f,91.0f,48.0f };
				PlayerAnimetion(FirstAttack, 3);
			}
			else if(m_AttackCount == 2) {
				m_AttackCount = 0;
				m_SwordRotation = { 0.0f,90.0f,60.0f };
				PlayerAnimetion(SecondAttack, 3);
			}
			//���̏���
			m_SwordEase = true;
			m_SwordFrame = 0.0f;
			m_SwordType = ArgSword;
			m_SwordAfterAlpha = 1.0f;
		}
		else {
			m_fbxObject->StopAnimation();
		}
	}	
	//�U���̃C���^�[�o��
	if (m_Attack) {
		m_AttackTimer++;
		if (m_AttackTimer <= 20) {
			m_SwordParticleNum = 1;
		}
		else if(m_AttackTimer >= 21 && m_AttackTimer <= 30) {
			m_SwordParticleNum = 7;
		}
		else {
			m_SwordParticleNum = 0;
		}
		m_SwordParticleCount = 1;

		//�U���G�t�F�N�g�̏o��
		if (m_AttackTimer == 20) {
			//�U���̌���
			//�E����
			if (m_Rotation.y == 90.0f) {
				m_AttackPos = { m_Position.x + 4.0f,m_Position.y,m_Position.z };
			}
			//������
			else if (m_Rotation.y == 270.0f) {
				m_AttackPos = { m_Position.x - 4.0f,m_Position.y,m_Position.z };
			}

			//�U�����ǂɂ��������ꍇ�ǂ���p�[�e�B�N�����o��
			if (block->AttackMapCollideCommon(m_AttackPos, { 5.5f,0.8f }, m_AttackPos)) {
				BirthEffect("Wall", m_AttackPos, m_PlayerDir);
				m_fbxObject->SetReverse(true);
			}
		}

		//���t���[���ōU���I��
		if (m_AttackTimer >= 35) {
			m_SecondTimer = 0;
			m_AttackTimer = 0;
			m_Attack = false;
			m_SwordEase = true;
			m_SwordFrame = 0.0f;
			m_SwordType = DeleteSword;
			m_SwordAfterAlpha = 0.0f;
			m_SwordParticleCount = 0;
		}
	}
	else {
		//���t���[���ȓ���������2�i�K�ڂ̍U�����o��
		if (m_AttackCount == 1) {
			m_SecondTimer++;
			if (m_SecondTimer >= 40) {
				m_AttackCount = 0;
				m_SecondTimer = 0;
			}
		}
	}
}
//�U���������邩
bool Player::CheckAttack() {
	//�U�����[�V�����ɂ���Ĕ�����t���[�����Ⴄ
	if (m_AttackCount == 1) {
		if ((m_Attack) && (m_AttackTimer >= 21 && m_AttackTimer <= 30)) {
			return true;
		}
		else {
			return false;
		}
	}
	else{
		if ((m_Attack) && (m_AttackTimer >= 22 && m_AttackTimer <= 30)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
//�v���C���[�̃_�b�V��
void Player::PlayerDush() {
	Input* input = Input::GetInstance();
	//�_�b�V������
	if ((!m_Dush) && (m_AddPower != 0.0f) && (PlayerSkill::GetInstance()->GetDushSkill())) {
		if (input->TriggerButton(input->Button_RB)) {
			m_Dush = true;
			m_AddPower = 0.0f;
			m_SideFrame = 0.0f;
			ResetAttack();
			if (m_PlayerDir == Right) {
				m_SideVelocity = 1.5f;
			}
			else if (m_PlayerDir == Left) {
				m_SideVelocity = -1.5f;
			}
			PlayerAnimetion(Dush, 4);

			BirthEffect("Dush", m_Position, m_PlayerDir);
		}
	}

	//�_�b�V�����͉��Ɏ����œ���
	if (m_Dush) {
		if (m_SideFrame < 1.0f) {
			m_SideFrame += 0.05f;
		}
		else {
			m_SideFrame = 0.0f;
			m_Dush = false;
		}

		m_SideVelocity = Ease(In, Cubic, m_SideFrame, m_SideVelocity, 0.0f);
		m_Position.x += m_SideVelocity;
	}
}
//�v���C���[�̉�]
void Player::PlayerRolling() {
	Input* input = Input::GetInstance();
	//�_�b�V������
	if ((!m_Rolling) && (m_AddPower == 0.0f) && (m_JumpCount == 0)) {
		if (input->TriggerButton(input->Button_RB)) {
			m_Rolling = true;
			m_SideFrame = 0.0f;
			ResetAttack();
			if (m_PlayerDir == Right) {
				m_SideVelocity = 1.2f;
			}
			else if (m_PlayerDir == Left) {
				m_SideVelocity = -1.2f;
			}
			PlayerAnimetion(Rolling, 2);
		}
	}

	//���[�����O���͉��Ɏ����œ���
	if (m_Rolling) {
		if (m_SideFrame < 1.0f) {
			m_SideFrame += 0.05f;
		}
		else {
			m_SideFrame = 0.0f;
			m_Rolling = false;
		}

		m_SideVelocity = Ease(In, Cubic, m_SideFrame, m_SideVelocity, 0.0f);
		m_Position.x += m_SideVelocity;
	}
}
//�v���C���[��HP��
void Player::PlayerHeal() {
	Input* input = Input::GetInstance();
	//�����Ă���Ԓ��߂�
	if (input->PushButton(input->Button_Y)  
		&& (m_HealType == NoHeal) && (m_SoulCount >= 6.0f) && (block->GetHitDown())  && (m_HP < 5) && (PlayerSkill::GetInstance()->GetHealSkill())) {
		m_HealType = UseHeal;
	}

	//�񕜃`���[�W
	if (m_HealType == UseHeal) {
		m_HealCount++;
		m_HealTimer++;
		if (m_HealTimer > 150) {
			BirthEffect("Heal", m_Position, m_PlayerDir);
			m_SoulCount -= 6.0f;
			m_HealTimer = 0;
			m_HealCount = 0;
			m_HP += 1;
			m_HealType = NoHeal;
			m_Frame = 0.0f;
		}
		else {
			//�r���Řb�����ꍇ�񕜏I��
			if (!input->PushButton(input->Button_Y) || m_Interval != 0) {
				m_HealTimer = 0;
				m_HealType = NoHeal;
				m_HealCount = 0;
			}
		}
	}
}
//�_���[�W��H�炤
void Player::PlayerDamage() {
	//�_���[�W���̒��˕Ԃ�
	if (m_HitDir == HitRight) {
		if (m_BoundPower > 0.0f) {
			m_BoundPower -= 0.05f;
		}
		else {
			m_HitDir = 0;
			m_BoundPower = 0.0f;
		}
	}
	else if (m_HitDir == HitLeft) {
		if (m_BoundPower < 0.0f) {
			m_BoundPower += 0.05f;
		}
		else {
			m_HitDir = 0;
			m_BoundPower = 0.0f;
		}
	}
	m_Position.x += m_BoundPower;
	//���񂾂Ƃ��̔���
	if (block->GetThornHit()) {
		if (m_HP > 1) {
			if (block->GetThornDir() == HitRight) {
				m_AddPower = 0.0f;
				m_BoundPower = 1.0f;
				m_HitDir = HitRight;
			}
			else if (block->GetThornDir() == HitLeft) {
				m_AddPower = 0.0f;
				m_BoundPower = -1.0f;
				m_HitDir = HitLeft;
			}
			else if (block->GetThornDir() == HitUp) {
				m_AddPower = 0.0f;
				m_BoundPower = 0.0f;
			}
			else if (block->GetThornDir() == HitDown) {
				m_AddPower = 0.7f;
				m_BoundPower = 0.0f;
			}
			m_Alive = false;
		}
		else {
			m_AddPower = 0.0f;
			m_BoundPower = 0.0f;
			if (!m_Death) {
				BirthEffect("Damege", m_Position, m_PlayerDir);
				m_HP -= 1;
				m_Death = true;
				m_Alive = false;
			}
		}
		
		block->SetThornDir(NoHit);
		block->SetThornHit(false);
	}

	//��������
	if (!m_Alive) {
		if (m_HP != 0) {
			m_Rotation.x--;
			m_RespornTimer++;
		}
	}

	//���ɂ��������Ƃ��̓���
	if (!m_Alive && m_RespornTimer == 1 && !m_Death) {
		BirthEffect("Damege", m_Position, m_PlayerDir);
		m_Jump = true;
	}

	//�_���[�W�󂯂����Ƃ̖��G����
	if (m_Interval != 0) {
		m_Interval--;

		if (m_Interval % 10 == 0) {
			m_FlashCount++;
		}
	}
	else {
		m_FlashCount = 0;
		m_Interval = 0;
	}
}
//�S�[����̓���
void Player::GoalMove() {
	if (m_GoalDir == RightGoal) {
		m_Position.x += 0.3f;
	}
	else if (m_GoalDir == LeftGoal) {
		m_Position.x -= 0.3f;
	}
}
//�S�[���̓���
bool Player::DeathMove() {
	if (m_Death) {
		block->SetThornDir(NoHit);
		block->SetThornHit(false);
		m_FlashCount = 0;
		m_Interval = 0;
		m_DeathTimer++;
		//�ŏ��ɃA�j���[�V����������
		if (m_DeathTimer == 1) {
			PlayerAnimetion(Death, 1);
		}
		//�O������
		if (m_DeathTimer >= 10) {
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.05f;
			}
			else {
				m_Frame = m_FrameMax;
			}

			m_Rotation.y = Ease(In, Cubic, m_Frame, m_Rotation.y, 180.0f);
		}

		//�V�F�C�N����
		if (m_DeathTimer == 150) {
			shake->SetShakeStart(true);
			m_ChangeColor = true;
		}
	
		shake->ShakePos(m_ShakePos.x, 10, 5, 300,10);
		shake->ShakePos(m_ShakePos.y, 10, 5, 300,10);
		if (!shake->GetShakeStart()) {
			m_ShakePos = { 0.0f,0.0f,0.0f };
		}
		else {
			//�V�F�C�N�n�܂�����p�[�e�B�N��
			m_DeathParticleCount++;
			//�f�B�]���u�ŏ���
			if (m_Addcolor.x <= 1.0f) {
				m_Addcolor.y += 0.01f;
				m_Addcolor.z += 0.01f;
			}
			else {
				m_Addcolor.y = 1.0f;
				m_Addcolor.z = 1.0f;
			}
			if (m_AddDisolve < 2.0f) {
				m_AddDisolve += 0.015f;
			}
			else {
				m_AddDisolve = 1.5f;
			}
		}
		m_Position.x += m_ShakePos.x;
		m_Position.y += m_ShakePos.y;
		if (m_AddDisolve >= 1.9f) {
			return true;
		}
	}
	return false;
}
//���
void Player::Finalize()
{
}
//�e�}�b�v���Ƃ̈ʒu������
void Player::InitPlayer(int StageNumber) {
	m_AddPower = 0.0f;
	m_FlashCount = 0;
	m_Interval = 0;
	effects.clear();
	if (StageNumber == Map1) {
		if (m_GoalDir == LeftGoal) {
			m_Position = { 275.0f,-70.0,0.0f };
		}
		else if (m_GoalDir == UpGoal) {
			m_Position = { 27.0f,-260.0,0.0f };
		}
		else if (m_GoalDir == RightGoal) {
			m_Position = { 22.0f,-135.0,0.0f };
		}
	}
	else if (StageNumber == Map2) {
		if (m_GoalDir == RightGoal) {
			m_Position = { 27.0f,-110.0f,0.0f };
		}
		else if (m_GoalDir == LeftGoal) {
			m_Position = { 279.0f,-84.0f,0.0f };
		}
	}
	else if (StageNumber == Map3) {
		if (m_GoalDir == RightGoal) {
			m_Position = { 39.0f,-70.0f,0.0f };
		}
		else if (m_GoalDir == UpGoal) {
			m_Position = { 108.0f,-280.0f,0.0f };
		}
	}
	else if (StageNumber == Map4) {
		if (m_GoalDir == DownGoal) {
			m_Position = { 117.0f,-11.0f,0.0f };
		}
		else if (m_GoalDir == RightGoal) {
			m_Position = { 20.0f,-140.0f,0.0f };
		}
	}
	else if (StageNumber == Map5) {

		if (m_GoalDir == LeftGoal) {
			m_Position = { 274.0f,-140.0f,0.0f };
		}
		else if (m_GoalDir == RightGoal) {
			m_Position = { 20.0f,-150.0f,0.0f };
		}
	}
	else if (StageNumber == Map6) {

		if (m_GoalDir == DownGoal) {
			m_Position = { 30.0f,-30.0f,0.0f };
		}
		else {
			m_Position = { 274.0f,-150.0f,0.0f };
		}
	}
	else if (StageNumber == BossMap) {
		if (m_GoalDir == DownGoal) {
			m_Position = { 175.0f,-155.0f,0.0f };
		}
		else if (m_GoalDir == LeftGoal) {
			m_Position = { 275.0f,-66.0f,0.0f };
		}
	}

	else if (StageNumber == TutoRial) {
		if (m_GoalDir == LeftGoal) {
			m_Position = { 270.0f,-120.0f,0.0f };
		}
	}
}
//�|�[�Y�J�����Ƃ��̓L�����������Ȃ�
void Player::Pause() {
	SwordUpdate();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//�G�f�B�^�[���̓���
void Player::Editor() {
	m_TutorialFinish = true;
	Input* input = Input::GetInstance();
	if (input->LeftTiltStick(input->Right)) {
		m_Position.x += 0.3f;
	}
	if (input->LeftTiltStick(input->Left)) {
		m_Position.x -= 0.3f;
	}

	if (input->LeftTiltStick(input->Up)) {
		m_Position.y += 0.3f;
	}

	if (input->LeftTiltStick(input->Down)) {
		m_Position.y -= 0.3f;
	}
	//�v���C���[�h�ł͂Ȃ�
	m_PlayMode = false;
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//�p�[�e�B�N�����o�Ă���
void Player::BirthParticle() {
	XMFLOAT4 s_color = { 0.8f,0.8f,0.8f,0.3f };
	XMFLOAT4 e_color = { 0.8f,0.8f,0.8f,0.3f };
	float s_scale = 1.0f;
	float e_scale = 0.0f;
	if (m_FootParticleCount >= 3 && m_Alive) {
		for (int i = 0; i < 3; ++i) {
			ParticleEmitter::GetInstance()->HootEffect(30, { m_Position.x,(m_Position.y - 2.0f),m_Position.z }, s_scale, e_scale, s_color, e_color);
		}
		m_FootParticleCount = 0;
	}
}
//���񂾎��̃p�[�e�B�N��
void Player::DeathBirthParticle() {
	XMFLOAT4 s_color = { 1.0f,0.9f,0.8f,1.0f };
	XMFLOAT4 e_color = { 1.0f,0.9f,0.8f,1.0f };
	float s_scale = 1.0f;
	float e_scale = 0.0f;
	float l_velocity = 0.3f;
	if (m_DeathParticleCount > 1) {
		for (int i = 0; i < 5; ++i) {
			ParticleEmitter::GetInstance()->DeathEffect(30, m_Position, s_scale, e_scale, s_color, e_color, l_velocity);
		}
		m_DeathParticleCount = 0;
	}
}
//�񕜃p�[�e�B�N��
void Player::HealParticle() {
	XMFLOAT4 s_color = { 0.5f,1.0f,0.1f,0.5f };
	XMFLOAT4 e_color = { 0.5f,1.0f,0.1f,0.5f };
	float s_scale = 2.0f;
	float e_scale = 0.0f;

	if (m_HealCount > 1) {
		ParticleEmitter::GetInstance()->HealEffect(50, { m_Position.x,m_Position.y - 2.0f,m_Position.z }, s_scale, e_scale, s_color, e_color);
		m_HealCount = 0;
	}
}
//�U�����Z�b�g
void Player::ResetAttack() {
	//�U�������Z�b�g�����
	m_SecondTimer = 0;
	m_AttackTimer = 0;
	m_Attack = false;
	m_SwordEase = true;
	m_SwordFrame = 0.0f;
	m_SwordType = DeleteSword;
	m_SwordAfterAlpha = 0.0f;
	m_SwordParticleNum = 0;
}
//�A�j���[�V�����̋��ʕϐ�
void Player::PlayerAnimetion(int Number, int AnimeSpeed) {
	m_AnimationType = Number;
	m_AnimeLoop = false;
	m_AnimationTimer.MoveAnimation = 0;
	m_AnimeSpeed = AnimeSpeed;
	m_AnimationStop = true;
	m_fbxObject->PlayAnimation(m_AnimationType);
}
//�����Ԃ������̈ʒu
void Player::ResPornPlayer() {
	//���O�܂ł̈ʒu��ۑ�����
	if (m_AddPower == 0.0f && !block->GetThornHit() && block->GetHitDown()) {
		m_SaveTimer++;
	}
	//�����ŕۑ�
	if (m_SaveTimer == 20) {
		m_RespornPos = m_Position;
		m_SaveTimer = 0;
	}
	//����
	if (!m_Alive) {
		if (m_RespornTimer == 100) {
			m_HP -= 1;
			m_Alive = true;
			m_RespornTimer = 0;
			m_Jump = false;
			block->SetThornHit(false);
			m_Rotation.x = 0.0f;
			m_Position = m_RespornPos;
		}
	}
}
//���[�h�����Ƃ��̏�����
void Player::LoadPlayer(const XMFLOAT3& StartPos) {
	m_Position = StartPos;
	m_fbxObject->SetPosition(m_Position);
	m_TutorialFinish = true;
	block->SetThornDir(0);
	block->SetThornHit(false);
}
//�v���C���[���G�ɂ��������u�Ԃ̔���
void Player::PlayerHit(const XMFLOAT3& pos) {
	PlayerAnimetion(Damage, 3);
	m_HP -= 1;
	m_Interval = 100;
	ResetAttack();
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = HitRight;//�E���ɒe�����
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = HitLeft;
	}

	if (m_HP == 0 && !m_Death) {
		m_Death = true;
		m_Alive = false;
	}

	//�G�t�F�N�g����
	BirthEffect("Damege", m_Position, m_PlayerDir);
}
//�v���C���[���G�ɂ��������u�Ԃ̔���
void Player::PlayerThornHit(const XMFLOAT3& pos) {
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = HitRight;//�E���ɒe�����
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = HitLeft;
	}
}
//�G�t�F�N�g����
void Player::BirthEffect(const std::string& newname, XMFLOAT3 pos, int dir) {
	PlayerEffect* newEffect;
	newEffect = new PlayerEffect();
	newEffect->CreateEffect(newname, pos, dir);
	newEffect->Initialize();
	effects.push_back(newEffect);
}
//�����V�[���̍X�V
void Player::IntroductionUpdate(int Timer) {
	//�t���[�����œ��������܂�
	if (Timer == 1) {
		m_Position = { 0.0f,2.2f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	//��莞�ԗ�������O�ɂ�����
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimationTimer.MoveAnimation++;
	
	if (m_AnimationTimer.MoveAnimation == 1) {
		//�A�j���[�V�����̂��߂̂��
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}

	//���̍X�V
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//�����V�[���̕`��
void Player::IntroductionDraw(DirectXCommon* dxCommon) {
	//FollowObj_Draw();
	Fbx_Draw(dxCommon);
	//FollowObj_Draw();
}
//�{�X�o��V�[���̍X�V
void Player::BossAppUpdate(int Timer) {
	m_AnimeLoop = true;
	m_AnimeSpeed = 1;
	m_AnimationType = Wait;
	m_fbxObject->PlayAnimation(m_AnimationType);
	m_fbxObject->SetPosition({ 0.0f,8.0f,0.0f });
	m_fbxObject->SetRotation({ 0.0f,0.0f,0.0f });
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
void Player::BossAppDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
//�{�X�I���V�[���̍X�V
void Player::BossEndUpdate(int Timer) {
	m_AnimeLoop = true;
	m_AnimeSpeed = 1;
	m_AnimationType = Wait;
	m_fbxObject->PlayAnimation(m_AnimationType);
	m_fbxObject->SetPosition({ 0.0f,8.0f,0.0f });
	m_fbxObject->SetRotation({ 0.0f,0.0f,0.0f });
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
void Player::BossEndDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
//�N���A�V�[���̍X�V
void Player::ClearUpdate(int Timer) {
	//�t���[�����œ��������܂�
	if (Timer == 1) {
		m_Position = { 0.0f,5.0f,-250.0f };
		m_Rotation = { 0.0f,0.0f,0.0f };
	}
	m_Position.z += 0.3f;
	m_AnimationTimer.MoveAnimation++;

	if (m_AnimationTimer.MoveAnimation == 1) {
		//�A�j���[�V�����̂��߂̂��
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//�����V�[���̕`��
void Player::ClearDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}