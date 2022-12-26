#include "FirstBoss.h"
#include "ImageManager.h"
#include <Easing.h>
FirstBoss::FirstBoss() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BossFBX);
	//�{�X�̖��O
	BossName* bossname_;
	bossname_ = new BossName();
	bossname.reset(bossname_);
	//�p�[�e�B�N��
	ParticleTex* particletex_;
	particletex_ = new ParticleTex();
	particletex_->Initialize();
	particletex.reset(particletex_);

	IKETexture* OutAreatexture_;
	OutAreatexture_ = IKETexture::Create(ImageManager::OutArea, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	OutAreatexture_->TextureCreate();
	//OutAreatexture_->SetRotation({ 90,0,0 });
	OutAreatexture_->SetScale(m_Scale);
	OutAreatexture.reset(OutAreatexture_);

	//
	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	m_Scale = { 0.01f,0.01f,0.01f };
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);
}

bool FirstBoss::Initialize() {
	assert(player);
	assert(playereffect);
	m_Position = { 205.0f, -145.0f,0.0f };
	//m_Position = { 5.0f,10.0f,0.0f };
	m_Scale = { 0.01f,0.01f,0.01f };
	m_HitRadius = 2.0f;

	return true;
}

bool FirstBoss::BattleInitialize() {
	assert(player);
	assert(playereffect);
	m_Position = { 205.0f, -145.0f,0.0f };
	//m_Position = { 5.0f,10.0f,0.0f };
	m_Scale = { 0.03f,0.03f,0.03f };
	m_HitRadius = 5.0f;

	return true;
}
//�s��
void FirstBoss::Spec() {
	//�s�������߂�
	if (!m_Active) {
		//�{�X�̖��O�\��
		if (m_AttackCount == 1) {
			bossname->SetAddStartChange(true);
		}
		//�U�����Ă��Ȃ�
		NotAttack();
	}
	else {
		//�s���J�n
		if ((m_Action % 2) == 0) {
			//���ړ�
			BesideAttack();
			
		}
		else if ((m_Action % 2) == 1) {
			//�˂��h���Ă���U��
			StabbingAttack();
		}
	}

	DrawOutArea();

	//�����Ă鎞�����X�V���Ȃ�
	if (m_Alive) {
		m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
		Fbx_SetParam();
	}
}
//�e�{�X���L�̕`��
void FirstBoss::specialDraw() {
	ImGui::Begin("Boss");
	ImGui::Text("m_AttackCount:%d", m_AttackCount);
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::Text("PosY:%f", m_Position.y);
	ImGui::Text("PosZ:%f", m_Position.z);
	ImGui::Text("RotX:%f", m_Rotation.x);
	ImGui::Text("RotY:%f", m_Rotation.y);
	ImGui::Text("RotZ:%f", m_Rotation.z);
	ImGui::End();
	IKETexture::PreDraw(0);
	if (m_DrawArea) {
		OutAreatexture->Draw();
	}
}
//�e�{�X���L�̕`��
void FirstBoss::specialDrawApp() {
	ImGui::Begin("Boss");
	ImGui::Text("Timer:%d", m_AppTimer);
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::Text("PosY:%f", m_Position.y);
	ImGui::Text("PosZ:%f", m_Position.z);
	ImGui::Text("RotX:%f", m_Rotation.x);
	ImGui::Text("RotY:%f", m_Rotation.y);
	ImGui::Text("RotZ:%f", m_Rotation.z);
	ImGui::End();
}
//�o�ꃀ�[�r�[
void FirstBoss::App() {
	if (m_AppTimer < 800) {
		m_AppTimer++;
	}

	if (m_AppNumber == NoMove) {
		if (m_AppTimer == 1) {
			//�A�j���[�V�����̂��߂̂��
			m_AnimeLoop = true;
			m_Number = 1;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);
			m_Position = { 60.0f,30.0f,10.0f };
			m_Rotation = { 45.0f,270.0f,0.0f };
		}

		if (m_AppTimer ==350) {
			m_AfterPos = { -60.0f,25.0f,7.0f };
			m_Frame = 0.0f;
			m_RotFrame = 0.0f;
			m_AppNumber = FirstMove;
		}
	}
	else if (m_AppNumber == FirstMove) {
		AppBossMove(m_AfterPos, 0.003f);
		if (m_AppTimer == 500) {
			//�A�j���[�V�����̂��߂̂��
			m_AnimeLoop = true;
			m_Number = 0;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);
			m_AfterPos = { 0.0f,25.0f,7.0f };
			m_AfterRot = { 45.0f,180.0f,0.0f };
			m_Frame = 0.0f;
			m_RotFrame = 0.0f;
			m_AppNumber = SecondMove;
		}
	}
	else if (m_AppNumber == SecondMove) {
		AppBossMove(m_AfterPos,0.003f);
		AppBossRot(m_AfterRot, 0.003f);
		if (m_AppTimer == 720) {
			m_AfterRot = { -25.0f,180.0f,0.0f };
			m_Frame = 0.0f;
			m_RotFrame = 0.0f;
			m_AppNumber = ThirdMove;
		}
	}
	else if (m_AppNumber == ThirdMove) {
		AppBossRot(m_AfterRot, 0.05f);
		if (m_AppTimer == 750) {
			m_AfterRot = { 45.0f,180.0f,0.0f };
			m_Frame = 0.0f;
			m_RotFrame = 0.0f;
			m_AppNumber = ThirdMove;
		}
	}
	else {
		AppBossRot(m_AfterRot, 0.1f);
	}

	//�����Ă鎞�����X�V���Ȃ�
	if (m_Alive) {
		m_fbxObject->SetScale(m_Scale);
		m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
		Fbx_SetParam();
	}
	////���̕����珙�X�ɏo��悤�ȉ��o
	//if (!m_AppMove) {
	//	m_MovieTimer++;
	//	if (m_MovieTimer == 680) {
	//		m_AppMove = true;
	//
	//		m_Frame = m_FrameMin;
	//		m_AfterPos.z = 0.0f;
	//	}
	//}
	//else {

	//	if (m_Frame < m_FrameMax) {
	//		m_Frame += 0.01f;
	//	}
	//	else {
	//		m_MovieTimer = 0;
	//		m_AppMove = false;
	//		m_Frame = m_FrameMin;
	//	}
	///*	m_pos.z = Ease(In, Quint, m_Frame, m_pos.z, m_AfterPos.z);
	//	m_Scale = { Ease(In, Quint, m_Frame, m_Scale.x, m_AfterScale.x),
	//		Ease(In, Quint, m_Frame,m_Scale.y, m_AfterScale.y),
	//		Ease(In, Quint, m_Frame,m_Scale.z, m_AfterScale.z),
	//	};*/
	//}
	////enemyobj->SetPosition(m_pos);
	////enemyobj->SetScale(m_Scale);
}
//�|������̓���
void FirstBoss::End() {
	m_Rotation.y += 5.0f;
	if (m_Scale.x > 0.0f) {
		m_Scale.x -= 0.02f;
		m_Scale.y -= 0.02f;
		m_Scale.z -= 0.02f;
	}
	else {
		m_Scale = { 0.0f,0.0f,0.0f };
	}

	//enemyobj->SetScale(m_Scale);
	//enemyobj->SetRotation(m_rot);
}
//�˂��h���Ă���U���̃G���A�\��
void FirstBoss::DrawOutArea() {
	if (m_DrawArea) {
		if (m_OutColor.w < 1.0f) {
			m_OutColor.w += 0.1f;
		}
		else {
			m_OutColor.w = 1.0f;
		}
	}
	else {
		if (m_OutColor.w > 0.0f) {
			m_OutColor.w -= 0.1f;
		}
		else {
			m_DrawArea = false;
			m_OutColor.w = 0.0f;
		}
	}

	OutAreatexture->Update();
	OutAreatexture->SetPosition(m_OutPos);
	OutAreatexture->SetScale(m_OutScale);
	OutAreatexture->SetColor(m_OutColor);
}
//�U�����Ă��Ȃ�
void FirstBoss::NotAttack() {
	if (m_AttackCount > 180) {
		m_Action = (rand() % 2);
		m_Frame = m_FrameMin;
		m_Pat = 1;
		m_Active = true;
	}
	else {
		//�U���Ԃ̃C���^�[�o��
		if (m_HP >= 20.0f) {
			m_AttackCount++;
		}
		else {
			m_AttackCount += 5;
		}
	}
}
//���ړ�
void FirstBoss::BesideAttack() {
	if (m_Frame < m_FrameMax) {
		m_Frame += 0.008f;
	}
	else {
		m_Frame = m_FrameMin;
		m_Pat++;
	}

	if (m_Pat == 1) {
		m_AfterPos.x = 155.0f;
		m_AfterPos.y = -158.0f;
		m_AfterRot.y = 270.0f;
	}
	else if (m_Pat == 2) {
		m_AfterPos.x = 223.0f;
		m_AfterRot.y = 90.0f;
	}
	else if (m_Pat == 3) {
		m_AfterPos.x = 254.0f;
		m_AfterRot.y = 90.0f;
	}
	else if (m_Pat == 4) {
		m_AfterPos.x = 223.0f;
		m_AfterRot.y = 270.0f;
	}
	else if (m_Pat == 5) {
		//AfterPos.x = 55.0f;
		m_AfterRot.y = 180.0f;
	}
	else {
		m_Active = false;
		m_AttackCount = 0;
		m_Frame = m_FrameMin;
		m_Pat = 0;
	}
//
//	m_pos = {
//Ease(In,Cubic,m_Frame,m_pos.x,m_AfterPos.x),
//Ease(In,Cubic,m_Frame,m_pos.y,m_AfterPos.y),
//m_pos.z,
//	};
//	enemyobj->SetPosition(m_pos);
//	m_rot.y = Ease(In, Quint, 0.5f, m_rot.y, m_AfterRot.y);
}
//�˂��h���Ă���U��
void FirstBoss::StabbingAttack() {
	if (m_MoveCount < 4) {
		m_AfterRot.y = 180.0f;
		switch (m_Pat) {
		case 1:
			m_AfterPos = {
			m_Position.x,
			-120.0f,
			m_Position.z
			};
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.01f;
				break;
			}
			else {
				m_DrawArea = true;
				m_Frame = m_FrameMin;
				m_TargetPos.x = player->GetPosition().x;
				m_Pat++;
				m_OutPos = { m_TargetPos.x,m_Position.y,m_Position.z + 5 };
				break;
			}
		case 2:
			m_AfterPos = {
			m_TargetPos.x,
			m_Position.y,
			m_Position.z
			};
			if (m_Aiming < 30) {
				m_Frame = 0.5f;
				m_Aiming++;
				break;
			}
			else {
				m_Frame = m_FrameMin;
				m_Aiming = 0;
				m_Pat++;
				break;
			}
		case 3:
			m_AfterPos = {
			m_Position.x,
			-158.0f,
			m_Position.z
			};
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.1f;
			}
			else {
				m_DrawArea = false;
				m_Frame = m_FrameMax;
				if (m_CoolT < 90) {
					m_CoolT++;
				}
				else {
					m_CoolT = 0;
					m_Frame = m_FrameMin;
					m_Pat = 1;
					m_MoveCount++;
					break;
				}
			}
			//default:
			//	MoveCount = 0;
			//	//pat = 1;
			//	break;
			//}
		}
	}
	else {
		switch (m_Pat) {
		case 1:
			m_AfterPos = {
			223.0f,
			-158.0f,
			m_Position.z
			};
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.01f;
				break;
			}
			else {
				m_Active = false;
				m_AttackCount = 0;
				m_Frame = m_FrameMin;
				m_Pat = 0;
				m_MoveCount = 0;
				break;
			}
		default:
			break;
		}
	}
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_AfterPos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_AfterPos.z)
	};
	m_Rotation.y = Ease(In, Quint, 0.5f, m_Rotation.y, m_AfterRot.y);
	//enemyobj->SetPosition(m_pos);
}
//�{�X�o��V�[���̃C�[�W���O�֐�(���W)
void FirstBoss::AppBossMove(XMFLOAT3 AfterPos, float AddFrame) {
	if (m_Frame < 1.0f)
	{
		m_Frame += AddFrame;
	}
	else {
		m_AfterPos = AfterPos;
		//m_AfterTarget = AfterTarget;
		m_Frame = 1.0f;
	}

	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,AfterPos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,AfterPos.z)
	};
}
//�{�X�o��V�[���̃C�[�W���O�֐�(��])
void FirstBoss::AppBossRot(XMFLOAT3 AfterRot, float AddFrame) {
	if (m_RotFrame  < 1.0f)
	{
		m_RotFrame  += AddFrame;
	}
	else {
		m_AfterRot = AfterRot;
		//m_AfterTarget = AfterTarget;
		m_RotFrame = 1.0f;
	}

	m_Rotation = {
Ease(In,Cubic,m_RotFrame,m_Rotation.x,AfterRot.x),
Ease(In,Cubic,m_RotFrame,m_Rotation.y,AfterRot.y),
	Ease(In,Cubic,m_RotFrame,m_Rotation.z,AfterRot.z)
	};
}