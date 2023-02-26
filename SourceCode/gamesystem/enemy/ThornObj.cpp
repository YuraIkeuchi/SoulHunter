#include "ThornObj.h"
#include "ModelManager.h"
#include <Easing.h>
#include "Collision.h"
#include "Audio.h"
#include "VolumManager.h"
bool ThornObj::Initialize() {
	
	m_Scale = { 2.5f,4.8f,2.5f };
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	//�X�e�[�W��
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::ThornObj);
	IKEObject3d* m_Object_ = new IKEObject3d();
	m_Object_ = IKEObject3d::Create();
	m_Object_->SetModel(m_Model);
	m_Object_->SetScale(m_Scale);
	m_Object_->SetLightEffect(false);
	m_Object.reset(m_Object_);
	m_TargetTimer = rand() % 90 + 10;

	ThornParticle* thornparticle_;
	thornparticle_ = new ThornParticle();
	thornparticle_->Initialize();
	thornparticle.reset(thornparticle_);
	return true;
}
//�X�V
void ThornObj::Update() {
	Collide();
	//�����n�߂鎞�Ԃ�ς��邱�ƂŃ^�C�~���O�����炷
	if (m_MoveTImer < m_TargetTimer) {
		m_MoveTImer++;
	}
	//�X�V�͈͂̂Ƃ��̂�
	if (UpdateCollide()) {
		if (m_Dir == Up) {
			m_SmokeParticlePos = { m_ThornSetPos.x,m_ThornSetPos.y + 15.0f,m_ThornSetPos.z };
			m_RockParticlePos = { m_ThornSetPos.x,m_ThornSetPos.y + 15.0f,m_ThornSetPos.z };
			m_Rotation.z = 0.0f;
			m_HitArea = { 5.0f,22.0f,5.0f };
			if (m_MoveTImer >= m_TargetTimer) {
				UpMove();
			}
		}
		else if (m_Dir == Down) {
			m_SmokeParticlePos = { m_ThornSetPos.x,m_ThornSetPos.y - 15.0f,m_ThornSetPos.z };
			m_RockParticlePos = { m_ThornSetPos.x,m_ThornSetPos.y - 15.0f,m_ThornSetPos.z };
			m_Rotation.z = 180.0f;
			m_HitArea = { 5.0f,22.0f,5.0f };
			if (m_MoveTImer >= m_TargetTimer) {
				DownMove();
			}
		}
		else if (m_Dir == Right) {
			m_SmokeParticlePos = { m_ThornSetPos.x + 15.0f,m_ThornSetPos.y,m_ThornSetPos.z };
			m_RockParticlePos = { m_ThornSetPos.x + 15.0f,m_ThornSetPos.y,m_ThornSetPos.z };
			m_Rotation.z = 270.0f;
			m_HitArea = { 22.0f,5.0f,5.0f };
			if (m_MoveTImer >= m_TargetTimer) {
				RightMove();
			}
		}
		else if (m_Dir == Left) {
			m_SmokeParticlePos = { m_ThornSetPos.x - 15.0f,m_ThornSetPos.y,m_ThornSetPos.z };
			m_RockParticlePos = { m_ThornSetPos.x - 15.0f,m_ThornSetPos.y,m_ThornSetPos.z };
			m_Rotation.z = 90.0f;
			m_HitArea = { 22.0f,5.0f,5.0f };
			if (m_MoveTImer >= m_TargetTimer) {
				LeftMove();
			}
		}
		Obj_SetParam();
		//�p�[�e�B�N���֌W
		if (m_SmokeParticleCount >= 2) {
			m_SmokeParticleCount = 0;
		}
		if (m_RockParticleCount >= 4) {
			m_RockParticleCount = 0;
		}
		thornparticle->SetStartColor({ 1.0f,1.0f,1.0f,1.0f });
		thornparticle->TexUpdate(m_SmokeParticlePos, m_SmokeParticleCount, 1, m_Dir);
		thornparticle->ObjUpdate(m_RockParticlePos, m_RockParticleCount, 3, m_Dir);
	}
	else {
		m_SmokeParticleCount = 0;
		m_RockParticleCount = 0;
	}
}
//�`��
 void ThornObj::Draw(DirectXCommon* dxCommon) {
	 if (DrawCollide()) {
		 thornparticle->Draw();
		 Obj_Draw();
	 }
}
 //�|�[�Y
