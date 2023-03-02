#pragma once
#include "GamePlayer.h"
#include "EnemyEffect.h"
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include "CollisionPrimitive.h"
#include "IKESprite.h"

//敵基底
class InterEnemy :
public ObjCommon{
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	/// getter
	bool GetLock() { return  m_Lock; }

	bool GetAlive() { return  m_Alive; }

	int GetHP() { return  m_HP; }

	float GetAngle() { return  m_Angle; }

	bool GetEffect() { return  m_Effect; }

	bool GetSoul() { return  m_Soul; }

	const XMFLOAT3& GetStartPos() { return  m_StartPos; }

	float GetThornPos() { return  m_ThornSetPos; }
	/// setter
	void SetEffect(const bool effect) { this->m_Effect = effect; }

	void SetSoul(const bool soul) { this->m_Soul = soul; }

	void SetAngle(const float angle) { this->m_Angle = angle; }

	void SetStartPos(const XMFLOAT3 m_StartPos) { this->m_StartPos = m_StartPos; }

	void SetThornPos(const float m_thornPos) { this->m_ThornSetPos = m_thornPos; }

	//bool Collision(XMFLOAT3 position, float radius);
	
protected:
	//クラス
	unique_ptr<GamePlayer> player = nullptr;
	std::vector<EnemyEffect*> enemyeffects;
	
	//スプライト
	unique_ptr<IKESprite> MiniEnemySprite;
	OBB OBB1 = {};
	OBB OBB2 = {};
	//座標やスケールなど
	XMFLOAT3 fbxscale = { 0.03f,0.03f,0.03f };
	XMFLOAT3 m_HitScale = {};
	XMFLOAT3 m_BoundPower = {};
	XMFLOAT3 m_OldPos = {};
	XMFLOAT3 m_StartPos = {};
	//生存
	bool m_Alive = true;
	int m_DeathTimer = 0;
	//HP
	int m_HP = 3;
	//ロックオン
	bool m_Lock = false;
	//距離
	float m_DistanceY = 0.0f;
	//エフェクト
	bool m_Effect = false;
	bool m_Soul = false;
	bool m_EffectArgment = false;
	int m_SoulCount = 0;
	//棘の的に使う
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//普通の敵関係
	//中心点からの大きさ
	XMFLOAT2 m_Radius;
	//ジャンプしたかどうか
	bool m_Jump = false;
	//上昇度
	float m_AddPower = 0.0f;
	//空中フラグ
	bool m_Air = false;
	//重力加速度
	float m_Gravity = 0.02f;;
	//移動速度
	float m_Speed;
	//攻撃食らったときの吹っ飛び
	//移動するかどうか
	bool m_SetMove;
	//ヒットした方向
	int m_HitDir;
	//移動時間
	int m_MoveTimer;
	//移動してない間のインターバル
	int m_NotMoveTimer;
	//地面にいるかどうか
	bool m_OnGround;
	//突進攻撃のロックオンするタイミングのタイマー
	int m_TargetTimer;
	//敵がどっちの壁にあたったか
	enum TouchWall {
		RightTouch,
		LeftTouch,
		DownWall,
	};
	int m_TouchWall;
	
	//パーティクル関係
	int m_FootParticleCount = 0;
	int m_DeathParticleCount = 0;
	//敵の種類(当たり判定などに用いる)
	int m_EnemyType = 0;
	bool m_BulletHit = 0;
	enum EnemyType {
		Normal,
		Thorn,
		Wing,
		Bird,
		FollowType,
		ChestType
	};
	//アニメーション
	bool m_AnimationStop = false;
	//ディゾルブ
	bool m_Disolve = false;
	//死んだときのモーション
	bool m_DeathMotion = false;
	//ジャンプ時のエフェクト発生条件
	bool m_BirdEffectArgment = false;
	//ダメージフラグ
	bool m_Damage = false;
	int m_DamageTimer = 0;
	//敵の座標(ミニマップ)
	XMFLOAT2 m_EnemyPosition = {};
	//棘の敵の必要変数
	float m_ThornSetPos = 0.0f;
	//アニメーションのスピード
	int m_AnimeTimer = 1;
	
public:
	virtual ~InterEnemy() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual bool Initialize()override;
	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();

	virtual void Action() = 0;//敵の行動

	/// <summary>
	/// ポーズのとき
	/// </summary>
	virtual void Pause() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(DirectXCommon* dxCommon)override;

	virtual void ImGuiDraw() = 0;

	virtual void MapDraw(XMFLOAT4 Color) = 0;


	bool Collision();//普通の当たり判定

	bool PlayerCollide();//プレイヤーがダメージを食らう当たり判定

	void DamageAct();//ダメージを受けた時の動き

	bool LockOn();//ロックオン

	bool UpdateCollide();//更新範囲

	bool DrawCollide();//描画範囲

	//足元にパーティクル
	void BirthParticle();

	//死んだ時
	void DeathBirthParticle();

	bool VanishEnemy();//敵が消える処理

	void ArgEffect();//エフェクト生成

	void ArgSoul();//エフェクト生成

	//ミニマップに敵を表示
	void MapEnemy();
};