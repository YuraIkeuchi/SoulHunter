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
//読み込み
Player::Player() {
	m_FollowModel = ModelManager::GetInstance()->GetModel(ModelManager::Sword);
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}
//初期化
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

	PlayerWing* playerwing_ = new PlayerWing();
	playerwing_->Initialize();
	playerwing.reset(playerwing_);

	return true;
}
//変数の初期化
void Player::StateInitialize() {
	m_Scale = { 3.0f, 3.0f, 3.0f };
	m_Position = { 20.0f,-100.0f,0.0f };
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_HP = 5;
	//プレイヤー関係
	m_OldPlayerPos = { 0, 0, 0 };
	m_Radius.x = 1.0f * m_Scale.x;
	m_Radius.y = 0.7f * m_Scale.y;
	m_Jump = false;
	m_AddPower = 0;
	m_Gravity = 0.02f;
}
//更新
void Player::Update()
{
	//手のボーン取得
	m_HandMat = m_fbxObject->GetWorldMat();
	Input* input = Input::GetInstance();
	//m_Object->Update();
	m_OldPlayerPos = m_Position;
	//ムービー中は一部挙動は出来ない
	if (!m_Movie) {
		if (m_GoalDir == No) {
			//移動
			PlayerMove();
			//ジャンプ
			PlayerJump();
			//ダッシュ
			PlayerDush();
			//攻撃(剣)
			if (m_AttackType == Sword && !m_CollideObj) {
				PlayerAttack();
			}

			//弾を撃つ
			else if (m_AttackType == Shot) {
				PlayerShot();
			}
			//必殺技
			else if (m_AttackType == Special) {
				PlayerSpecial();
			}
			//HP回復
			PlayerHeal();
			//ダメージ
			PlayerDamage();
			//復活処理
			ResPornPlayer();
			//エフェクト発生
			JumpArgment();
			AttackArgment();
		}
		else {
			//ゴール後の動き
			GoalMove();
		}
	}

	//自動落下
	PlayerFall();
	//パーティクル生成
	BirthParticle();
	//剣の更新
	SwordUpdate();
	//パーティクルを出す
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };
	//パーティクル
	if (m_SwordParticleCount < 1) {
		m_SwordParticleCount++;
	}
	else {
		m_SwordParticleCount = 0;
	}
	//プレイモード
	m_PlayMode = true;
	//ゴールしたときの処理(またゴールしないように)
	if (m_ChangeInterVal) {
		m_IntervalTimer++;
		if (m_IntervalTimer == 120) {
			m_IntervalTimer = 0;
			m_ChangeInterVal = false;
		}
	}

	//プレイヤーが持てる魂の最大量
	if (m_SoulCount >= 72.0f) {
		m_SoulCount = 72.0f;
	}

	// 行列の更新など
	//Obj_SetParam();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
	m_fbxObject->SetDisolve(Disolve);

	//パーティクルのカウント数の更新
	if (m_ParticleCount > 3) {
		m_ParticleCount = 0;
	}

	if (m_HealCount > 3) {
		m_HealCount = 0;
	}
	m_WingPosition = m_Position;
	//パーティクル関係
	particletex->Update(m_ParticlePos, m_ParticleCount, 3, m_ParticleNumber);
	particleheal->SetStartColor({ 0.5f,1.0f,0.1f,1.0f });
	particleheal->Update({ m_Position.x,m_Position.y - 1.0f,m_Position.z }, m_HealCount, 3);
	swordparticle->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	swordparticle->Update(m_SwordParticlePos, m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	//羽
	if (m_PlayerDir == Left) {
		playerwing->SetPosition({ m_Position.x,m_Position.y,m_Position.z });
		playerwing->SetDir(0);
	}
	else {
		playerwing->SetPosition({ m_Position.x,m_WingPosition.y,m_Position.z });
		playerwing->SetDir(1);
	}
	
	playerwing->Update();
	//エフェクト関係
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
//剣の更新
void Player::SwordUpdate() {
	//行列を求める
	m_VectorSwordPos.m128_f32[0] = m_HandMat.r[3].m128_f32[0];
	m_VectorSwordPos.m128_f32[1] = m_HandMat.r[3].m128_f32[1];
	m_VectorSwordPos.m128_f32[2] = m_HandMat.r[3].m128_f32[2];
	//変換
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
	//m_FollowObject->SetColor(m_SwordColor);
	m_FollowObject->FollowUpdate(m_HandMat);
}
//プレイヤーの移動
void Player::PlayerMove() {
	Input* input = Input::GetInstance();
	//地面にいる間は攻撃モーションで動き止まる
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			//動きやジャンプ
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
			//動きやジャンプ
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

	//歩きアニメーション
	WalkAnimation();

}
//歩きアニメーション
void Player::WalkAnimation() {
	Input* input = Input::GetInstance();
	//歩きモーション
	if (input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left) && (m_HealType == NoHeal) && (m_AddPower == 0.0f)) {
		if ((m_AnimeTimer < 3) && (m_JumpCount == 0) && (!m_AnimationStop) && (!m_Special)) {
			m_AnimeTimer++;
		}
		if (m_AnimeTimer == 1) {
			//アニメーションのためのやつ
			m_AnimeLoop = true;
			m_Number = 1;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}
	//止まっている
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
//移動の共通処理
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
//プレイヤーのジャンプ
void Player::PlayerJump() {
	Input* input = Input::GetInstance();
	//プレイヤージャンプ処理
	if (input->TriggerButton(input->Button_B) && (m_JumpCount < 4) && (m_AddPower <= 0.3f) && (!m_Special)
		&& (m_HealType == NoHeal) && (m_Alive)) {
		m_JumpCount++;
		m_Jump = true;
		m_ParticleCount = 0;
		m_WingDeleteCount = 0;
		m_AddPower = 0.8f;
		PlayerAnimetion(2, 2);
		m_JumpArgment = true;
		//ジャンプ回数でプレイヤーの羽が変化する
		playerwing->SetAnimation(true);
		playerwing->SetEaseStart(true);
		playerwing->SetFrame(0.0f);
		playerwing->SetAfterScale({ 0.005f,0.005f,0.005f });
	}
	//エフェクトの発生
}
//プレイヤーの落下
void Player::PlayerFall() {

	m_WingPosition.y = m_Position.y;
	if (m_Jump) {
		//ジャンプ処理
	//ダッシュ中のときは重力がない
		if (!m_Dush && !m_Special) {
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
			m_WingPosition.y += m_AddPower;
		}

		//壁との当たり判定
		if (block->PlayerMapCollideCommon(m_Position, m_Radius, m_OldPlayerPos, m_Jump,
			m_AddPower) && m_Alive)
		{
			//初期化
			m_Gravity = 0.02f;
			m_Jump = false;
			m_AddPower = 0.0f;
		}

		if (m_JumpCount != 0) {
			m_WingDeleteCount++;
		}

		if (m_WingDeleteCount == 15) {
			playerwing->SetEaseStart(true);
			playerwing->SetFrame(0.0f);
			playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });
			m_WingDeleteCount = 0;
		}
		//if(m_JumpCount)
	}
	else {
		m_Jump = true;
	}

	//落下速度の限界
	if (m_AddPower < -1.0f) {
		m_AddPower = -1.0f;
	}
	
	//ジャンプ回数のリセット
	if (m_AddPower == 0.0f && block->GetHitDown()) {
		m_JumpCount = 0;
		playerwing->SetEaseStart(true);
		playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });
	}
}
//プレイヤーの攻撃
void Player::PlayerAttack() {
	Input* input = Input::GetInstance();
	//攻撃
	//攻撃の向き
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
			playerwing->SetEaseStart(true);
			playerwing->SetFrame(0.0f);
			playerwing->SetAfterScale({ 0.000f,0.000f,0.000f });
		}
		else {
			m_AnimeLoop = true;
			m_AnimeSpeed = 2;
			m_Number = 3;
			m_fbxObject->PlayAnimation(m_Number);
		}
	}

	//攻撃のインターバル
	if (m_Attack) {
		//攻撃エフェクトの出現
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
//プレイヤーのダッシュ
void Player::PlayerDush() {
	Input* input = Input::GetInstance();
	//ダッシュ処理
	if ((!m_Dush) && (s_UseDush) && (!m_Special) && (m_SoulCount >= 2.0f) && (m_AddPower != 0.0f) && (m_Alive)) {
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
//弾を打つ
void Player::PlayerShot() {
	Input* input = Input::GetInstance();
	//攻撃
	//攻撃の向き
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
//必殺技
void Player::PlayerSpecial() {
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Button_A) && (m_AddPower == 0.0f) && (!m_Special) && (m_SoulCount >= 25.0f)) {
		m_SoulCount -= 25.0f;
		m_Special = true;
		m_Frame = 0.0f;
		m_AfterPosY = m_Position.y + 8.0f;
		m_SpecialCount = 0;
	}

	//必殺技
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
//プレイヤーのHP回復
void Player::PlayerHeal() {
	Input* input = Input::GetInstance();
	//押している間貯める
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
//ダメージを食らう
void Player::PlayerDamage() {

	//ダメージ時の跳ね返り
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

	//復活処理
	if (!m_Alive) {
		m_RespornTimer++;
		m_Rotation.z--;
	}

	//死んだときの判定
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

	//棘にあたったときの動き
	if (!m_Alive && m_RespornTimer == 1) {
		m_Effect = true;
		m_Jump = true;
	}

	//ダメージ受けたあとの無敵時間
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
//エフェクト生成
void Player::JumpArgment() {
	if (m_JumpArgment) {
		JumpEffect* newJumpEffect;
		newJumpEffect = new JumpEffect();
		newJumpEffect->Initialize();
		jumpeffects.push_back(newJumpEffect);
		m_JumpArgment = false;
	}
}
//上に同じ
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
//ゴール後の動き
void Player::GoalMove() {
	if (m_GoalDir == RightGoal) {

		m_Position.x += 0.3f;
	}
	else if (m_GoalDir == LeftGoal) {
		m_Position.x -= 0.3f;
	}
}
//描画
void Player::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("player");
	ImGui::SetWindowPos(ImVec2(1000, 450));
	ImGui::SetWindowSize(ImVec2(280, 300));
	ImGui::Text("m_FoodParticleCount:%f", m_FoodParticleCount);
	ImGui::Text("m_FoodParticlePos.x:%f", m_FoodParticlePos.x);
	ImGui::Text("m_FoodParticlePos.y:%f", m_FoodParticlePos.y);
	ImGui::Text("m_FoodParticlePos.z:%f", m_FoodParticlePos.z);
	ImGui::End();

	//エフェクト関係
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
		FollowObj_Draw();
		//Obj_Draw();
		if (m_SwordColor.w >= 0.1f) {
			
		}
		Fbx_Draw(dxCommon);
		playerwing->Draw(dxCommon);
	}
	particleheal->Draw();
	particletex->Draw();
	swordparticle->Draw();
	//particleobj->ImGuiDraw();
	//object1->Draw(dxCommon->GetCmdList());
}
//解放
void Player::Finalize()
{
}
//各マップごとの位置初期化
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
			m_Position = { 175.0f,-20.0f,0.0f };
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
//ポーズ開いたときはキャラが動かない
void Player::Pause() {
	SwordUpdate();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//エディター時の動き
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
	//プレイモードではない
	m_PlayMode = false;

	//Obj_SetParam();
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//パーティクルが出てくる
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
//アニメーションの共通変数
void Player::PlayerAnimetion(int Number, int AnimeSpeed) {
	m_Number = Number;
	m_AnimeLoop = false;
	m_AnimeTimer = 0;
	m_AnimeSpeed = AnimeSpeed;
	m_AnimationStop = true;
	m_fbxObject->PlayAnimation(m_Number);
}
//生き返った時の位置
void Player::ResPornPlayer() {
	//直前までの位置を保存する
	if (m_AddPower == 0.0f && !block->GetThornHit() && block->GetHitDown()) {
		m_SaveTimer++;
	}
	//ここで保存
	if (m_SaveTimer == 20) {
		m_RespornPos = m_Position;
		m_SaveTimer = 0;
	}
	//復活
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
//ロードしたときの初期化
void Player::LoadPlayer(const XMFLOAT3& StartPos) {
	m_Position = StartPos;
	//m_Object->SetPosition(m_Position);
	m_fbxObject->SetPosition(m_Position);
}
//プレイヤーが敵にあたった瞬間の判定
void Player::PlayerHit(const XMFLOAT3& pos) {
	m_Effect = true;
	m_HP -= 1;
	m_Interval = 100;
	//m_Effect = true;
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = 1;//右側に弾かれる
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = 2;
	}
}
//プレイヤーが敵にあたった瞬間の判定
void Player::PlayerThornHit(const XMFLOAT3& pos) {

	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = 1;//右側に弾かれる
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = 2;
	}
}
//スキルリセット
void Player::ResetSkill() {
	s_UseCompass = false;
	s_UseLibra = false;
	s_UseDush = false;
	s_UseHeal = false;
}
//導入シーンの更新
void Player::IntroductionUpdate(int Timer) {
	m_SwordColor = { 1.0f,1.0f,0.0f,0.0f };
	m_HandMat = m_fbxObject->GetWorldMat();
	//フレーム数で動きが決まる
	if (Timer == 1) {
		m_Position = { 0.0f,2.0f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}
	//パーティクル
	//if (m_SwordParticleCount < 3) {
	//	m_SwordParticleCount++;
	//}
	//else {
	//	m_SwordParticleCount = 0;
	//}
	//一定時間立ったら前にすすむ
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimeTimer++;
	
	if (m_AnimeTimer == 1) {
		//アニメーションのためのやつ
		m_AnimeLoop = true;
		m_Number = 1;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_Number);
	}

	//剣の更新
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);

	
	//FollowObj_SetParam(m_HandMat);
}
//導入シーンの描画
void Player::IntroductionDraw(DirectXCommon* dxCommon) {
	//FollowObj_Draw();
	Fbx_Draw(dxCommon);
	//FollowObj_Draw();
}