void ThornObj::Pause() {
	m_Object->Update();
}
//�����蔻��
bool ThornObj::Collide() {
	int Interval = player->GetInterVal();
	//�O�ϓ����蔻��
	Sphere sphere;
	sphere.center = { player->GetPosition().x,player->GetPosition().y,player->GetPosition().z };
	sphere.radius = 1;

	Box box;
	box.center = { m_Position.x,m_Position.y,m_Position.z };
	box.scale = { m_HitArea.x,m_HitArea.y,m_HitArea.z };

	if (Collision::CheckSphere2Box(sphere, box) && (Interval == 0)) {
		player->PlayerHit(m_Position);
		return true;
	}
	else {
		return false;
	}

	return true;
}
//�����
void ThornObj::UpMove() {
	switch (m_Pat) {
	case Stop:
		//�����ĂȂ�����
		if (m_AttackTimer <= 100) {
			m_AttackTimer++;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.y + 20.0f;
			m_Afterpos = {
				m_Position.x,
				m_Position.y - 4.0f,
				m_Position.z
			};
			m_Pat = Set;
			m_AttackTimer = 0;
			break;
		}
		//�L�т�O����
	case Set:
		m_SmokeParticleCount++;
		m_RockParticleCount++;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.y + 720.0f;
			m_Frame = 0.0f;
			m_Pat = Attack;
			m_Afterpos = {
				m_Position.x,
				m_Position.y + 20.0f,
				m_Position.z
			};
			break;
		}
		//�L�т�
	case Attack:
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
			break;
		}
		else {
			if (m_CoolT == 1) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/ioe7p-jin8c.wav", VolumManager::GetInstance()->GetSEVolum());
			}
			m_Frame = 1.0f;
			if (m_CoolT < 50) {
				m_CoolT++;
				break;
			}
			else {
				m_AfterRotetion = m_Rotation.y - 20.0f;
				m_Afterpos = {
				m_Position.x,
				m_Position.y - 16.0f,
				m_Position.z
				};
				m_Pat = Return;
				m_Frame = 0.0f;
				m_CoolT = 0;
				break;
			}
		}
	case Return:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_Rotation.y = 0.0f;
			m_Frame = 0;
			m_Pat = Stop;
			break;
		}
	}
	m_Rotation.y = Ease(In, Cubic, m_Frame, m_Rotation.y, m_AfterRotetion);
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_Afterpos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_Afterpos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_Afterpos.z)
	};
}
//������
void ThornObj::DownMove() {
	switch (m_Pat) {
	case Stop:
		//�����ĂȂ�����
		if (m_AttackTimer <= 100) {
			m_AttackTimer++;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.y + 20.0f;
			m_Afterpos = {
				m_Position.x,
				m_Position.y + 4.0f,
				m_Position.z
			};
			m_Pat = Set;
			m_AttackTimer = 0;
			break;
		}
		//�L�т�O����
	case Set:
		m_SmokeParticleCount++;
		m_RockParticleCount++;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.y + 720.0f;
			m_Frame = 0.0f;
			m_Pat = Attack;
			m_Afterpos = {
				m_Position.x,
				m_Position.y - 20.0f,
				m_Position.z
			};
			break;
		}
		//�L�т�
	case Attack:
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
			break;
		}
		else {
			if (m_CoolT == 1) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/ioe7p-jin8c.wav", VolumManager::GetInstance()->GetSEVolum());
			}
			m_Frame = 1.0f;
			if (m_CoolT < 50) {
				m_CoolT++;
				break;
			}
			else {
				m_AfterRotetion = m_Rotation.y - 20.0f;
				m_Afterpos = {
				m_Position.x,
				m_Position.y + 16.0f,
				m_Position.z
				};
				m_Pat = Return;
				m_Frame = 0.0f;
				m_CoolT = 0;
				break;
			}
		}
	case Return:
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_Rotation.y = 0.0f;
			m_Frame = 0;
			m_Pat = Stop;
			break;
		}
	}
	m_Rotation.y = Ease(In, Cubic, m_Frame, m_Rotation.y, m_AfterRotetion);
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_Afterpos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_Afterpos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_Afterpos.z)
	};
}
//�E����
void ThornObj::RightMove() {
	switch (m_Pat) {
	case Stop:
		//�����ĂȂ�����
		if (m_AttackTimer <= 100) {
			m_AttackTimer++;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.x + 20.0f;
			m_Afterpos = {
				m_Position.x - 4.0f,
				m_Position.y,
				m_Position.z
			};
			m_Pat = Set;
			m_AttackTimer = 0;
			break;
		}
		//�L�т�O����
	case Set:
		m_SmokeParticleCount++;
		m_RockParticleCount++;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.x + 720.0f;
			m_Frame = 0.0f;
			m_Pat = Attack;
			m_Afterpos = {
				m_Position.x + 20.0f,
				m_Position.y,
				m_Position.z
			};
			break;
		}
		//�L�т�
	case Attack:
		if (m_Frame < 1.0f) {
			//m_RotaPower = 20.0f;
			m_Frame += 0.1f;
			break;
		}
		else {
			if (m_CoolT == 1) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/ioe7p-jin8c.wav", VolumManager::GetInstance()->GetSEVolum());
			}
			m_Frame = 1.0f;
			if (m_CoolT < 50) {
				m_CoolT++;
				break;
			}
			else {
				m_AfterRotetion = m_Rotation.x - 20.0f;
				m_Afterpos = {
				m_Position.x - 16.0f,
				m_Position.y,
				m_Position.z
				};
				m_Pat = Return;
				m_Frame = 0.0f;
				m_CoolT = 0;
				break;
			}
		}
	case Return:
		m_Rotation.x = 0.0f;
		//m_RotaPower = -2.0f;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_Frame = 0;
			m_Pat = Stop;
			break;
		}
	}
	m_Rotation.x = Ease(In, Cubic, m_Frame, m_Rotation.x, m_AfterRotetion);
	//m_Rotation.x += m_RotaPower;
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_Afterpos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_Afterpos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_Afterpos.z)
	};
}
//������
void ThornObj::LeftMove() {
	switch (m_Pat) {
	case Stop:
		//�����ĂȂ�����
		if (m_AttackTimer <= 100) {
			m_AttackTimer++;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.x + 20.0f;
			m_Afterpos = {
				m_Position.x + 4.0f,
				m_Position.y,
				m_Position.z
			};
			m_Pat = Set;
			m_AttackTimer = 0;
			break;
		}
		//�L�т�O����
	case Set:
		m_SmokeParticleCount++;
		m_RockParticleCount++;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_AfterRotetion = m_Rotation.x + 720.0f;
			m_Frame = 0.0f;
			m_Pat = Attack;
			m_Afterpos = {
				m_Position.x - 20.0f,
				m_Position.y,
				m_Position.z
			};
			break;
		}
		//�L�т�
	case Attack:
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
			break;
		}
		else {
			if (m_CoolT == 1) {
				Audio::GetInstance()->PlayWave("Resources/Sound/SE/ioe7p-jin8c.wav", VolumManager::GetInstance()->GetSEVolum());
			}
			m_Frame = 1.0f;
			if (m_CoolT < 50) {
				m_CoolT++;
				break;
			}
			else {
				m_AfterRotetion = m_Rotation.x - 20.0f;
				m_Afterpos = {
				m_Position.x + 16.0f,
				m_Position.y,
				m_Position.z
				};
				m_Pat = Return;
				m_Frame = 0.0f;
				m_CoolT = 0;
				break;
			}
		}
	case Return:
		m_Rotation.x = 0.0f;
		if (m_Frame < 1.0f) {
			m_Frame += 0.01f;
			break;
		}
		else {
			m_Frame = 0;
			m_Pat = Stop;
			break;
		}
	}
	m_Rotation.x = Ease(In, Cubic, m_Frame, m_Rotation.x, m_AfterRotetion);
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_Afterpos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_Afterpos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_Afterpos.z)
	};
}
//�X�V��͈͓��ɓ��������̂�
bool ThornObj::UpdateCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 50.0f, m_PlayerPos.x, m_PlayerPos.y, 50.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}
//�`���͈͓��ɓ��������̂�
bool ThornObj::DrawCollide() {
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_Position.x, m_Position.y, 50.0f, m_PlayerPos.x, m_PlayerPos.y, 50.0f)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}