#include "Player.h"
#include "Input.h"
#include "imgui.h"
#include "ModelManager.h"
#include "IKEFbxLoader.h"
#include "ParticleManager.h"
#include "Audio.h"
#include <Easing.h>
using namespace DirectX;
bool Player::s_UseCompass = false;
bool Player::s_UseDush = false;
bool Player::s_UseLibra = false;
bool Player::s_UseHeal = false;
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
	m_FollowObject_->SetScale({ 2.5f,2.5f,2.5f });
	m_FollowObject.reset(m_FollowObject_);

	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	ParticleTex* particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);

	SwordParticle* swordparticle_ = new SwordParticle();
	swordparticle_->Initialize();
	swordparticle.reset(swordparticle_);

	ParticleHeal* particleheal_ = new ParticleHeal();
	particleheal_->Initialize();
	particleheal.reset(particleheal_);

	/*PlayerWing* playerwing_ = new PlayerWing();
	playerwing_->Initialize();
	playerwing.reset(playerwing_);*/

	return true;
}
//�ϐ��̏�����
void Player::StateInitialize() {
	m_Scale = { 3.0f, 3.0f, 3.0f };
	m_Position = { 20.0f,-100.0f,0.0f };
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_HP = 5;
	//�v���C���[�֌W
	m_OldPlayerPos = { 0, 0, 0 };
	m_Radius.x = 1.0f * m_Scale.x;
	m_Radius.y = 0.7f * m_Scale.y;
	m_Jump = false;
	m_AddPower = 0;
	m_Gravity = 0.02f;
}
//�X�V
void Player::Update()
{
	//��̃{�[���擾
	m_HandMat = m_fbxObject->GetWorldMat();
	Input* input = Input::GetInstance();
	//m_Object->Update();
	m_OldPlayerPos = m_Position;
	//���[�r�[���͈ꕔ�����͏o���Ȃ�
	if (!m_Movie) {
		if (m_GoalDir == No) {
			//�ړ�
			PlayerMove();
			//�W�����v
			PlayerJump();
			//�_�b�V��
			PlayerDush();
			//�U��(��)
			if (m_AttackType == Sword && !m_CollideObj) {
				PlayerAttack();
			}

			//�e������
			else if (m_AttackType == Shot) {
				PlayerShot();
			}
			//�K�E�Z
			else if (m_AttackType == Special) {
				PlayerSpecial();
			}
			//HP��
			PlayerHeal();
			//�_���[�W
			PlayerDamage();
			//��������
			ResPornPlayer();
			//�G�t�F�N�g����
			JumpArgment();
			AttackArgment();
		}
		else {
			//�S�[����̓���
			GoalMove();
		}
	}

	//��������
	PlayerFall();
	//�p�[�e�B�N������
	BirthParticle();
	//���̍X�V
	SwordUpdate();
	
	//�v���C���[�h
	m_PlayMode = true;
	//�S�[�������Ƃ��̏���(�܂��S�[�����Ȃ��悤��)
	if (m_ChangeInterVal) {
		m_IntervalTimer++;
		if (m_IntervalTimer == 120) {
			m_IntervalTimer = 0;
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

	//�H�֌W
	WingUpdate();
	//�G�t�F�N�g�̍X�V
	EffectUpdate();
}
//���̍X�V
void Player::SwordUpdate() {
	//�s������߂�
	m_VectorSwordPos.m128_f32[0] = m_HandMat.r[3].m128_f32[0];
	m_VectorSwordPos.m128_f32[1] = m_HandMat.r[3].m128_f32[1];
	m_VectorSwordPos.m128_f32[2] = m_HandMat.r[3].m128_f32[2];
	//�ϊ�
	m_SwordPos.x = m_VectorSwordPos.m128_f32[0];
	m_SwordPos.y = m_VectorSwordPos.m128_f32[1];
	m_SwordPos.z = m_VectorSwordPos.m128_f32[2];
	
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
	m_FollowObject->SetColor(m_SwordColor);
	m_FollowObject->FollowUpdate(m_HandMat);
}
//�G�t�F�N�g�̍X�V
void Player::EffectUpdate() {
	//�p�[�e�B�N���̃J�E���g���̍X�V
	if (m_ParticleCount > 3) {
		m_ParticleCount = 0;
	}

	if (m_HealCount > 3) {
		m_HealCount = 0;
	}
	//�p�[�e�B�N�����o��
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };

	//�p�[�e�B�N���֌W
	particletex->Update(m_ParticlePos, m_ParticleCount, 3, m_ParticleNumber);
	particleheal->SetStartColor({ 0.5f,1.0f,0.1f,1.0f });
	particleheal->Update({ m_Position.x,m_Position.y - 1.0f,m_Position.z }, m_HealCount, 3);
	swordparticle->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	for (int i = 0; i < m_SwordParticleNum; i++) {
		swordparticle->SetParticle(m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	}
	swordparticle->Update(m_SwordParticlePos, m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	//�G�t�F�N�g�֌W
	for (JumpEffect* jumpeffect : jumpeffects) {
		if (jumpeffect != nullptr) {
			jumpeffect->Update(m_Position);
		}
	}
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Update();
		}
	}
}
//�H�֌W
void Player::WingUpdate() {
	//m_WingPosition = m_Position;
	////�H
	//if (m_PlayerDir == Left) {
	//	playerwing->SetPosition({ m_Position.x,m_Position.y,m_Position.z });
	//	playerwing->SetDir(0);
	//}
	//else {
	//	playerwing->SetPosition({ m_Position.x,m_WingPosition.y,m_Position.z });
	//	playerwing->SetDir(1);
	//}

	//playerwing->Update();
}
//�v���C���[�̈ړ�
void Player::PlayerMove() {
	Input* input = Input::GetInstance();
	//�n�ʂɂ���Ԃ͍U�����[�V�����œ����~�܂�
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			//������W�����v
			if (input->LeftTiltStick(input->Right) && (!m_Dush) && (!m_Special) && (m_Alive)) {
				MoveCommon(0.3f, Right, 90.0f);

			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush) && (!m_Special) && (m_Alive)) {
				MoveCommon(-0.3f, Left, 270.0f);

			}
			particletex->SetParticleBreak(true);
		}
		else {
			m_Velocity = 0.0f;
			if (m_FoodParticleCount == 5.0f) {
				m_FoodParticleCount = 0.0f;
			}
		}
	}
	else {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal)) {
			//������W�����v
			if (input->LeftTiltStick(input->Right) && (!m_Dush) && (!m_Special) && (m_Alive)) {
				MoveCommon(0.3f, Right, 90.0f);

			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush) && (!m_Special) && (m_Alive)) {
				MoveCommon(-0.3f, Left, 270.0f);

			}
			particletex->SetParticleBreak(true);
		}
		else {
			m_Velocity = 0.0f;
			m_FoodParticleCount = 0.0f;
		}
	}
	m_Position.x += m_Velocity;
	particletex->SetParticleBreak(true);

	//�����A�j���[�V����
	WalkAnimation();

}
//�����A�j���[�V����
void Player::WalkAnimation() {
	Input* input = Input::GetInstance();
	//�������[�V����
	if (input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left) && (m_HealType == NoHeal) && (m_AddPower == 0.0f)) {
		if ((m_AnimeTimer < 3) && (m_JumpCount == 0) && (!m_AnimationStop) && (!m_Special)) {
			m_AnimeTimer++;
		}
		if (m_AnimeTimer == 1) {
			//�A�j���[�V�����̂��߂̂��
			m_AnimeLoop = true;
			m_Number = 1;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}
	//�~�܂��Ă���
	else {
		m_AnimeTimer = 0;
		if (m_AnimeTimer == 0 && !m_AnimationStop) {
			m_AnimeLoop = true;
			m_AnimeSpeed = 1;
			m_Number = 3;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}
}
//�ړ��̋��ʏ���
void Player::MoveCommon(float Velocity, int Dir, float RotationY) {
	m_Velocity = Velocity;
	m_PlayerDir = Dir;
	m_Rotation.y = RotationY;
	if (!m_Jump && m_AddPower == 0.0f) {
		m_FoodParticleCount += 0.5f;
		m_ParticlePos.x = m_Position.x;
		m_ParticlePos.y = m_Position.y - 1.5f;
		m_ParticlePos.z = m_Position.z;
		m_FoodParticlePos = {
			m_Position.x,
			m_Position.y - 1.0f,
			m_Position.z,
		};
	}
}
//�v���C���[�̃W�����v
void Player::PlayerJump() {
	Input* input = Input::GetInstance();
	//�v���C���[�W�����v����
	if (input->TriggerButton(input->Button_B) && (m_JumpCount < 4) && (m_AddPower <= 0.3f) && (!m_Special)
		&& (m_HealType == NoHeal) && (m_Alive)) {
		m_JumpCount++;
		m_Jump = true;
		m_ParticleCount = 0;
		m_WingDeleteCount = 0;
		m_AddPower = 0.8f;
		m_JumpArgment = true;
		if (m_JumpCount == 1) {
			PlayerAnimetion(2, 2);
		}
		else if (m_JumpCount == 2) {
			PlayerAnimetion(5, 2);
		}
		else if (m_JumpCount == 3) {
			PlayerAnimetion(6, 2);
		}
		else if (m_JumpCount == 4) {
			PlayerAnimetion(7, 2);
			m_JumpRot = true;
			m_RotFrame = 0.0f;
		}
		////�W�����v�񐔂Ńv���C���[�̉H���ω�����
		//playerwing->SetAnimation(true);
		//playerwing->SetEaseStart(true);
		//playerwing->SetFrame(0.0f);
		//playerwing->SetAfterScale({ 0.005f,0.005f,0.005f });
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

	m_WingPosition.y = m_Position.y;
	if (m_Jump) {
		//�W�����v����
	//�_�b�V�����̂Ƃ��͏d�͂��Ȃ�
		if (!m_Dush && !m_Special) {
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
			m_WingPosition.y += m_AddPower;
		}

		//�ǂƂ̓����蔻��
		if (block->PlayerMapCollideCommon(m_Position, m_Radius, m_OldPlayerPos, m_Jump,
			m_AddPower) && m_Alive)
		{
			//������
			m_Gravity = 0.02f;
			m_Jump = false;
			m_AddPower = 0.0f;
		}

		//if (m_JumpCount != 0) {
		//	m_WingDeleteCount++;
		//}

		//if (m_WingDeleteCount == 15) {
		//	playerwing->SetEaseStart(true);
		//	playerwing->SetFrame(0.0f);
		//	playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });
		//	m_WingDeleteCount = 0;
		//}
		//if(m_JumpCount)
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
	/*	playerwing->SetEaseStart(true);
		playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });*/
	}
}
//�v���C���[�̍U��
void Player::PlayerAttack() {
	Input* input = Input::GetInstance();
	//�U��
	//�U���̌���
	if (input->TriggerButton(input->Button_A) && !m_Attack && (m_HealType == NoHeal) && (m_Alive)) {
		if (!m_CollideChest) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Sword.wav", VolumManager::GetInstance()->GetSEVolum());
			m_Attack = true;
			if (m_Rotation.y == 90.0f) {
				m_AttackPos = { m_Position.x + 4.0f,m_Position.y,m_Position.z };
			}
			else if (m_Rotation.y == 270.0f) {
				m_AttackPos = { m_Position.x - 4.0f,m_Position.y,m_Position.z };
			}
			PlayerAnimetion(0, 2);
			m_SwordEase = true;
			m_SwordFrame = 0.0f;
			m_SwordType = ArgSword;
			m_SwordAfterAlpha = 1.0f;
		/*	playerwing->SetEaseStart(true);
			playerwing->SetFrame(0.0f);
			playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });*/
		}
		else {
			m_AnimeLoop = true;
			m_AnimeSpeed = 2;
			m_Number = 3;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}	
	//�U���̃C���^�[�o��
	if (m_Attack) {
		if (m_AttackTimer <= 10) {
			m_SwordParticleNum = 1;
		}
		else if(m_AttackTimer >= 15 && m_AttackTimer <= 20) {
			m_SwordParticleNum = 7;
		}
		else {
			m_SwordParticleNum = 0;
		}
		m_SwordParticleCount = 1;
		//�U���G�t�F�N�g�̏o��
		if (m_AttackTimer == 8) {
			m_AttackArgment = true;
		}
		m_AttackTimer++;
		
		if (m_AttackTimer >= 30) {
			m_AttackTimer = 0;
			m_Attack = false;
			m_SwordEase = true;
			m_SwordFrame = 0.0f;
			m_SwordType = DeleteSword;
			m_SwordAfterAlpha = 0.0f;
			m_SwordParticleCount = 0;
		}

		if (m_AddPower == 0.0f) {
			m_FoodParticleCount += 0.25f;
			m_FoodParticlePos = {
		m_AttackPos.x,
		m_AttackPos.y - 2.0f,
		m_AttackPos.z,
			};
		}
	}
}
//�v���C���[�̃_�b�V��
void Player::PlayerDush() {
	Input* input = Input::GetInstance();
	//�_�b�V������
	if ((!m_Dush) && (!m_Special) && (m_SoulCount >= 2.0f) && (m_AddPower != 0.0f) && (m_Alive)) {
		if (input->TriggerButton(input->Button_RB)) {
			m_SoulCount -= 2.0f;
			m_AddPower = 0.0f;
			m_Dush = true;
			m_ParticlePos = m_Position;
			m_ParticleCount = 3;
			particletex->SetParticleBreak(false);
			if (m_PlayerDir == Right) {
				//m_Rotation.y = 180.0f;
				m_DushDir = DushRight;
			}
			else if (m_PlayerDir == Left) {
				//m_Rotation.y = 0.0f;
				m_DushDir = DushLeft;
			}
			PlayerAnimetion(8, 2);
		}
	}

	if (m_Dush) {
		m_DushTimer--;
		if (m_DushDir == DushRight) {
			m_Position.x += 1.5f;
		}
		else if (m_DushDir == DushLeft) {
			m_Position.x -= 1.5f;
		}

		if (m_DushTimer == 0) {
			m_DushDir = NoDush;
			m_Dush = false;
			m_DushTimer = 15;
		}
	}
}
//�e��ł�
void Player::PlayerShot() {
	Input* input = Input::GetInstance();
	//�U��
	//�U���̌���
	if (input->TriggerButton(input->Button_A) && (!playerbullet->GetAlive()) && (m_SoulCount >= 10.0f)) {
		Audio::GetInstance()->PlayWave("Resources/Sound/SE/Decision.wav", VolumManager::GetInstance()->GetSEVolum());
		m_SoulCount -= 10.0f;
		playerbullet->SetAlive(true);
		playerbullet->SetPosition(m_Position);
		if (m_Rotation.y == 90.0f) {
			playerbullet->SetAddSpeed(1.0f);
		}
		else {
			playerbullet->SetAddSpeed(-1.0f);
		}
	}

	m_BulletDistance = fabs(m_Position.x) - fabs(playerbullet->GetPosition().x);
	m_BulletDistance = fabs(m_BulletDistance);
	if ((playerbullet->GetAlive()) && (m_BulletDistance >= 80.0f)) {
		playerbullet->SetAlive(false);
	}
}
//�K�E�Z
void Player::PlayerSpecial() {
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Button_A) && (m_AddPower == 0.0f) && (!m_Special) && (m_SoulCount >= 25.0f)) {
		m_SoulCount -= 25.0f;
		m_Special = true;
		m_Frame = 0.0f;
		m_AfterPosY = m_Position.y + 8.0f;
		m_SpecialCount = 0;
	}

	//�K�E�Z
	if (m_Special) {
		if (m_SpecialCount == 0) {
			if (m_Frame < 1.0f) {
				m_Frame += 0.025f;
			}
			else {
				m_SpecialCount = 1;
				m_AfterPosY = m_Position.y - 8.0f;
				m_Frame = 0.0f;
				m_Rotation.z = 0.0f;
			}
			m_CameraDistance = Ease(In, Quad, m_Frame, m_CameraDistance, 10.0f);
			m_Rotation.z = Ease(In, Quad, m_Frame, m_Rotation.z, 360.0f);
		}
		else {
			if (m_Frame < 1.0f) {
				m_Frame += 0.2f;
			}
			else {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/Decision.wav", VolumManager::GetInstance()->GetSEVolum());
				m_SpecialCount = 0;
				m_Frame = 0.0f;
				m_Special = false;
				m_SpecialEffect = true;
				m_ParticleCount = 3;
				particletex->SetParticleBreak(false);
			}
			m_CameraDistance = Ease(In, Quad, m_Frame, m_CameraDistance, 0.0f);
		}
		m_Position.y = Ease(In, Quad, m_Frame, m_Position.y, m_AfterPosY);
	}
}
//�v���C���[��HP��
void Player::PlayerHeal() {
	Input* input = Input::GetInstance();
	//�����Ă���Ԓ��߂�
	if (input->PushButton(input->Button_Y) && (s_UseHeal) && (m_HP <= 4) && (!m_Special)
		&& (m_HealType == NoHeal) && (m_SoulCount >= 6.0f) && (block->GetHitDown())) {
		m_HealType = InterVal;
	}

	if (m_HealType == InterVal) {
		m_HealCount++;
		m_CameraDistance += 0.1f;
		m_HealTimer++;
		if (m_HealTimer > 100) {
			m_SoulCount -= 6.0f;
			m_HealTimer = 0;
			m_HealCount = 0;
			m_HP += 1;
			m_HealType = Invocation;
			m_Frame = 0.0f;
		}
		else {
			if (!input->PushButton(input->Button_Y) || m_Interval != 0) {
				m_HealTimer = 0;
				m_HealType = Fail;
				m_Frame = 0.0f;
				m_HealCount = 0;
			}
		}
	}
	else if (m_HealType == Invocation) {
		particleheal->SetHeal(true);
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
		}
		else {
			m_HealType = NoHeal;
		}
		m_CameraDistance = Ease(In, Quad, m_Frame, m_CameraDistance, 0.0f);
	}
	else if (m_HealType == Fail) {
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
		}
		else {
			m_HealType = NoHeal;
		}
		m_CameraDistance = Ease(In, Quad, m_Frame, m_CameraDistance, 0.0f);
	}

}
//�_���[�W��H�炤
void Player::PlayerDamage() {

	//�_���[�W���̒��˕Ԃ�
	if (m_HitDir == 1) {
		if (m_BoundPower > 0.0f) {
			m_BoundPower -= 0.05f;
		}
		else {
			m_HitDir = 0;
			m_BoundPower = 0.0f;
		}
	}
	else if (m_HitDir == 2) {
		if (m_BoundPower < 0.0f) {
			m_BoundPower += 0.05f;
		}
		else {
			m_HitDir = 0;
			m_BoundPower = 0.0f;
		}
	}
	m_Position.x += m_BoundPower;

	//��������
	if (!m_Alive) {
		m_RespornTimer++;
		m_Rotation.z--;
	}

	//���񂾂Ƃ��̔���
	if (block->GetThornHit()) {
		m_Alive = false;
		if (block->GetThornDir() == 1) {
			m_AddPower = 0.0f;
			m_BoundPower = 0.0f;
		}
		else if (block->GetThornDir() == 2) {
			m_AddPower = 0.7f;
			m_BoundPower = 0.0f;
		}
		else if (block->GetThornDir() == 3) {
			m_AddPower = 0.0f;
			m_BoundPower = 1.0f;
			m_HitDir = 1;
		}
		else if (block->GetThornDir() == 4) {
			m_AddPower = 0.0f;
			m_BoundPower = -1.0f;
			m_HitDir = 2;
		}
		block->SetThornDir(0);
		block->SetThornHit(false);
	}

	//���ɂ��������Ƃ��̓���
	if (!m_Alive && m_RespornTimer == 1) {
		m_Effect = true;
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
//�G�t�F�N�g����
void Player::JumpArgment() {
	if (m_JumpArgment) {
		JumpEffect* newJumpEffect;
		newJumpEffect = new JumpEffect();
		newJumpEffect->Initialize();
		jumpeffects.push_back(newJumpEffect);
		m_JumpArgment = false;
	}
}
//��ɓ���
void Player::AttackArgment() {
	if (m_AttackArgment) {
		AttackEffect* newAttackEffect;
		newAttackEffect = new AttackEffect();
		newAttackEffect->Initialize();
		newAttackEffect->SetEffect(m_AttackPos, m_PlayerDir);
		attackeffects.push_back(newAttackEffect);
		m_AttackArgment = false;
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
//�`��
void Player::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("player");
	ImGui::SetWindowPos(ImVec2(1000, 450));
	ImGui::SetWindowSize(ImVec2(280, 300));
	ImGui::Text("m_Attack:%f", m_Rotation.x);
	ImGui::End();

	//�G�t�F�N�g�֌W
	for (JumpEffect* jumpeffect : jumpeffects) {
		if (jumpeffect != nullptr) {
			jumpeffect->Draw();
		}
	}
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Draw();
		}
	}

	//m_Object->Draw();
	if (m_FlashCount % 2 == 0 && m_PlayMode) {
		//Obj_Draw();
		if (m_SwordColor.w >= 0.1f) {
			FollowObj_Draw();
		}
		Fbx_Draw(dxCommon);
		//playerwing->Draw(dxCommon);
	}
	particleheal->Draw();
	particletex->Draw();
	swordparticle->Draw();
	//particleobj->ImGuiDraw();
	//object1->Draw(dxCommon->GetCmdList());
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
	jumpeffects.clear();
	attackeffects.clear();
	if (StageNumber == Map1) {
		if (m_GoalDir == LeftGoal) {
			m_Position = { 275.0f,-110.0,0.0f };
		}
		else if (m_GoalDir == UpGoal) {
			m_Position = { 49.0f,-220.0,0.0f };
		}
		else if (m_GoalDir == RightGoal) {
			m_Position = { 24.0f,-191.0,0.0f };
		}
	}
	else if (StageNumber == Map2) {
		if (m_GoalDir == RightGoal) {
			m_Position = { 27.0f,-110.0f,0.0f };
		}
		else if (m_GoalDir == LeftGoal) {
			m_Position = { 267.0f,-70.0f,0.0f };
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
			m_Position = { 40.0f,-30.0f,0.0f };
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
			m_Position = { 270.0f,-190.0f,0.0f };
		}
	}

	m_AnimeLoop = true;
	m_AnimeSpeed = 2;
	m_Number = 3;
	m_fbxObject->PlayAnimation(m_Number);
}
//�|�[�Y�J�����Ƃ��̓L�����������Ȃ�
void Player::Pause() {
	SwordUpdate();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//�G�f�B�^�[���̓���
void Player::Editor() {
	Input* input = Input::GetInstance();
	if (input->LeftTiltStick(input->Right)) {
		m_Position.x += 0.3f;
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	if (input->LeftTiltStick(input->Left)) {
		m_Position.x -= 0.3f;
		m_Rotation = { 0.0f,0.0f,0.0f };
	}

	if (input->LeftTiltStick(input->Up)) {
		m_Position.y += 0.3f;
		//rot = { 0.0f,90.0f,0.0f };
	}

	if (input->LeftTiltStick(input->Down)) {
		m_Position.y -= 0.3f;
		//rot = { 0.0f,270.0f,0.0f };
	}
	//�v���C���[�h�ł͂Ȃ�
	m_PlayMode = false;

	//Obj_SetParam();
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//�p�[�e�B�N�����o�Ă���
void Player::BirthParticle() {
	//m_PlayerPos = player->GetPosition();
	if (m_FoodParticleCount >= 5.0f && m_Alive) {
		for (int i = 0; i < m_FoodParticleNum; ++i) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = m_Position.z;
			//const float rnd_sca = 0.1f;
			//float sca{};
			//sca = (float)rand() / RAND_MAX*rnd_sca;
			ParticleManager::GetInstance()->Add(30, { m_FoodParticlePos.x + vel.x,(m_FoodParticlePos.y) + vel.y,m_FoodParticlePos.z }, vel, XMFLOAT3(), 1.2f, 0.6f);
		}
		m_FoodParticleCount = 0.0f;
	}
}
//�A�j���[�V�����̋��ʕϐ�
void Player::PlayerAnimetion(int Number, int AnimeSpeed) {
	m_Number = Number;
	m_AnimeLoop = false;
	m_AnimeTimer = 0;
	m_AnimeSpeed = AnimeSpeed;
	m_AnimationStop = true;
	m_fbxObject->PlayAnimation(m_Number);
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
			m_Rotation.z = 0.0f;
			m_Position = m_RespornPos;
		}
	}
}
//���[�h�����Ƃ��̏�����
void Player::LoadPlayer(const XMFLOAT3& StartPos) {
	m_Position = StartPos;
	//m_Object->SetPosition(m_Position);
	m_fbxObject->SetPosition(m_Position);
}
//�v���C���[���G�ɂ��������u�Ԃ̔���
void Player::PlayerHit(const XMFLOAT3& pos) {
	PlayerAnimetion(4, 3);
	m_Effect = true;
	m_HP -= 1;
	m_Interval = 100;
	//m_Effect = true;
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = 1;//�E���ɒe�����
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = 2;
	}
}
//�v���C���[���G�ɂ��������u�Ԃ̔���
void Player::PlayerThornHit(const XMFLOAT3& pos) {

	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = 1;//�E���ɒe�����
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = 2;
	}
}
//�X�L�����Z�b�g
void Player::ResetSkill() {
	s_UseCompass = false;
	s_UseLibra = false;
	s_UseDush = false;
	s_UseHeal = false;
}
//�����V�[���̍X�V
void Player::IntroductionUpdate(int Timer) {
	m_SwordColor = { 1.0f,1.0f,0.0f,0.0f };
	m_HandMat = m_fbxObject->GetWorldMat();
	//�t���[�����œ��������܂�
	if (Timer == 1) {
		m_Position = { 0.0f,2.0f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}
	//�p�[�e�B�N��
	//if (m_SwordParticleCount < 3) {
	//	m_SwordParticleCount++;
	//}
	//else {
	//	m_SwordParticleCount = 0;
	//}
	//��莞�ԗ�������O�ɂ�����
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimeTimer++;
	
	if (m_AnimeTimer == 1) {
		//�A�j���[�V�����̂��߂̂��
		m_AnimeLoop = true;
		m_Number = 1;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_Number);
	}

	//���̍X�V
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);

	
	//FollowObj_SetParam(m_HandMat);
}
//�����V�[���̕`��
void Player::IntroductionDraw(DirectXCommon* dxCommon) {
	//FollowObj_Draw();
	Fbx_Draw(dxCommon);
	//FollowObj_Draw();
}
//�{�X�V�[���̍X�V
void Player::BossAppUpdate(int Timer) {
	m_fbxObject->SetPosition({ 0.0f,8.0f,0.0f });
	m_fbxObject->SetRotation({ 0.0f,0.0f,0.0f });
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}

void Player::BossAppDraw(DirectXCommon* dxCommon) {
	//FollowObj_Draw();
	Fbx_Draw(dxCommon);
	//FollowObj_Draw();
}