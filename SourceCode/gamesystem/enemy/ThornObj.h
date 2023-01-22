#pragma once
#include "Player.h"
#include "ObjCommon.h"
#include "DirectXCommon.h"
#include "ThornParticle.h"
#include <memory>
using namespace std;         //  名前空間指定
//棘の棒
class ThornObj :
public ObjCommon{
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	bool Initialize() override;
	void Update() override;
	//それぞれの方向の動き
	void UpMove();
	void DownMove();
	void RightMove();
	void LeftMove();
	void Pause();
	void Finalize();
	bool Collide();//当たり判定
	bool UpdateCollide();//更新範囲
	bool DrawCollide();//描画範囲
	void Draw(DirectXCommon* dxCommon) override;;
public:
	const XMFLOAT3& GetThornPos() { return  m_ThornSetPos; }
	int GetDir() { return  m_Dir; }
	int GetTargetTimer() { return  m_TargetTimer; }

	void SetThornObjPos(const XMFLOAT3 m_ThornSetPos) { this->m_ThornSetPos = m_ThornSetPos; }
	void SetDir(const int Dir) { this->m_Dir = Dir; }
	void SetTargetTimer(const int m_TargetTImer) { this->m_TargetTimer = m_TargetTImer; }
private:
	//クラス
	unique_ptr<ThornParticle> thornparticle;
	unique_ptr<Player> player = nullptr;
	XMFLOAT3 m_Afterpos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HitArea = { 5.0f,20.0f,5.0f };
	XMFLOAT3 StartPos = {0.0f,0.0f,0.0f};
	float m_Frame = 0.0f;
	bool m_Active = false;//行動開始
	int m_Pat = 0;//パターン
	int m_CoolT = 0;//クールタイム
	//動いてない時間
	int m_AttackTimer = 0;
	//実際に動くまでの時間
	int m_TargetTimer = 0;
	int m_MoveTImer = 0;
	//csvで読み込む座標
	XMFLOAT3 m_ThornSetPos;
	//パーティクル関係
	XMFLOAT3 m_SmokeParticlePos;
	int m_SmokeParticleCount = 0;
	XMFLOAT3 m_RockParticlePos;
	float m_AfterRotetion = 0.0f;
	int m_RockParticleCount = 0;
	//どの攻撃をするか
	enum ActionType {
		Stop,
		Set,
		Attack,
		Return,
	};
	//方向
	int m_Dir = 0;
	enum Dir {
		Up,
		Down,
		Right,
		Left
	};
};