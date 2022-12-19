#include "FirstBoss.h"
#include "ImageManager.h"
#include <Easing.h>
FirstBoss::FirstBoss() {
	model = ModelManager::GetInstance()->GetModel(ModelManager::FirstBoss);
	
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

}

void FirstBoss::Initialize() {
	assert(player);
	assert(playereffect);
	m_pos = { 205.0f, -145.0f,80.0f };
	//敵
	IKEObject3d* enemyobj_ = new IKEObject3d();
	enemyobj_ = IKEObject3d::Create();
	enemyobj_->SetModel(model);
	enemyobj_->SetPosition(m_pos);
	m_rot = { 0.0f,180.0f,0.0f };
	enemyobj_->SetRotation(m_rot);
	enemyobj_->SetScale(m_Scale);
	enemyobj.reset(enemyobj_);
	m_HitRadius = 2.0f;
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
		if ((m_Action % 2) == 0) {
			//横移動
			BesideAttack();
			
		}
		else if ((m_Action % 2) == 1) {
			//突き刺してくる攻撃
			StabbingAttack();
		}
	}

	DrawOutArea();
	enemyobj->SetRotation(m_rot);
}
//各ボス特有の描画
void FirstBoss::specialDraw() {
	IKETexture::PreDraw(0);
	if (m_DrawArea) {
		OutAreatexture->Draw();
	}
}
//登場ムービー
void FirstBoss::App() {
	//奥の方から徐々に出るような演出
	if (!m_AppMove) {
		m_MovieTimer++;
		if (m_MovieTimer == 680) {
			m_AppMove = true;
	
			m_Frame = m_FrameMin;
			m_AfterPos.z = 0.0f;
		}
	}
	else {

		if (m_Frame < m_FrameMax) {
			m_Frame += 0.01f;
		}
		else {
			m_MovieTimer = 0;
			m_AppMove = false;
			m_Frame = m_FrameMin;
		}
		m_pos.z = Ease(In, Quint, m_Frame, m_pos.z, m_AfterPos.z);
		m_Scale = { Ease(In, Quint, m_Frame, m_Scale.x, m_AfterScale.x),
			Ease(In, Quint, m_Frame,m_Scale.y, m_AfterScale.y),
			Ease(In, Quint, m_Frame,m_Scale.z, m_AfterScale.z),
		};
	}
	enemyobj->SetPosition(m_pos);
	enemyobj->SetScale(m_Scale);
}
//倒した後の動き
void FirstBoss::End() {
	m_rot.y += 5.0f;
	if (m_Scale.x > 0.0f) {
		m_Scale.x -= 0.02f;
		m_Scale.y -= 0.02f;
		m_Scale.z -= 0.02f;
	}
	else {
		m_Scale = { 0.0f,0.0f,0.0f };
	}

	enemyobj->SetScale(m_Scale);
	enemyobj->SetRotation(m_rot);
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
	if (m_AttackCount > 180) {
		m_Action = (rand() % 2);
		m_Frame = m_FrameMin;
		m_Pat = 1;
		m_Active = true;
	}
	else {
		//攻撃間のインターバル
		if (m_HP >= 20.0f) {
			m_AttackCount++;
		}
		else {
			m_AttackCount += 5;
		}
	}
}
//横移動
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

	m_pos = {
Ease(In,Cubic,m_Frame,m_pos.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_pos.y,m_AfterPos.y),
m_pos.z,
	};
	enemyobj->SetPosition(m_pos);
	m_rot.y = Ease(In, Quint, 0.5f, m_rot.y, m_AfterRot.y);
}
//突き刺してくる攻撃
void FirstBoss::StabbingAttack() {
	if (m_MoveCount < 4) {
		m_AfterRot.y = 180.0f;
		switch (m_Pat) {
		case 1:
			m_AfterPos = {
			m_pos.x,
			-120.0f,
			m_pos.z
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
				m_OutPos = { m_TargetPos.x,m_pos.y,m_pos.z + 5 };
				break;
			}
		case 2:
			m_AfterPos = {
			m_TargetPos.x,
			m_pos.y,
			m_pos.z
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
			m_pos.x,
			-158.0f,
			m_pos.z
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
			m_pos.z
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
	m_pos = {
Ease(In,Cubic,m_Frame,m_pos.x,m_AfterPos.x),
Ease(In,Cubic,m_Frame,m_pos.y,m_AfterPos.y),
	Ease(In,Cubic,m_Frame,m_pos.z,m_AfterPos.z)
	};
	m_rot.y = Ease(In, Quint, 0.5f, m_rot.y, m_AfterRot.y);
	enemyobj->SetPosition(m_pos);
}