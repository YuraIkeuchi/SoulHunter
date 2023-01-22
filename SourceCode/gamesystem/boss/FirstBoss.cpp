#include "FirstBoss.h"
#include "ImageManager.h"
#include "VariableCommon.h"
#include <Easing.h>
FirstBoss::FirstBoss() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BossFBX);
	//パーティクル
	//パーティクル
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
	m_ChangeColor = true;
}
//初期化
bool FirstBoss::Initialize() {
	assert(player);
	m_Position = { 205.0f, -145.0f,0.0f };
	//m_Position = { 5.0f,10.0f,0.0f };
	m_Scale = { 0.01f,0.01f,0.01f };
	m_HitRadius = 2.2f;

	return true;
}
//バトル開始時の初期化
bool FirstBoss::BattleInitialize() {
	assert(player);
	m_Position = { 205.0f, -154.0f,0.0f };
	m_Rotation = { 0.0f,180.0f,0.0f };
	//m_Position = { 5.0f,10.0f,0.0f };
	m_Scale = { 0.02f,0.02f,0.02f };
	m_OBBScale = { 3.0f,0.25f,0.5f };
	m_HitRadius = 2.2f;

	return true;
}
//行動
void FirstBoss::Spec() {
	//行動を決める
	if (!m_Active) {
		//攻撃していない
		NotAttack();
		m_HitRadius = 2.2f;
	}
	else {
		//行動開始
		if (m_Action == 0) {
			//横移動
			BesideAttack();	
			m_HitRadius = 2.2f;
		}
		else if (m_Action == 1) {
			//突き刺してくる攻撃
			StabbingAttack();
			m_HitRadius = 2.2f;
		}
		else if (m_Action == 2) {
			//炎の攻撃
			FireAttack();
			m_HitRadius = 2.2f;
		}
		else if (m_Action == 3) {
			//必殺アタック
			SpecialAttack();
		}
	}
	FireBallArgment();
	DrawOutArea();
	//生きてる時しか更新しない
	if (m_Alive) {
		//エフェクト関係
		for (FireBall* fireball : fireballs) {
			if (fireball != nullptr) {
				if (fireball->Collide(player->GetPosition()) && player->GetInterVal() == 0) {
					player->PlayerHit(m_Position);
				}
				fireball->Update();
			}
		}
		m_fbxObject->SetScale(m_Scale);
		m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
		Fbx_SetParam();
	}
}
//各ボス特有の描画
void FirstBoss::specialDraw(DirectXCommon* dxCommon) {
	//ImGui::Begin("Boss");
	///*ImGui::SliderFloat("PosX", &m_Position.x, 150, 250);
	//ImGui::SliderFloat("PosY", &m_Position.y, -90, -150);
	//ImGui::SliderFloat("PosZ", &m_Position.z, 30, -30);
	//ImGui::SliderFloat("RotX", &m_Rotation.x, 360, -360);
	//ImGui::SliderFloat("RotY", &m_Rotation.y, 360, -360);
	//ImGui::SliderFloat("RotZ", &m_Rotation.z, 360, -360);*/
	//ImGui::Text("HP:%f", m_HP);
	//ImGui::Text("m_Action:%d", m_Action);
	//ImGui::Text("m_DamageTimer:%d", m_DamageTimer);
	//ImGui::Text("m_AttackCount:%d", m_AttackCount);
	//ImGui::End();
	IKETexture::PreDraw(0);
	if (m_DrawArea) {
		OutAreatexture->Draw();
	}
	//エフェクト関係
	for (FireBall* fireball : fireballs) {
		if (fireball != nullptr) {
			fireball->Draw(dxCommon);
		}
	}
}
//各ボス特有の描画
void FirstBoss::specialDrawApp() {

}
//各ボス特有の描画
void FirstBoss::specialDrawEnd() {

}
//登場ムービー
void FirstBoss::App() {
	if (m_AppTimer < 800) {
		m_AppTimer++;
	}

	if (m_AppNumber == NoMove) {
		if (m_AppTimer == 1) {
			//アニメーションのためのやつ
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
			//アニメーションのためのやつ
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

	//生きてる時しか更新しない
	if (m_Alive) {
		m_fbxObject->SetScale(m_Scale);
		m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
		Fbx_SetParam();
	}
}
//倒した後の動き
void FirstBoss::Dead() {
	m_Rotation.y += 5.0f;
	if (m_Scale.x > 0.0f) {
		m_Scale.x -= 0.0001f;
		m_Scale.y -= 0.0001f;
		m_Scale.z -= 0.0001f;
	}
	else {
		m_Scale = { 0.0f,0.0f,0.0f };
	}
	m_fbxObject->SetScale(m_Scale);
	m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
	Fbx_SetParam();
	//enemyobj->SetScale(m_Scale);
	//enemyobj->SetRotation(m_rot);
}
//ボス終了
void FirstBoss::End() {
	m_Scale = { 0.03f,0.03f,0.03f };
	m_Position = { 0.0f,10.0f,20.0f };
	m_Rotation = { 0.0f,180.0f,0.0f };
	m_fbxObject->SetScale(m_Scale);
	m_fbxObject->Update(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
	Fbx_SetParam();
}
//突き刺してくる攻撃のエリア表示
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
//攻撃していない
void FirstBoss::NotAttack() {
	if (m_AttackCount > 500) {
		m_RandFire = rand() % 3;
		m_Frame = m_FrameMin;
		m_Pat = 1;
		//m_Action = (rand() % 4);
		m_Action = 3;
		m_Active = true;
	}
	else {
		//sin波によって上下に動く
		m_Angle += 1.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		m_Position.y = (sin(m_Angle2) * 4.0f + 4.0f) + (-154.0f);
		StateManager();
		if (m_AttackCount == 5) {
			//アニメーションのためのやつ
			m_AnimeLoop = true;
			m_Number = 0;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}
}
//横移動
void FirstBoss::BesideAttack() {
	//アニメーションのためのやつ
	m_AnimeLoop = true;
	m_Number = 1;
	m_AnimeSpeed = 1;
	m_fbxObject->PlayAnimation(m_Number);
	m_ParticlePos = m_Position;
	//攻撃の動き
	if (m_Pat == 1) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-105.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 2) {
		m_TargetCoolT = 1;
		m_AfterPos = { 250.0f,-105.0f,0.0f };
		m_AfterRot = { 0.0f,270.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 3) {
		m_TargetCoolT = 100;
		m_AfterPos = { 250.0f,-154.0f,0.0f };
		m_AfterRot = { 20.0f,270.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 4) {
		m_TargetCoolT = 100;
		m_FoodParticleCount += 3;
		m_AfterPos = { 159.0f,-154.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,720.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 5) {
		m_TargetCoolT = 1;
		m_FoodParticleCount = 0;
		m_AfterPos = { 159.0f,-96.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,720.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 6) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-96.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.05f, m_TargetCoolT);
	}
	else if (m_Pat == 7) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-154.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.005f, m_TargetCoolT);
	}
	else {
		m_Angle = 280.0f;
		m_Active = false;
		m_AttackCount = 0;
		m_Frame = m_FrameMin;
		m_Pat = 0;
	}
}
//突き刺してくる攻撃
void FirstBoss::StabbingAttack() {
	m_ParticlePos = m_Position;
	if (m_MoveCount < 1) {
		m_AfterRot = { 0.0f,180.0f,0.0f };
		switch (m_Pat) {
		//上に飛ぶ
		case 1:	//アニメーションのためのやつ
			m_AfterPos = {
			m_Position.x,
			-110.0f,
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
		//場所移動
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
		//落下
		case 3:
			m_AfterPos = {
			m_Position.x,
			-154.0f,
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
					if (m_CoolT <= 10) {
						m_FoodParticleCount += 2;
					}
				}
				else {
					m_CoolT = 0;
					m_Frame = m_FrameMin;
					m_Pat = 1;
					m_MoveCount++;
					break;
				}
			}
		}
	}
	else {
		switch (m_Pat) {
			
		case 1:
			m_AfterPos = {
			205.0f,
			-154.0f,
			m_Position.z
			};
			m_AfterRot = { 0.0f,270.0f,0.0f };
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.01f;
				break;
			}
			else {
				m_Pat++;
				m_Frame = m_FrameMin;
				break;
			}
		case 2:
			m_AfterRot = { 0.0f,180.0f,0.0f };
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.01f;
				break;
			}
			else {
				m_Angle = 280.0f;
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
	m_Rotation = {
		Ease(In,Cubic,m_Frame,m_Rotation.x,m_AfterRot.x),
Ease(In,Cubic,m_Frame,m_Rotation.y,m_AfterRot.y),
Ease(In,Cubic,m_Frame,m_Rotation.z,m_AfterRot.z),
	};
}
//炎の攻撃
void FirstBoss::FireAttack() {
	if (m_FireState == Set0) {
		m_AfterRot = { 0.0f,180.0f,0.0f };
		m_AfterPos = {
		m_Position.x,
		-130.0f,
		m_Position.z
		};
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.01f;
		}
		else {
			m_Frame = m_FrameMax;
			m_CoolT++;
			if (m_CoolT > 90) {
				m_CoolT = 0;
				m_Frame = m_FrameMin;
				m_RandFire = rand() % 2;
				m_FireState = Set1;
			}
		}
	}
	else if (m_FireState == Set1) {
		if (m_RandFire == 0) {
			m_AfterPos = { 159.0f,-140.0f,0.0f };
			m_AfterRot = { -20.0f,90.0f,0.0f };
		}
		else {
			m_AfterPos = { 248.0f,-140.0f,0.0f };
			m_AfterRot = { -20.0f,270.0f,0.0f };
		}
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.01f;
		}
		else {
			m_Frame = m_FrameMin;
			m_FireState = Set2;
		}
	}
	else if (m_FireState == Set2) {
		if (m_RandFire == 0) {
			m_AfterRot = { 20.0f,90.0f,0.0f };
		}
		else {
			m_AfterRot = { 20.0f,270.0f,0.0f };
		}
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.05f;
		}
		else {
			m_Frame = m_FrameMin;
			m_FireState = ShotFire;
		}
	}
	else if (m_FireState == ShotFire) {
		m_CoolT++;
		if (m_CoolT % 15 == 0) {
			m_AddPowerY += 0.2f;
			m_FireBallArgment = true;
		}
		if (m_CoolT > 100) {
			m_AddPowerY = -0.5f;
			m_CoolT = 0;
			m_Frame = m_FrameMin;
			m_FireState = EndFire;
		}
	}
	else {
		m_AfterPos = { 205.0f,-154.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		if (m_Frame < m_FrameMax) {
			m_Frame += 0.01f;
		}
		else {
			m_Angle = 280.0f;
			m_Active = false;
			m_AttackCount = 0;
			m_Frame = m_FrameMin;
			m_FireState = Set0;
		}
	}
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_AfterPos.y),
	Ease(In,Cubic,m_Frame,m_Position.z,m_AfterPos.z)
	};
	m_Rotation = {
		Ease(In,Cubic,m_Frame,m_Rotation.x,m_AfterRot.x),
Ease(In,Cubic,m_Frame,m_Rotation.y,m_AfterRot.y),
Ease(In,Cubic,m_Frame,m_Rotation.z,m_AfterRot.z),
	};
}
//必殺アタック
void FirstBoss::SpecialAttack() {
	//アニメーションのためのやつ
	m_AnimeLoop = true;
	m_Number = 1;
	m_AnimeSpeed = 1;
	m_fbxObject->PlayAnimation(m_Number);
	//攻撃の動き
	if (m_Pat == 1) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-105.0f,30.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 2) {
		m_TargetCoolT = 50;
		m_AfterPos = { 205.0f,-145.0f,30.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		if (m_CoolT == 49) {
			m_TargetPos = player->GetPosition();
		}
		if (m_TargetPos.y < -154.0f) {
			m_TargetPos.y = -154.0f;
		}
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 3) {
		m_TargetCoolT = 20;
		m_AfterPos = m_TargetPos;
		m_AfterRot = { 0.0f,180.0f,720.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.02f, m_TargetCoolT);
	}
	else if (m_Pat == 4) {
		m_TargetCoolT = 1;
		m_AfterPos = { m_Position.x,-105.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,720.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.01f, m_TargetCoolT);
	}
	else if (m_Pat == 5) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-105.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.05f, m_TargetCoolT);
	}
	else if (m_Pat == 6) {
		m_TargetCoolT = 1;
		m_AfterPos = { 205.0f,-154.0f,0.0f };
		m_AfterRot = { 0.0f,180.0f,0.0f };
		FrameMove(m_AfterPos, m_AfterRot, 0.005f, m_TargetCoolT);
	}
	else {
		m_Angle = 280.0f;
		m_Active = false;
		m_AttackCount = 0;
		m_Frame = m_FrameMin;
		m_Pat = 0;
	}
}
//エフェクト生成
void FirstBoss::FireBallArgment() {
	if (m_FireBallArgment) {
		FireBall* newFireBall;
		newFireBall = new FireBall();
		newFireBall->Initialize();
		newFireBall->SetAlive(true);
		newFireBall->SetAddPowerY(m_AddPowerY);
		newFireBall->SetPosition({m_Position.x,m_Position.y + 1.5f,m_Position.z});
		if (m_RandFire == 0) {
			newFireBall->SetAddSpeed(0.5f);
		}
		else {
			newFireBall->SetAddSpeed(-0.5f);
		}
		fireballs.push_back(newFireBall);
		m_FireBallArgment = false;
	}
}
//ボス登場シーンのイージング関数(座標)
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
//ボス登場シーンのイージング関数(回転)
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
//バトルのイージング関数
void FirstBoss::FrameMove(XMFLOAT3 AfterPos, XMFLOAT3 AfterRot, float addframe,int TargetTimer) {

	if (m_Frame < m_FrameMax) {
		m_Frame += addframe;
	}
	else {
		m_Frame = m_FrameMax;
		m_CoolT++;
		if (m_CoolT >= TargetTimer) {
			m_Frame = m_FrameMin;
			m_Pat++;
			m_CoolT = 0;
		}
	}
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,AfterPos.y),
Ease(In,Cubic,m_Frame,m_Position.z,AfterPos.z),
	};
	m_Rotation = {
		Ease(In,Cubic,m_Frame,m_Rotation.x,AfterRot.x),
Ease(In,Cubic,m_Frame,m_Rotation.y,AfterRot.y),
Ease(In,Cubic,m_Frame,m_Rotation.z,AfterRot.z),
	};
}
//HPに応じたステータス
void FirstBoss::StateManager() {
	if (m_HP >= 30) {
		m_AttackCount += 2;
	}
	else if (m_HP >= 29 && m_HP >= 20) {
		m_AttackCount += 3;
	}
	else if (m_HP >= 19 && m_HP >= 10) {
		m_AttackCount += 4;
	}
	else {
		m_AttackCount += 5;
	}
}

void FirstBoss::Pause() {
	Fbx_SetParam();
	m_fbxObject->StopAnimation();
	m_fbxObject->Update(true, 1, m_AnimationStop);
}