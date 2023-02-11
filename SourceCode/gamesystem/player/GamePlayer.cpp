#include "GamePlayer.h"
#include "Input.h"
#include "ModelManager.h"
#include "ParticleManager.h"
#include "PlayerSkill.h"
#include "VariableCommon.h"
#include "VolumManager.h"
#include "ParticleEmitter.h"
#include "Audio.h"
#include "PlayerSword.h"
#include <Easing.h>
using namespace DirectX;
//読み込み
GamePlayer::GamePlayer() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}
//初期化
bool GamePlayer::Initialize()
{

	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	Shake* shake_ = new Shake();
	shake.reset(shake_);

	PlayerSword::GetInstance()->Initialize();

	return true;
}
//csvを開く
void GamePlayer::OpenCsv() {
	m_PlayerFile.open("Resources/player_state/Player_State.csv");

	m_PlayerPopcom << m_PlayerFile.rdbuf();

	m_PlayerFile.close();
}
//CSVのロード
void GamePlayer::LoadCsv() {

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
void GamePlayer::StateInitialize() {
	//CSVを開く
	OpenCsv();
	//CSVから値読み込み
	LoadCsv();
}
//更新
void GamePlayer::Update()
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

	//剣の更新
	PlayerSword::GetInstance()->SetHandMat(m_HandMat);
	PlayerSword::GetInstance()->Update();
}
//描画
void GamePlayer::Draw(DirectXCommon* dxCommon) {	
	//エフェクトの描画
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Draw();
		}
	}
	//点滅してるかどうかで描画が変わる
	if (m_FlashCount % 2 == 0 && m_PlayMode) {
		if (m_HP != 0) {
			PlayerSword::GetInstance()->Draw(dxCommon);
		}
		if (m_AddDisolve <= 1.5f) {
			Fbx_Draw(dxCommon);
		}
	}
	//パーティクルの描画
	if (m_HP != 0) {
		PlayerSword::GetInstance()->ParticleDraw();
	}
}
//Imgui
void GamePlayer::ImGuiDraw() {
	ImGui::Begin("player");
	ImGui::Text("m_LimitPosX:%f", m_LimitPos.x);
	ImGui::Text("m_PosX:%f", m_Position.x);
	ImGui::Text("m_PosY:%f", m_Position.y);
	ImGui::Text("RotY:%f", m_Rotation.y);
	ImGui::Text("LeftL:%d", m_LeftLimit);
	ImGui::Text("RightL:%d", m_RightLimit);
	ImGui::End();

	PlayerSword::GetInstance()->ImGuiDraw();
}
//エフェクトの更新
void GamePlayer::EffectUpdate() {
	//パーティクル生成
	BirthParticle();
	DeathBirthParticle();
	HealParticle();

	//エフェクト更新
	for (PlayerEffect* neweffect : effects) {
		if (neweffect != nullptr) {
			neweffect->Update();
		}
	}
}
//プレイヤーの移動
void GamePlayer::PlayerMove() {
	Input* input = Input::GetInstance();
	//チュートリアル時移動距離に限界がある
	if (!m_TutorialFinish && m_Position.x >= 73.0f) {
		m_Position.x = 73.0f;
	}
	//地面にいる間は攻撃モーションで動き止まる
	if (m_AddPower == 0.0f) {
		if ((input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left)) && (m_HealType == NoHeal) && (!m_Attack)) {
			////当たり判定を精密に取るため
			if (m_Rotation.y == 90.0f) {
				m_LimitPos = { m_Position.x + 1.3f, m_Position.y, m_Position.z };
			}
			else if (m_Rotation.y == 270.0f) {
				m_LimitPos = { m_Position.x - 1.3f, m_Position.y, m_Position.z };
			}

			//当たり判定
			if (block->LimitMapCollideCommon(m_LimitPos, { 3.0f,1.0f }, m_LimitPos) && m_Rotation.y == 90.0f) {
				m_RightLimit = true;
			}
			else {
				m_RightLimit = false;
			}

			if (block->LimitMapCollideCommon(m_LimitPos, { 3.0f,1.0f }, m_LimitPos) && m_Rotation.y == 270.0f) {
				m_LeftLimit = true;
			}
			else {
				m_LeftLimit = false;
			}

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
void GamePlayer::WalkAnimation() {
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
void GamePlayer::MoveCommon(float Velocity, int Dir, float RotationY) {
	m_Velocity = Velocity;
	m_PlayerDir = Dir;
	m_Rotation.y = RotationY;
	if (!m_Jump && m_AddPower == 0.0f) {
		m_FootParticleCount += 1;
	}
}
//プレイヤーのジャンプ
void GamePlayer::PlayerJump() {
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
void GamePlayer::PlayerFall() {
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
void GamePlayer::PlayerAttack() {
	Input* input = Input::GetInstance();
	//攻撃
	if (input->TriggerButton(input->Button_A) && !m_Attack && (m_HealType == NoHeal)) {
		if (!m_CollideChest) {
			Audio::GetInstance()->PlayWave("Resources/Sound/SE/Sword.wav", VolumManager::GetInstance()->GetSEVolum());
			m_Attack = true;
			PlayerSword::GetInstance()->SwordBirth();
			//攻撃回数によって動きが変わる
			m_AttackCount++;
			if (m_AttackCount == 1) {
				PlayerSword::GetInstance()->SetRotation({ 32.0f,91.0f,48.0f });
				PlayerAnimetion(FirstAttack, 3);
			}
			else if(m_AttackCount == 2) {
				m_AttackCount = 0;
				PlayerSword::GetInstance()->SetRotation({ 0.0f, 90.0f, 60.0f });
				PlayerAnimetion(SecondAttack, 3);
			}
		}
		else {
			m_fbxObject->StopAnimation();
		}
	}	
	//攻撃のインターバル
	if (m_Attack) {
		m_AttackTimer++;
		if (m_AttackTimer <= 20) {
			PlayerSword::GetInstance()->SetSwordParticleNum(1);
		}
		else if(m_AttackTimer >= 21 && m_AttackTimer <= 30) {
			PlayerSword::GetInstance()->SetSwordParticleNum(7);
		}
		else {
			PlayerSword::GetInstance()->SetSwordParticleNum(0);
		}

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
			ResetAttack();
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
bool GamePlayer::CheckAttack() {
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
void GamePlayer::PlayerDush() {
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
void GamePlayer::PlayerRolling() {
	Input* input = Input::GetInstance();
	//ローリング
	if ((!m_Rolling) && (m_AddPower == 0.0f) && (m_JumpCount == 0) && (block->GetHitDown())) {
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
void GamePlayer::PlayerHeal() {
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
void GamePlayer::PlayerDamage() {
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
void GamePlayer::GoalMove() {
	if (m_GoalDir == RightGoal) {
		m_Position.x += 0.3f;
	}
	else if (m_GoalDir == LeftGoal) {
		m_Position.x -= 0.3f;
	}
}
//ゴールの動き
bool GamePlayer::DeathMove() {
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
void GamePlayer::Finalize()
{
}
//各マップごとの位置初期化
void GamePlayer::InitPlayer(int StageNumber) {
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
void GamePlayer::Pause() {
	PlayerSword::GetInstance()->Update();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//エディター時の動き
void GamePlayer::Editor() {
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
	PlayerSword::GetInstance()->Update();
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, 1, m_AnimationStop);
}
//パーティクルが出てくる
void GamePlayer::BirthParticle() {
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
void GamePlayer::DeathBirthParticle() {
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
void GamePlayer::HealParticle() {
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
void GamePlayer::ResetAttack() {
	//攻撃もリセットされる
	m_SecondTimer = 0;
	m_AttackTimer = 0;
	m_Attack = false;
	PlayerSword::GetInstance()->SwordFinish();
}
//アニメーションの共通変数
void GamePlayer::PlayerAnimetion(int Number, int AnimeSpeed) {
	m_AnimationType = Number;
	m_AnimeLoop = false;
	m_AnimationTimer.MoveAnimation = 0;
	m_AnimeSpeed = AnimeSpeed;
	m_AnimationStop = true;
	m_fbxObject->PlayAnimation(m_AnimationType);
}
//生き返った時の位置
void GamePlayer::ResPornPlayer() {
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
void GamePlayer::LoadPlayer(const XMFLOAT3& StartPos) {
	m_Position = StartPos;
	m_fbxObject->SetPosition(m_Position);
	m_TutorialFinish = true;
	block->SetThornDir(0);
	block->SetThornHit(false);
}
//プレイヤーが敵にあたった瞬間の判定
void GamePlayer::PlayerHit(const XMFLOAT3& pos) {
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
void GamePlayer::PlayerThornHit(const XMFLOAT3& pos) {
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
void GamePlayer::BirthEffect(const std::string& newname, XMFLOAT3 pos, int dir) {
	PlayerEffect* newEffect;
	newEffect = new PlayerEffect();
	newEffect->CreateEffect(newname, pos, dir);
	newEffect->Initialize();
	effects.push_back(newEffect);
}
//ボス登場シーンの更新
void GamePlayer::BossAppUpdate(int Timer) {
	m_AnimeLoop = true;
	m_AnimeSpeed = 1;
	m_AnimationType = Wait;
	m_fbxObject->PlayAnimation(m_AnimationType);
	m_fbxObject->SetPosition({ 0.0f,8.0f,0.0f });
	m_fbxObject->SetRotation({ 0.0f,0.0f,0.0f });
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
void GamePlayer::BossAppDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
//ボス終了シーンの更新
void GamePlayer::BossEndUpdate(int Timer) {
	m_AnimeLoop = true;
	m_AnimeSpeed = 1;
	m_AnimationType = Wait;
	m_fbxObject->PlayAnimation(m_AnimationType);
	m_fbxObject->SetPosition({ 0.0f,8.0f,0.0f });
	m_fbxObject->SetRotation({ 0.0f,0.0f,0.0f });
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
void GamePlayer::BossEndDraw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
