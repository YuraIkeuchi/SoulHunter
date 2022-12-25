#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Block.h"
#include "IKEFBXModel.h"
#include "IKEFBXObject3d.h"
#include "DirectXCommon.h"
#include "PlayerBullet.h"
#include "ParticleTex.h"
#include "VolumManager.h"
#include "ParticleHeal.h"
#include "SwordParticle.h"
#include "ObjCommon.h"
#include "JumpEffect.h"
#include "AttackEffect.h"
#include "PlayerWing.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

class Player :
	public ObjCommon
{
public:
	void SetPlayerBullet(PlayerBullet* playerbullet) { this->playerbullet.reset(playerbullet); }
	void SetBlock(Block* block) { this->block.reset(block); }
	Player();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	//static Player* Create(IKEModel* model = nullptr);

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
	//剣の更新
	void SwordUpdate();
	//エフェクトの更新
	void EffectUpdate();
	//羽関係
	void WingUpdate();
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
	//ダッシュ
	void PlayerDush();
	//弾を撃つ
	void PlayerShot();
	//必殺技
	void PlayerSpecial();
	//HP回復
	void PlayerHeal();
	//ダメージ
	void PlayerDamage();
	//エフェクト発生
	void JumpArgment();
	void AttackArgment();
	//ゴール後の動き
	void GoalMove();
	//プレイヤーが敵にあたった瞬間の判定
	void PlayerHit(const XMFLOAT3& pos);
	//プレイヤーが敵にあたった瞬間の判定
	void PlayerThornHit(const XMFLOAT3& pos);
	//スキルリセット
	void ResetSkill();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

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

	//アニメーション関係
	void PlayerAnimetion(int Number,int AnimeSpeed);
	
	//導入シーンのための処理
	void IntroductionUpdate(int Timer);
	void IntroductionDraw(DirectXCommon* dxCommon);

	//ボスシーンのための処理
	void BossAppUpdate(int Timer);
	void BossAppDraw(DirectXCommon* dxCommon);
public:
	//getter setter
	const XMFLOAT3& GetAttackPos() { return  m_AttackPos; }
	bool GetAlive() { return  m_Alive; }
	int GetHP() { return  m_HP; }
	int GetJumpCount() { return  m_JumpCount; }
	float GetSoulCount() { return  m_SoulCount; }
	int GetInterVal() { return  m_Interval; }
	float GetCameraDistance() { return  m_CameraDistance; }
	float GetAddPower() { return  m_AddPower; }
	float GetVelosity() { return  m_Velocity; }
	bool GetUseCompass() { return  s_UseCompass; }
	bool GetUseLibra() { return  s_UseLibra; }
	bool GetUseDush() { return  s_UseDush; }
	bool GetUseHeal() { return  s_UseHeal; }
	bool GetEffect() { return  m_Effect; }
	int GetAttackTimer() { return  m_AttackTimer; }
	bool GetDush() { return  m_Dush; }
	bool GetChangeInterVal() { return  m_ChangeInterVal; }
	bool GetSpecialEffect() { return  m_SpecialEffect; }
	bool GetReadText() { return  m_ReadText; }

	void SetHP(int HP) { this->m_HP = HP; }
	void SetSoulCount(float SoulCount) { this->m_SoulCount = SoulCount; }
	void SetInterval(int Interval) { this->m_Interval = Interval; }
	void SetEffect(bool effect) { this->m_Effect = effect; }
	void SetSpecialEffect(bool SpecialEffect) { this->m_SpecialEffect = SpecialEffect; }
	void SetUseDush(bool UseDush) { this->s_UseDush = UseDush; }
	void SetUseLibra(bool UseLibra) { this->s_UseLibra = UseLibra; }
	void SetUseCompass(bool UseCompass) { this->s_UseCompass = UseCompass; }
	void SetUseHeal(bool UseHeal) { this->s_UseHeal = UseHeal; }
	void SetChangeInterVal(bool m_ChangeInterVal) { this->m_ChangeInterVal = m_ChangeInterVal; }
	void SetGoalDir(int m_GoalDir) { this->m_GoalDir = m_GoalDir; }
	void SetCollideObj(bool m_CollideObj) { this->m_CollideObj = m_CollideObj; }
	void SetCollideChest(bool m_CollideChest) { this->m_CollideChest = m_CollideChest; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
	void SetReadText(bool m_ReadText) { this->m_ReadText = m_ReadText; }

private:
	//スキルを使えるかどうか
	static bool s_UseDush;
	static bool s_UseLibra;
	static bool s_UseCompass;
	static bool s_UseHeal;
private:
	//攻撃の位置を取る
	XMFLOAT3 m_AttackPos = { 0.0f,0.0f,0.0f };
	unique_ptr<ParticleTex> particletex = nullptr;
	unique_ptr<SwordParticle> swordparticle = nullptr;
	unique_ptr<ParticleHeal> particleheal = nullptr;
	//クラス
	unique_ptr<PlayerBullet> playerbullet = nullptr;
	unique_ptr<Block> block = nullptr;
	std::vector<JumpEffect*> jumpeffects;
	std::vector<AttackEffect*> attackeffects;
	unique_ptr<PlayerWing> playerwing = nullptr;
	//プレイモードか
	bool m_PlayMode = false;
	//生きているかどうか
	bool m_Alive = true;
	//リスポーン
	int m_RespornTimer = 0;
	//攻撃できるか
	bool m_Attack = false;
	int m_AttackTimer = 0;
	//攻撃時のエフェクト発生条件
	bool m_AttackArgment = false;
	//HP
	int m_HP = 5;
	//無敵時間
	int m_Interval = 0;
	int m_FlashCount = 0;
	//ダメージ受けたときの反動
	float m_BoundPower = 0.0f;
	//ダメージを受けた向き
	int m_HitDir = 0;
	//ダメージ時のエフェクト
	bool m_Effect = false;
	//プレイヤー関係
	//座標
	XMFLOAT3 m_OldPlayerPos = {0.0f,0.0f,0.0f};
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
	//ジャンプ時のエフェクト発生条件
	bool m_JumpArgment = false;
	//向いている向き
	float m_Velocity = 0.0f;
	int m_PlayerDir = 0;
	enum PlayerDir {
		Right,
		Left
	};
	//ダッシュ関係
	bool m_Dush = false;
	int m_DushTimer = 15;
	enum DushDir {
		NoDush,
		DushRight,
		DushLeft,
	};
	int m_DushDir = 0;
	//足元のパーティクル
	int m_FoodParticleNum = 5;
	float m_FoodParticleCount = 0;
	XMFLOAT3 m_FoodParticlePos = { 0.0f,0.0f,0.0f };
	//普通のパーティクル
	int m_ParticleCount = 0;
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	//剣のパーティクル
	int m_SwordParticleCount = 0;
	XMFLOAT3 m_SwordParticlePos = { 0.0f,0.0f,0.0f };
	//ゴールしたときの変数
	bool m_ChangeInterVal = false;
	int m_IntervalTimer = 0;
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
	//アニメーション関係
	int m_Number = 0;
	bool m_AnimeLoop = false;
	int m_AnimeTimer = 0;
	int m_AnimeSpeed = 1;
	bool m_AnimationStop = false;
	//必殺技
	bool m_Special = false;
	float m_Frame = 0.0f;
	float m_AfterPosY = 0.0f;
	int m_SpecialCount = 0;
	bool m_SpecialEffect = false;
	//必殺技時のカメラの距離
	float m_CameraDistance = 0.0f;
	//パーティクルのための変数
	int m_ParticleNumber = 0;
	float m_BulletDistance = 0.0f;
	//提出用の攻撃タイプ
	int m_AttackType = 0;
	enum AttackType {
		Sword,
		Shot,
		Special
	};
	//ムービー中の動き
	bool m_Movie = false;
	//ディゾルブ
	float Disolve = -1.0f;
	//復活処理
	int m_SaveTimer = 0;
	XMFLOAT3 m_RespornPos = { 0.0f,0.0f,0.0f };
	//HP回復関係
	int m_HealCount = 0;
	int m_HealTimer = 0;
	int m_HealType = 0;
	enum HealType {
		NoHeal,
		InterVal,
		Invocation,
		Fail,
	};

	//手行列
	XMMATRIX m_HandMat;
	XMVECTOR m_VectorSwordPos;//剣の座標
	XMFLOAT3 m_SwordPos;//剣の座標
	XMFLOAT3 m_SwordRotation = { 60.0f,100.0f,0.0f };
	XMFLOAT4 m_SwordColor = { 1.0f,1.0f,0.0f,0.0f };
	float m_SwordFrame = 0.0f;
	bool m_SwordEase = false;
	int m_SwordType = 0;
	int m_SwordParticleNum = 0;
	float m_SwordAfterAlpha = 0.0f;
	enum SwordType {
		NoSword,
		ArgSword,
		DeleteSword,
	};
	XMFLOAT3 m_WingPosition = { 0.0f,0.0f,0.0f };
	int m_WingDeleteCount = 0;
};

