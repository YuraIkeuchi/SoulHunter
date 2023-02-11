#pragma once
#include "Block.h"
#include "DirectXCommon.h"

#include "ObjCommon.h"
#include "Shake.h"
#include "PlayerEffect.h"
#include <memory>
using namespace std;         //  名前空間指定

class Player :
	public ObjCommon
{
public:
	void SetBlock(Block* block) { this->block.reset(block); }
	Player();

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;

	void StateInitialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;
	void ImGuiDraw();

	//エフェクトの更新
	void EffectUpdate();
	//プレイヤーの挙動
	//移動
	void PlayerMove();
	//歩きアニメーション
	void WalkAnimation();
	//共通移動処理
	void MoveCommon(float Velocity,int Dir,float RotationY);
	//ジャンプ
	void PlayerJump();
	//落下
	void PlayerFall();
	//攻撃
	void PlayerAttack();
	//攻撃当たり判定を取るか
	bool CheckAttack();
	//ダッシュ
	void PlayerDush();
	//プレイヤーの回転
	void PlayerRolling();
	//HP回復
	void PlayerHeal();
	//ダメージ
	void PlayerDamage();
	//ゴール後の動き
	void GoalMove();
	//死んだ時の動き
	bool DeathMove();
	//プレイヤーが敵にあたった瞬間の判定
	void PlayerHit(const XMFLOAT3& pos);
	//プレイヤーが敵にあたった瞬間の判定
	void PlayerThornHit(const XMFLOAT3& pos);
	/// <summary>
	/// 開放
	/// </summary>
	void Finalize();
	//ポーズのとき
	void Pause();
	//エディターのとき
	void Editor();
	//ステージごとの位置初期化
	void InitPlayer(int StageNUmber);

	//棘にあたった時の復活処理
	void ResPornPlayer();

	//ロードしたときの位置初期化
	void LoadPlayer(const XMFLOAT3& StartPos);

	//足元にパーティクル
	void BirthParticle();
	//死んだ時
	void DeathBirthParticle();
	//回復パーティクル
	void HealParticle();
	//攻撃リセット
	void ResetAttack();

	//アニメーション関係
	void PlayerAnimetion(int Number,int AnimeSpeed);
	//エフェクト生成
	void BirthEffect(const std::string& newname, XMFLOAT3 pos, int dir);

	//csvを開く
	void OpenCsv();
	//csvのロード
	void LoadCsv();
	
	//導入シーンのための処理
	void IntroductionUpdate(int Timer);
	void IntroductionDraw(DirectXCommon* dxCommon);

	//ボス登場シーンのための処理
	void BossAppUpdate(int Timer);
	void BossAppDraw(DirectXCommon* dxCommon);
	//ボス終了シーンのための処理
	void BossEndUpdate(int Timer);
	void BossEndDraw(DirectXCommon* dxCommon);
	//クリアシーンのための処理
	void ClearUpdate(int Timer);
	void ClearDraw(DirectXCommon* dxCommon);
public:
	//getter setter
	bool GetAlive() { return  m_Alive; }
	int GetHP() { return  m_HP; }
	float GetSoulCount() { return  m_SoulCount; }
	int GetInterVal() { return  m_Interval; }
	float GetAddPower() { return  m_AddPower; }
	float GetVelosity() { return  m_Velocity; }
	bool GetChangeInterVal() { return  m_ChangeInterVal; }
	bool GetReadText() { return  m_ReadText; }

	void SetHP(int HP) { this->m_HP = HP; }
	void SetSoulCount(float SoulCount) { this->m_SoulCount = SoulCount; }
	void SetInterval(int Interval) { this->m_Interval = Interval; }
	void SetChangeInterVal(bool m_ChangeInterVal) { this->m_ChangeInterVal = m_ChangeInterVal; }
	void SetGoalDir(int m_GoalDir) { this->m_GoalDir = m_GoalDir; }
	void SetCollideChest(bool m_CollideChest) { this->m_CollideChest = m_CollideChest; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
	void SetReadText(bool m_ReadText) { this->m_ReadText = m_ReadText; }
	void SetTutorialFinish(bool m_TutorialFinish) { this->m_TutorialFinish = m_TutorialFinish; }

private:
	
private:
	vector<PlayerEffect*> effects;

	//クラス
	unique_ptr<Block> block = nullptr;
	
	unique_ptr<Shake> shake = nullptr;
	//プレイモードか
	bool m_PlayMode = false;
	//生きているかどうか
	bool m_Alive = true;
	//リスポーン
	int m_RespornTimer = 0;
	//攻撃できるか
	bool m_Attack = false;
	int m_AttackTimer = 0;
	//2回目の攻撃判定
	int m_AttackCount = 0;
	int m_SecondTimer = 0;
	//HP
	int m_HP = 0;
	//無敵時間
	int m_Interval = 0;
	int m_FlashCount = 0;
	//ダメージ受けたときの反動
	float m_BoundPower = 0.0f;
	//ダメージを受けた向き
	int m_HitDir = 0;
	//プレイヤー関係
	//座標
	XMFLOAT3 m_OldPos = {0.0f,0.0f,0.0f};
	//プレイヤーのマップチップの当たり判定をより正確に行うための処理
	XMFLOAT3 m_LimitPos = { 0.0f,0.0f,0.0f };
	bool m_RightLimit = false;
	bool m_LeftLimit = false;
	//中心点からの大きさ
	XMFLOAT2 m_Radius = {0.0f,0.0f};
	//ジャンプしたかどうか
	bool m_Jump = false;
	//上昇度
	float m_AddPower = 0.0f;
	//重力加速度
	float m_Gravity = 0.0f;
	//ジャンプ回数
	int m_JumpCount = 4;
	//ジャンプ時の動きの変数
	bool m_JumpRot = false;
	float m_RotFrame = 0.0f;
	float m_Velocity = 0.0f;
	//向いている向き
	int m_PlayerDir = 0;
	enum PlayerDir {
		Right,
		Left
	};
	//ダッシュ関係
	bool m_Dush = false;
	bool m_Rolling = false;
	float m_SideFrame = 0.0f;
	float m_SideVelocity = 0.0f;
	//足元のパーティクル
	int m_FootParticleCount = 0;
	//普通のパーティクル
	int m_DeathParticleCount = 0;

	//ゴールしたときの変数
	bool m_ChangeInterVal = false;
	int m_GoalIntervalTimer = 0;
	int m_GoalDir = 0;
	enum GoalDir {
		No,
		LeftGoal,
		RightGoal,
		UpGoal,
		DownGoal
	};
	//宝箱を見ているか
	bool m_ReadText = false;
	bool m_CollideObj = false;
	bool m_CollideChest = false;
	//プレイヤーが使える魂の数
	float m_SoulCount = 20.0f;
	//イージングのため
	float m_Frame = 0.0f;
	//ムービー中の動き
	bool m_Movie = false;
	//復活処理
	int m_SaveTimer = 0;
	XMFLOAT3 m_RespornPos = { 0.0f,0.0f,0.0f };
	//HP回復関係
	int m_HealCount = 0;
	int m_HealTimer = 0;
	int m_HealType = 0;
	enum HealType {
		NoHeal,
		UseHeal,
	};

	//攻撃の位置を取る
	XMFLOAT3 m_AttackPos = { 0.0f,0.0f,0.0f };
	//手行列
	XMMATRIX m_HandMat;

	//死んだ動き
	bool m_Death = false;
	int m_DeathTimer = 0;
	//シェイク用変数
	XMFLOAT3 m_ShakePos = { 0.0f,0.0f,0.0f };

	//アニメーションタイマー用
	struct AnimationTimer {
		int MoveAnimation = 0;
		int NotAnimation = 0;
		int FallAnimation = 0;
	};

	AnimationTimer m_AnimationTimer;
	//プレイヤーのアニメーション
	enum AnimationType {
		FirstAttack,
		SecondAttack,
		Rolling,
		Walk,
		FirstJump,
		Wait,
		Death,
		SecondJump,
		ThirdJump,
		FinalJump,
		Dush,
		Damage,
		Fall
	};

	//csv用変数
	std::ifstream m_PlayerFile;
	std::stringstream m_PlayerPopcom;
	std::string m_PlayerLine;

	//チュートリアル時の変数
	bool m_TutorialFinish = false;
};

