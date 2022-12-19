#pragma once
#include <DirectXMath.h>
#include "IKEObject3d.h"
#include "IKEModel.h"
#include "IKESprite.h"
#include "Player.h"
#include "Pause.h"
#include "PlayerEffect.h"
#include "PlayerBullet.h"
#include "IKETexture.h"
#include "ParticleTex.h"
#include "BossEffect.h"
#include "BossName.h"
#include "VariableCommon.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
#define DIRECTINPUT_VERSION 0x0800

class InterBoss {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetPlayerEffect(PlayerEffect* playereffect) { this->playereffect.reset(playereffect); }
	void SetPlayerBullet(PlayerBullet* playerbullet) { this->playerbullet.reset(playerbullet); }
	void SetPause(Pause* pause) { this->pause.reset(pause); }
	
	//gettersetter
	const XMFLOAT3& GetPosition() { return  enemyobj->GetPosition(); }
	const XMFLOAT3& GetRotation() { return enemyobj->GetRotation(); }
	bool GetEffect() { return  m_Effect; }
	bool GetAlive() { return  m_Alive; }
	const float& GetHP() { return  m_HP; }
	const int& GetDeathTimer() { return  m_DeathTimer; }

	void SetPosition(const XMFLOAT3& position) { enemyobj->SetPosition(position); }
	void SetRotation(const XMFLOAT3& rotation) { enemyobj->SetRotation(rotation); }
	void SetScale(const XMFLOAT3& scale) { enemyobj->SetScale(scale); }
	void SetEffect(bool effect) { this->m_Effect = effect; }
	void SetAlive(bool m_Alive) { this->m_Alive = m_Alive; }
	void SetMovie(bool m_Movie) { this->m_Movie = m_Movie; }
public:
	
	//初期化
	virtual void Initialize() = 0;
	//更新
	void Update();
	//描画
	void Draw();
	virtual void App() = 0;//ボス出現モーション

	virtual void Spec() = 0;//ボス特有の処理

	virtual void End() = 0;//ボス特有の処理
	virtual void specialDraw() = 0;//ボス特有の描画

	bool collidePlayer();//プレイヤーとの当たり判定
	bool collideBoss();//攻撃判定
	bool BulletCollision();//弾との当たり判定;
	bool SpecialCollide();//必殺技の当たり判定
	void ArgEffect();//エフェクトの生成
	//void Pause(const int& Timer);
protected:
	//各クラス
	std::vector<BossEffect*> bosseffects;
	unique_ptr<Player> player = nullptr;
	unique_ptr<PlayerBullet> playerbullet = nullptr;
	unique_ptr<BossName> bossname = nullptr;
	unique_ptr<ParticleTex> particletex = nullptr;
	unique_ptr<PlayerEffect> playereffect = nullptr;
	unique_ptr<Pause> pause = nullptr;
	//テクスチャやオブジェクト
	unique_ptr<IKEObject3d> enemyobj = nullptr;
	IKEModel* model = nullptr;
	
	//座標や回転
	const float PI = 3.14f;
	XMFLOAT3 m_pos = { 0,0,0 };
	XMFLOAT3 m_OldPos = { 0,0,0 };
	XMFLOAT3 m_rot = { 0,0,0 };
	XMFLOAT3 m_Scale{ 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterScale{ 2.8f,2.8f,2.8f };
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_TargetPos = { 0.0f,0.0f,0.0f };
	//あたり範囲
	float m_HitRadius = 0.0f;
	//HP
	float m_HP = 40.0f;
	//エフェクト
	bool m_Effect = false;
	float m_Frame = 0.0f;//フレーム
	bool m_Active = false;//行動開始
	int m_Action = 0;//攻撃の種類
	int m_Pat = 0;//パターン
	int m_Aiming = 0;//敵追従
	int m_CoolT = 0;//クールタイム
	int m_AttackCount = 0;//攻撃までの間
	int m_MoveCount = 0;//何回行動したか
	bool m_Alive = false;//生きてますか
	bool m_BulletHit = false;//弾がヒットしたか
	bool m_SpecialHit = false;//必殺技の当たり判定
	bool m_Movie = false;//ムービー中かどうか
	int m_MovieTimer = 0;//ムービーの時間
	bool m_AppMove = false;//登場シーン
	bool m_EffectArgment = false;//エフェクト生成
	int m_DeathTimer = 0;//死ぬまでの時間
	int m_ParticleCount = 0;//パーティクルの生成までのフレーム
	
	int m_HitDir;
};

