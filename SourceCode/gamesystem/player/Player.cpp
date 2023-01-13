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
	m_FollowObject_->SetScale(m_SwordScale);
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

	Shake* shake_ = new Shake();
	shake.reset(shake_);

	return true;
}
//変数の初期化
void Player::StateInitialize() {
	m_Scale = { 3.0f, 3.0f, 3.0f };
	m_Position = { 20.0f,-100.0f,0.0f };
	m_Rotation = { 0.0f,90.0f,0.0f };
	m_AddDisolve = 0.0f;
	m_Addcolor = { 0.0f,0.0f,0.0f,1.0f };
	m_HP = 5;
	m_Interval = 0;
	m_FlashCount = 0;
	m_Death = false;
	m_RespornTimer = 0;
	m_Alive = true;
	//プレイヤー関係
	m_OldPlayerPos = { 0, 0, 0 };
	m_Radius.x = 1.3f * m_Scale.x;
	m_Radius.y = 0.7f * m_Scale.y;
	m_Jump = false;
	m_AddPower = -0.01f;
	m_Gravity = 0.02f;
}
//更新
void Player::Update()
{
	//手のボーン取得
	m_HandMat = m_fbxObject->GetWorldMat();
	//m_Object->Update();
	m_OldPlayerPos = m_Position;
	
	//ムービー中は一部挙動は出来ない
	if (!m_Movie) {
		if (m_GoalDir == No && !m_Death) {
			//移動
			PlayerMove();
			//ジャンプ
			PlayerJump();
			//ダッシュ
			PlayerDush();
			//攻撃(剣)
			if (!m_CollideObj) {
				PlayerAttack();
			}
			//HP回復
			PlayerHeal();
			//ダメージ
			PlayerDamage();
			//復活処理
			ResPornPlayer();
			//エフェクト発生関係
			AttackArgment();
			WallArgment();
			DushArgment();
			DamageArgment();
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

	//エフェクトの更新
	EffectUpdate();

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
//エフェクトの更新
void Player::EffectUpdate() {
	//パーティクルのカウント数の更新
	if (m_ParticleCount > 3) {
		m_ParticleCount = 0;
	}

	if (m_HealCount > 3) {
		m_HealCount = 0;
	}
	//パーティクルを出す
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };

	//パーティクル関係
	particletex->SetStartColor({ 1.0f,0.9f,0.8f,1.0f });
	
	particletex->Update(m_ParticlePos, m_ParticleCount, 3, m_ParticleNumber);
	particleheal->SetStartColor({ 0.5f,1.0f,0.1f,1.0f });
	particleheal->Update({ m_Position.x,m_Position.y - 1.0f,m_Position.z }, m_HealCount, 3);
	swordparticle->SetStartColor({ 1.0f,0.5f,0.0f,1.0f });
	for (int i = 0; i < m_SwordParticleNum; i++) {
		swordparticle->SetParticle(m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));
	}
	swordparticle->Update(m_SwordParticlePos, m_SwordParticleCount, 1, m_FollowObject->GetMatrix2(m_HandMat));

	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Update();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Update(m_AttackPos, m_PlayerDir);
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Update(m_Position, m_Dush);
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Update(m_Position, m_Effect);
		}
	}
}
//プレイヤーの移動
void Player::PlayerMove() {
	Input* input = Input::GetInstance();
	//当たり判定を精密に取るため
	m_LimitLeftPos = { m_Position.x - 2.3f,m_Position.y,m_Position.z };
	m_LimitRightPos = { m_Position.x + 2.3f,m_Position.y,m_Position.z };

	//当たり判定
	if (block->LimitMapCollideCommon(m_LimitLeftPos, { 2.0f,1.0f }, m_LimitLeftPos)) {
		m_LeftLimit = true;
	}
	else {
		m_LeftLimit = false;
	}

	if (block->LimitMapCollideCommon(m_LimitRightPos, { 2.0f,1.0f }, m_LimitRightPos)) {
		m_RightLimit = true;
	}
	else {
		m_RightLimit = false;
	}
	//地面にいる間は攻撃モーションで動き止まる
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			//動きやジャンプ
			if (input->LeftTiltStick(input->Right) && (!m_Dush) && (m_Alive)) {
				if (!m_RightLimit) {
					MoveCommon(0.3f, Right, 90.0f);
				}
				else {
					MoveCommon(0.0f, Right, 90.0f);
				}
			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush) && (m_Alive)) {
				if (!m_LeftLimit) {
					MoveCommon(-0.3f, Left, 270.0f);
				}
				else {
					MoveCommon(0.0f, Left, 270.0f);
				}

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
			if (input->LeftTiltStick(input->Right) && (!m_Dush) && (m_Alive)) {
				MoveCommon(0.3f, Right, 90.0f);

			}

			if (input->LeftTiltStick(input->Left) && (!m_Dush) && (m_Alive)) {
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
		if ((m_AnimationTimer.MoveAnimation < 3) && (m_JumpCount == 0) && (!m_AnimationStop)) {
			m_AnimationTimer.MoveAnimation++;
			m_AnimationTimer.NotAnimation = 0;
		}
		if (m_AnimationTimer.MoveAnimation == 1) {
			//アニメーションのためのやつ
			m_AnimeLoop = true;
			m_AnimationType = Walk;
			m_AnimeSpeed = 1;
			m_fbxObject->PlayAnimation(m_AnimationType);
		}
	}
	//止まっている
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
	if (input->TriggerButton(input->Button_B) && (m_JumpCount < 4) && (m_AddPower <= 0.3f)
		&& (m_HealType == NoHeal) && (m_Alive)) {
		m_JumpCount++;
		m_Jump = true;
		m_ParticleCount = 0;
		m_AddPower = 0.8f;
	
		if (m_JumpCount == 1) {
			PlayerAnimetion(FirstJump, 2);
		}
		else if (m_JumpCount == 2) {
			PlayerAnimetion(SecondJump, 2);
		}
		else if (m_JumpCount == 3) {
			PlayerAnimetion(ThirdJump, 2);
		}
		else if (m_JumpCount == 4) {
			PlayerAnimetion(FinalJump, 2);
			m_JumpRot = true;
			m_RotFrame = 0.0f;
		}
	}

	//四回目はジャンプ時回転する
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
	//エフェクトの発生
}
//プレイヤーの落下
void Player::PlayerFall() {
	if (m_HP != 0) {
		m_Gravity = 0.02f;
	}
	else {
		m_Gravity = 0.001f;
	}
	if (m_Jump) {
		//ジャンプ処理
	//ダッシュ中のときは重力がない
		if (!m_Dush) {
			m_AddPower -= m_Gravity;
			m_Position.y += m_AddPower;
		}

		//壁との当たり判定
		if (block->PlayerMapCollideCommon(m_Position, m_Radius, m_OldPlayerPos, m_Jump,
			m_AddPower) && m_Alive)
		{
			//初期化
			m_Jump = false;
			m_AddPower = 0.0f;
		}

		//空中アニメーション
		/*m_AnimationTimer.FallAnimation++;
		if (m_AnimationTimer.FallAnimation == 1) {
			PlayerAnimetion(10, 1);
		}*/
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
	}
}
//プレイヤーの攻撃
void Player::PlayerAttack() {
	Input* input = Input::GetInstance();
	//攻撃
	if (input->TriggerButton(input->Button_A) && !m_Attack && (m_HealType == NoHeal) && (m_Alive)) {
		if (!m_CollideChest) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Sword.wav", VolumManager::GetInstance()->GetSEVolum());
			m_Attack = true;
			//攻撃回数によって動きが変わる
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
			//剣の処理
			m_SwordEase = true;
			m_SwordFrame = 0.0f;
			m_SwordType = ArgSword;
			m_SwordAfterAlpha = 1.0f;
		}
		else {
			m_fbxObject->StopAnimation();
		}
	}	
	//攻撃のインターバル
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

		//攻撃エフェクトの出現
		if (m_AttackTimer == 20) {
			//攻撃範囲の設定
			//攻撃の向き
			//右向き
			if (m_Rotation.y == 90.0f) {
				m_AttackPos = { m_Position.x + 4.0f,m_Position.y,m_Position.z };
			}
			//左向き
			else if (m_Rotation.y == 270.0f) {
				m_AttackPos = { m_Position.x - 4.0f,m_Position.y,m_Position.z };
			}

			//攻撃時壁にあたった場合壁からパーティクルを出す
			if (block->AttackMapCollideCommon({ m_AttackPos.x,m_SwordPos.y,m_AttackPos.z }, { 5.5f,0.8f }, { m_AttackPos.x,m_SwordPos.y,m_AttackPos.z })) {
				m_WallArgment = true;
			}
		}

		//一定フレームで攻撃終了
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

		//攻撃が地面で行われた場合砂煙が発生する
		if (!m_Jump && m_AddPower == 0.0f) {
			m_FoodParticleCount += 0.25f;
			m_FoodParticlePos = {
		m_AttackPos.x,
		m_AttackPos.y - 2.0f,
		m_AttackPos.z,
			};
		}
	}
	else {
		//一定フレーム以内だったら2段階目の攻撃が出る
		if (m_AttackCount == 1) {
			m_SecondTimer++;
			if (m_SecondTimer >= 40) {
				m_AttackCount = 0;
				m_SecondTimer = 0;
			}
		}
	}
}
//攻撃判定を取るか
bool Player::CheckAttack() {
	//攻撃モーションによって判定取るフレームが違う
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
//プレイヤーのダッシュ
void Player::PlayerDush() {
	Input* input = Input::GetInstance();
	//ダッシュ処理
	if ((!m_Dush) && (m_SoulCount >= 2.0f) && (m_AddPower != 0.0f) && (m_Alive) && (s_UseDush)) {
		if (input->TriggerButton(input->Button_RB)) {
			m_DushArgment = true;
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
			PlayerAnimetion(Dush, 4);
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
			m_ParticleCount = 0;
			m_DushDir = NoDush;
			m_Dush = false;
			m_DushTimer = 10;
		}
	}
}
//プレイヤーのHP回復
void Player::PlayerHeal() {
	Input* input = Input::GetInstance();
	//押している間貯める
	if (input->PushButton(input->Button_Y) && (s_UseHeal) && (m_HP <= 4)
		&& (m_HealType == NoHeal) && (m_SoulCount >= 6.0f) && (block->GetHitDown())) {
		m_HealType = InterVal;
	}

	if (m_HealType == InterVal) {
		m_HealCount++;
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
	}
	else if (m_HealType == Fail) {
		if (m_Frame < 1.0f) {
			m_Frame += 0.1f;
		}
		else {
			m_HealType = NoHeal;
		}
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


	//死んだときの判定
	if (block->GetThornHit()) {
		if (m_HP >= 2) {
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
		}
		else {
			if (block->GetThornDir() == 1) {
				m_AddPower = 0.0f;
				m_BoundPower = 0.0f;
			}
			else if (block->GetThornDir() == 2) {
				m_AddPower = 0.0f;
				m_BoundPower = 0.0f;
			}
			else if (block->GetThornDir() == 3) {
				m_AddPower = 0.0f;
				m_BoundPower = 0.0f;
				m_HitDir = 1;
			}
			else if (block->GetThornDir() == 4) {
				m_AddPower = 0.0f;
				m_BoundPower = 0.0f;
				m_HitDir = 2;
			}
			if (!m_Death) {
				m_HP -= 1;
				m_Effect = true;
				m_Death = true;
			}
		}
		m_DamageArgment = true;
		m_Alive = false;
		block->SetThornDir(0);
		block->SetThornHit(false);
	}

	//復活処理
	if (!m_Alive && m_HP >= 1) {
		if (m_HP != 0) {
			m_RespornTimer++;
			m_Rotation.x--;
		}
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
//エフェクト発生(攻撃)
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
//壁にあたった時のエフェクト
void Player::WallArgment() {
	if (m_WallArgment) {
		WallAttackEffect* newwallEffect;
		newwallEffect = new WallAttackEffect();
		newwallEffect->Initialize();
		walleffects.push_back(newwallEffect);
		m_WallArgment = false;
	}
}
//エフェクト発生(ダッシュ)
void Player::DushArgment() {
	if (m_DushArgment) {
		PlayerDushEffect* newDushEffect;
		newDushEffect = new PlayerDushEffect();
		newDushEffect->Initialize();
		dusheffects.push_back(newDushEffect);
		m_DushArgment = false;
	}
}
//エフェクト発生(ダメージ)
void Player::DamageArgment() {
	if (m_DamageArgment) {
		PlayerDamageEffect* newDamageEffect;
		newDamageEffect = new PlayerDamageEffect();
		newDamageEffect->Initialize();
		damageeffects.push_back(newDamageEffect);
		m_DamageArgment = false;
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
//ゴールの動き
bool Player::DeathMove() {
	if (m_Death) {
		m_DeathTimer++;
		//最初にアニメーションが入る
		if (m_DeathTimer == 1) {
			PlayerAnimetion(Death, 1);
		}
		//前を向く
		if (m_DeathTimer >= 10) {
			if (m_Frame < m_FrameMax) {
				m_Frame += 0.05f;
			}
			else {
				m_Frame = m_FrameMax;
			}

			m_Rotation.y = Ease(In, Cubic, m_Frame, m_Rotation.y, 180.0f);
		}

		//シェイクする
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
			//シェイク始まったらパーティクル
			m_ParticleCount++;
			//ディゾルブで消す
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
		particletex->SetParticleBreak(true);
		m_ParticleNumber = 2;
		m_ParticlePos = m_Position;
		if (m_AddDisolve >= 1.9f) {
			return true;
		}
	}

	return false;
}
//描画
void Player::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("player");
	ImGui::SetWindowPos(ImVec2(1000, 450));
	ImGui::SetWindowSize(ImVec2(280, 300));
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::Text("LimitRightPosX:%f", m_LimitRightPos.x);
	ImGui::Text("LimitLeftPosX:%f", m_LimitLeftPos.x);
	ImGui::Text("LimitRight::%d", m_RightLimit);
	ImGui::Text("LimitLeft::%d", m_LeftLimit);
	ImGui::End();

	//エフェクトの描画
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Draw();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Draw();
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Draw();
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Draw();
		}
	}

	//点滅してるかどうかで描画が変わる
	if (m_FlashCount % 2 == 0 && m_PlayMode) {
		if (m_SwordColor.w >= 0.1f && m_HP != 0) {
			FollowObj_Draw();
		}
		if (m_AddDisolve <= 1.5f) {
			Fbx_Draw(dxCommon);
		}
	}
	//パーティクルの描画
	particleheal->Draw();
	particletex->Draw();
	if (m_HP != 0) {
		swordparticle->Draw();
	}
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
	attackeffects.clear();
	walleffects.clear();
	dusheffects.clear();
	damageeffects.clear();
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

	//m_AnimeLoop = true;
	//m_AnimeSpeed = 2;
	//m_AnimationType = 3;
	//m_fbxObject->PlayAnimation(m_AnimationType);
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
			ParticleManager::GetInstance()->Add(30, { m_FoodParticlePos.x + vel.x,(m_FoodParticlePos.y) + vel.y,m_FoodParticlePos.z }, vel, XMFLOAT3(), 1.2f, 0.6f);
		}
		m_FoodParticleCount = 0.0f;
	}
}
//アニメーションの共通変数
void Player::PlayerAnimetion(int Number, int AnimeSpeed) {
	m_AnimationType = Number;
	m_AnimeLoop = false;
	m_AnimationTimer.MoveAnimation = 0;
	m_AnimeSpeed = AnimeSpeed;
	m_AnimationStop = true;
	m_fbxObject->PlayAnimation(m_AnimationType);
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
			m_Rotation.x = 0.0f;
			m_Position = m_RespornPos;
		}
	}
}
//ロードしたときの初期化
void Player::LoadPlayer(const XMFLOAT3& StartPos) {
	m_Position = StartPos;
	//m_Object->SetPosition(m_Position);
	m_fbxObject->SetPosition(m_Position);
	block->SetThornDir(0);
	block->SetThornHit(false);
}
//プレイヤーが敵にあたった瞬間の判定
void Player::PlayerHit(const XMFLOAT3& pos) {
	PlayerAnimetion(Damage, 3);
	m_Effect = true;
	m_DamageArgment = true;
	m_HP -= 1;
	m_Interval = 100;
	//攻撃もリセットされる
	m_SecondTimer = 0;
	m_AttackTimer = 0;
	m_Attack = false;
	m_SwordEase = true;
	m_SwordFrame = 0.0f;
	m_SwordType = DeleteSword;
	m_SwordAfterAlpha = 0.0f;
	m_SwordParticleCount = 0;
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = 1;//右側に弾かれる
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = 2;
	}

	if (m_HP == 0 && !m_Death) {
		m_Death = true;
		m_Alive = false;
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
	//フレーム数で動きが決まる
	if (Timer == 1) {
		m_Position = { 0.0f,2.2f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	//一定時間立ったら前にすすむ
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimationTimer.MoveAnimation++;
	
	if (m_AnimationTimer.MoveAnimation == 1) {
		//アニメーションのためのやつ
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}

	//剣の更新
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//導入シーンの描画
void Player::IntroductionDraw(DirectXCommon* dxCommon) {
	//FollowObj_Draw();
	Fbx_Draw(dxCommon);
	//FollowObj_Draw();
}
//ボス登場シーンの更新
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
//ボス終了シーンの更新
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
//クリアシーンの更新
void Player::ClearUpdate(int Timer) {
	//フレーム数で動きが決まる
	if (Timer == 1) {
		m_Position = { 0.0f,5.0f,-250.0f };
		m_Rotation = { 0.0f,0.0f,0.0f };
	}
	m_Position.z += 0.3f;
	m_AnimationTimer.MoveAnimation++;

	if (m_AnimationTimer.MoveAnimation == 1) {
		//アニメーションのためのやつ
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//導入シーンの描画
void Player::ClearDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}