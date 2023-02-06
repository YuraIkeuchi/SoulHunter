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

	SwordParticle* swordparticle_ = new SwordParticle();
	swordparticle_->Initialize();
	swordparticle.reset(swordparticle_);

	Shake* shake_ = new Shake();
	shake.reset(shake_);

	return true;
}
//csvを開く
void Player::OpenCsv() {
	m_PlayerFile.open("Resources/player_state/Player_State.csv");

	m_PlayerPopcom << m_PlayerFile.rdbuf();

	m_PlayerFile.close();
}
//CSVのロード
void Player::LoadCsv() {

	while (getline(m_PlayerPopcom,m_PlayerLine)) {
		//解析しやすくする
		std::istringstream line_stream(m_PlayerLine);

		std::string word;
		//半角スペース区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//飛ばす
			continue;
		}
		//各コマンド
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
//変数の初期化(必要な物のみ)
void Player::StateInitialize() {
	//CSVを開く
	OpenCsv();
	//CSVから値読み込み
	LoadCsv();
}
//更新
void Player::Update()
{
	//手のボーン取得
	m_HandMat = m_fbxObject->GetWorldMat();
	//m_Object->Update();
	m_OldPos = m_Position;
	
	//ムービー中は一部挙動は出来ない
	if (!m_Movie) {
		if (m_GoalDir == No && !m_Death && m_Alive) {
			//移動
			PlayerMove();
			//ジャンプ
			PlayerJump();
			//ダッシュ
			PlayerDush();
			//ローリング
			PlayerRolling();
			//攻撃(剣)
			if (!m_CollideObj) {
				PlayerAttack();
			}
			//HP回復
			PlayerHeal();
		}
		else {
			//ゴール後の動き
			GoalMove();
		}
	}
	if (m_GoalDir == No && !m_Death) {
		//ダメージ
		PlayerDamage();
		//復活処理
		ResPornPlayer();
	}
	//自動落下
	PlayerFall();

	//剣の更新
	SwordUpdate();
	
	//プレイモード
	m_PlayMode = true;
	//ゴールしたときの処理(またゴールしないように)
	if (m_ChangeInterVal) {
		m_GoalIntervalTimer++;
		if (m_GoalIntervalTimer == 120) {
			m_GoalIntervalTimer = 0;
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
//描画
void Player::Draw(DirectXCommon* dxCommon) {	
	//エフェクトの描画
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Draw();
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
//剣の更新
void Player::SwordUpdate() {
	XMVECTOR l_VectorSwordPos;
	//行列を求める
	l_VectorSwordPos.m128_f32[0] = m_HandMat.r[3].m128_f32[0];
	l_VectorSwordPos.m128_f32[1] = m_HandMat.r[3].m128_f32[1];
	l_VectorSwordPos.m128_f32[2] = m_HandMat.r[3].m128_f32[2];
	//変換
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
//エフェクトの更新
void Player::EffectUpdate() {
	//パーティクル生成
	BirthParticle();
	DeathBirthParticle();
	HealParticle();

	//剣のパーティクルの場所を決める
	m_SwordParticlePos = { static_cast<float>(rand() % 1) * -1,
			 static_cast<float>(rand() % 1) + 1,
			0 };

	//エフェクト更新
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
//プレイヤーの移動
void Player::PlayerMove() {
	Input* input = Input::GetInstance();
	//当たり判定を精密に取るため
	m_LimitLeftPos = { m_Position.x - 1.3f,m_Position.y,m_Position.z };
	m_LimitRightPos = { m_Position.x + 1.3f,m_Position.y,m_Position.z };

	//当たり判定
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

	//チュートリアル時移動距離に限界がある
	if (!m_TutorialFinish && m_Position.x >= 73.0f) {
		m_Position.x = 73.0f;
	}
	//地面にいる間は攻撃モーションで動き止まる
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			//動きやジャンプ
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
			//動きやジャンプ
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
		m_FootParticleCount += 1;
	}
}
//プレイヤーのジャンプ
void Player::PlayerJump() {
	Input* input = Input::GetInstance();
	//プレイヤージャンプ処理
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
		if (block->PlayerMapCollideCommon(m_Position, m_Radius, m_OldPos, m_Jump,
			m_AddPower) && m_Alive)
		{
			//初期化
			m_Jump = false;
			m_AddPower = 0.0f;
		}
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
	if (input->TriggerButton(input->Button_A) && !m_Attack && (m_HealType == NoHeal)) {
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
			if (block->AttackMapCollideCommon(m_AttackPos, { 5.5f,0.8f }, m_AttackPos)) {
				BirthEffect("Wall", m_AttackPos, m_PlayerDir);
				m_fbxObject->SetReverse(true);
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

	//ダッシュ中は横に自動で動く
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
//プレイヤーの回転
void Player::PlayerRolling() {
	Input* input = Input::GetInstance();
	//ダッシュ処理
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

	//ローリング中は横に自動で動く
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
//プレイヤーのHP回復
void Player::PlayerHeal() {
	Input* input = Input::GetInstance();
	//押している間貯める
	if (input->PushButton(input->Button_Y)  
		&& (m_HealType == NoHeal) && (m_SoulCount >= 6.0f) && (block->GetHitDown())  && (m_HP < 5) && (PlayerSkill::GetInstance()->GetHealSkill())) {
		m_HealType = UseHeal;
	}

	//回復チャージ
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
			//途中で話した場合回復終了
			if (!input->PushButton(input->Button_Y) || m_Interval != 0) {
				m_HealTimer = 0;
				m_HealType = NoHeal;
				m_HealCount = 0;
			}
		}
	}
}
//ダメージを食らう
void Player::PlayerDamage() {
	//ダメージ時の跳ね返り
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
	//死んだときの判定
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

	//復活処理
	if (!m_Alive) {
		if (m_HP != 0) {
			m_Rotation.x--;
			m_RespornTimer++;
		}
	}

	//棘にあたったときの動き
	if (!m_Alive && m_RespornTimer == 1 && !m_Death) {
		BirthEffect("Damege", m_Position, m_PlayerDir);
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
		block->SetThornDir(NoHit);
		block->SetThornHit(false);
		m_FlashCount = 0;
		m_Interval = 0;
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
			m_DeathParticleCount++;
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
		if (m_AddDisolve >= 1.9f) {
			return true;
		}
	}
	return false;
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
//ポーズ開いたときはキャラが動かない
void Player::Pause() {
	SwordUpdate();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//エディター時の動き
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
	//プレイモードではない
	m_PlayMode = false;
	SwordUpdate();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//パーティクルが出てくる
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
//死んだ時のパーティクル
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
//回復パーティクル
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
//攻撃リセット
void Player::ResetAttack() {
	//攻撃もリセットされる
	m_SecondTimer = 0;
	m_AttackTimer = 0;
	m_Attack = false;
	m_SwordEase = true;
	m_SwordFrame = 0.0f;
	m_SwordType = DeleteSword;
	m_SwordAfterAlpha = 0.0f;
	m_SwordParticleNum = 0;
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
	m_fbxObject->SetPosition(m_Position);
	m_TutorialFinish = true;
	block->SetThornDir(0);
	block->SetThornHit(false);
}
//プレイヤーが敵にあたった瞬間の判定
void Player::PlayerHit(const XMFLOAT3& pos) {
	PlayerAnimetion(Damage, 3);
	m_HP -= 1;
	m_Interval = 100;
	ResetAttack();
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = HitRight;//右側に弾かれる
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = HitLeft;
	}

	if (m_HP == 0 && !m_Death) {
		m_Death = true;
		m_Alive = false;
	}

	//エフェクト生成
	BirthEffect("Damege", m_Position, m_PlayerDir);
}
//プレイヤーが敵にあたった瞬間の判定
void Player::PlayerThornHit(const XMFLOAT3& pos) {
	if (m_Position.x > pos.x) {
		m_BoundPower = 1.0f;
		m_HitDir = HitRight;//右側に弾かれる
	}
	else {
		m_BoundPower = -1.0f;
		m_HitDir = HitLeft;
	}
}
//エフェクト生成
void Player::BirthEffect(const std::string& newname, XMFLOAT3 pos, int dir) {
	PlayerEffect* newEffect;
	newEffect = new PlayerEffect();
	newEffect->CreateEffect(newname, pos, dir);
	newEffect->Initialize();
	effects.push_back(newEffect);
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