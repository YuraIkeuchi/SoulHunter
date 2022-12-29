#include "FirstBoss.h"
#include "ImageManager.h"
#include <Easing.h>
FirstBoss::FirstBoss() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::BossFBX);
	//ボスの名前
	BossName* bossname_;
	bossname_ = new BossName();
	bossname.reset(bossname_);
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
	m_Position = { 205.0f, -152.0f,0.0f };
	m_Rotation = { 0.0f,270.0f,0.0f };
	//m_Position = { 5.0f,10.0f,0.0f };
	m_Scale = { 0.02f,0.02f,0.02f };
	m_HitRadius = 3.0f;

	return true;
}
//行動
void FirstBoss::Spec() {
	//行動を決める
	if (!m_Active) {
		//ボスの名前表示
		if (m_AttackCount == 1) {
			bossname->SetAddStartChange(true);
		}
		//攻撃していない
		NotAttack();
	}
	else {
		//行動開始
		if (m_Action == 0) {
			//横移動
			BesideAttack();
			
		}
		else if (m_Action == 1) {
			//突き刺してくる攻撃
			StabbingAttack();
		}
		else if (m_Action == 2) {
			//炎の攻撃
			FireAttack();
		}
	}
	FireBallArgment();
	DrawOutArea();

	//生きてる時しか更新しない
	if (m_Alive) {
		//エフェクト関係
		for (FireBall* fireball : fireballs) {
			if (fireball != nullptr) {
				if (fireball->Collide(player->GetPosition())) {
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
	//ImGui::Text("m_FireState:%d", m_FireState);
	//ImGui::Text("m_Cool:%d", m_CoolT);
	//ImGui::Text("Frame:%f", m_Frame);
	////ImGui::Text("PosX:%f", m_Position.x);
	////ImGui::Text("PosY:%f", m_Position.y);
	////ImGui::Text("PosZ:%f", m_Position.z);
	////ImGui::Text("RotX:%f", m_Rotation.x);
	////ImGui::Text("RotY:%f", m_Rotation.y);
	////ImGui::Text("RotZ:%f", m_Rotation.z);
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
	//ImGui::Begin("Boss");
	//ImGui::Text("Timer:%d", m_AppTimer);
	//ImGui::Text("PosX:%f", m_Position.x);
	//ImGui::Text("PosY:%f", m_Position.y);
	//ImGui::Text("PosZ:%f", m_Position.z);
	//ImGui::Text("RotX:%f", m_Rotation.x);
	//ImGui::Text("RotY:%f", m_Rotation.y);
	//ImGui::Text("RotZ:%f", m_Rotation.z);
	//ImGui::End();
}
//各ボス特有の描画
void FirstBoss::specialDrawEnd() {
	//ImGui::Begin("Boss");
	//ImGui::Text("Timer:%d", m_AppTimer);
	//ImGui::Text("PosX:%f", m_Position.x);
	//ImGui::Text("PosY:%f", m_Position.y);
	//ImGui::Text("PosZ:%f", m_Position.z);
	//ImGui::Text("RotX:%f", m_Rotation.x);
	//ImGui::Text("RotY:%f", m_Rotation.y);
	//ImGui::Text("RotZ:%f", m_Rotation.z);
	//ImGui::End();
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
	//enemyobj->SetScale(m_Scale);
	//enemyobj->SetRotation(m_rot);
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
	if (m_AttackCount > 250) {
		m_RandFire = rand() % 3;
		m_Frame = m_FrameMin;
		m_Pat = 1;
		m_Active = true;
	}
	else {
		//sin波によって上下に動く
		m_Angle += 1.0f;
		m_Angle2 = m_Angle * (3.14f / 180.0f);
		m_Position.y = (sin(m_Angle2) * 4.0f + 4.0f) + (-152.0f);
		//攻撃間のインターバル
		if (m_HP >= 20.0f) {
			m_AttackCount++;
		}
		else {
			m_AttackCount += 5;
		}

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
	if (m_Frame < m_FrameMax) {
		m_Frame += 0.01f;
	}
	else {
		m_Frame = m_FrameMin;
		m_Pat++;
	}

	if (m_Pat == 1) {
		m_AfterPos.x = 159.0f;
		m_AfterPos.y = -152.0f;
		m_AfterRot = { 45.0f,270.0f,0.0f };
	}
	else if (m_Pat == 2) {
		m_AfterPos.x = 203.0f;
		m_AfterRot = { 0.0f,180.0f,0.0f };
	}
	else if (m_Pat == 3) {
		m_AfterPos.x = 248.0f;
		m_AfterRot = { 45.0f,90.0f,0.0f };
	}
	else if (m_Pat == 4) {
		m_AfterPos.x = 203.0f;
		m_AfterRot = { 0.0f,270.0f,0.0f };
	}
	/*else if (m_Pat == 5) {
		m_AfterRot = { 0.0f,180.0f,0.0f };
	}*/
	else {
		m_Angle = 280.0f;
		m_Active = false;
		m_AttackCount = 0;
		m_Frame = m_FrameMin;
		m_Pat = 0;
	}
//
	m_Position = {
Ease(In,Cubic,m_Frame,m_Position.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_Position.y,m_AfterPos.y),
m_Position.z,
	};
	m_Rotation = {
		Ease(In,Cubic,m_Frame,m_Rotation.x,m_AfterRot.x),
Ease(In,Cubic,m_Frame,m_Rotation.y,m_AfterRot.y),
m_Rotation.z,
	};
}
//突き刺してくる攻撃
void FirstBoss::StabbingAttack() {
	if (m_MoveCount < 4) {
		m_AfterRot = { 0.0f,180.0f,0.0f };
		switch (m_Pat) {
		case 1:	//アニメーションのためのやつ
		/*	m_AnimeLoop = true;
			m_Number = 0;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);*/
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
			-152.0f,
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
			-152.0f,
			m_Position.z
			};
			m_AfterRot = { 0.0f,270.0f,0.0f };
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
m_Rotation.z,
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
			m_AfterPos = { 159.0f,-152.0f,0.0f };
			m_AfterRot = { -20.0f,90.0f,0.0f };
		}
		else {
			m_AfterPos = { 248.0f,-152.0f,0.0f };
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
			m_Frame += 0.01f;
		}
		else {
			m_FireBallArgment = true;
			m_Frame = m_FrameMin;
			m_FireState = ShotFire;
		}
	}
	else if (m_FireState == ShotFire) {
		m_CoolT++;
		if (m_CoolT > 100) {
			m_CoolT = 0;
			m_Frame = m_FrameMin;
			m_FireState = EndFire;
		}
	}
	else {
		m_AfterPos = {
			223.0f,
			-152.0f,
			m_Position.z
		};
		m_AfterRot = { 0.0f,270.0f,0.0f };
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
m_Rotation.z,
	};
}
//エフェクト生成
void FirstBoss::FireBallArgment() {
	if (m_FireBallArgment) {
		FireBall* newFireBall;
		newFireBall = new FireBall();
		newFireBall->Initialize();
		newFireBall->SetAlive(true);
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