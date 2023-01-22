#pragma once
#include "Player.h"
#include "IKETexture.h"
#include "ParticleTex.h"
#include "BossEffect.h"
#include "CollisionPrimitive.h"
#include "ObjCommon.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

class InterBoss :
	public ObjCommon {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }

	//gettersetter
	bool GetEffect() { return  m_Effect; }
	bool GetAlive() { return  m_Alive; }
	const float& GetHP() { return  m_HP; }
	const int& GetDeathTimer() { return  m_DeathTimer; }

	void SetEffect(bool effect) { this->m_Effect = effect; }
	void SetAlive(bool m_Alive) { this->m_Alive = m_Alive; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
public:
	
	//初期化
	virtual bool Initialize() = 0;
	//初期化
	virtual bool BattleInitialize() = 0;
	//更新
	void Update();
	/// <summary>
	/// ポーズのとき
	/// </summary>
	virtual void Pause() = 0;
	//描画
	void Draw(DirectXCommon* dxCommon);
	//登場シーン更新
	void AppUpdate();
	//登場シーン描画
	void AppDraw(DirectXCommon* dxCommon);
	//終了シーン更新
	void EndUpdate();
	//終了シーン描画
	void EndDraw(DirectXCommon* dxCommon);
	virtual void App() = 0;//ボス出現モーション

	virtual void Spec() = 0;//ボス特有の処理

	virtual void Dead() = 0;//ボス特有の処理
	virtual void End() = 0;//ボス特有の処理
	virtual void specialDraw(DirectXCommon* dxCommon) = 0;//ボス特有の描画
	virtual void specialDrawApp() = 0;//ボス特有の描画
	virtual void specialDrawEnd() = 0;//ボス特有の描画
	//パーティクル
	void BirthParticle();
	bool collidePlayer();//プレイヤーとの当たり判定
	bool collideBoss();//攻撃判定
	void ArgEffect();//エフェクトの生成
	//void Pause(const int& Timer);
protected:
	//各クラス
	std::vector<BossEffect*> bosseffects;
	unique_ptr<Player> player = nullptr;
	unique_ptr<ParticleTex> particletex = nullptr;
	//OBB
	OBB OBB1 = {};
	OBB OBB2 = {};
	//座標や回転
	const float PI = 3.14f;
	XMFLOAT3 m_OldPos = { 0,0,0 };
	XMFLOAT3 m_AfterScale{ 2.8f,2.8f,2.8f };
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_TargetPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_OBBScale = { 0.0f,0.0f,0.0f };
	//あたり範囲
	float m_HitRadius = 0.0f;
	//HP
	float m_HP = 1.0f;
	//エフェクト
	bool m_Effect = false;
	float m_Frame = 0.0f;//フレーム
	float m_RotFrame = 0.0f;//フレーム
	bool m_Active = false;//行動開始
	int m_Action = 0;//攻撃の種類
	int m_Pat = 0;//パターン
	int m_Aiming = 0;//敵追従
	int m_CoolT = 0;//クールタイム
	int m_TargetCoolT = 0;
	int m_AttackCount = 0;//攻撃までの間
	int m_MoveCount = 0;//何回行動したか
	bool m_Alive = false;//生きてますか
	bool m_BulletHit = false;//弾がヒットしたか
	bool m_Movie = false;//ムービー中かどうか
	int m_MovieTimer = 0;//ムービーの時間
	bool m_AppMove = false;//登場シーン
	bool m_EffectArgment = false;//エフェクト生成
	int m_DeathTimer = 0;//死ぬまでの時間
	int m_DeathParticleCount = 0;//パーティクルの生成までのフレーム
	
	int m_HitDir;
	//ダメージフラグ
	bool m_Damage = false;
	int m_DamageTimer = 0;

	//パーティクル関係
	int m_FoodParticleCount = 0;
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleNum = 5;
};

