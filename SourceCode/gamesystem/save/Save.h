#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Player.h"
#include "IKESprite.h"
#include "ParticleTex.h"
#include "MarkEffect.h"
#include "VariableCommon.h" 
#include <array>  
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//セーブのクラス
class Save {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	const void Draw();
	//当たり判定
	bool Collide();
	//ステージごとの初期化
	void InitSave(int StageNumber);
	//テクスチャの動き
	void TexMove();
	//アニメーション
	void SaveAnime();
private:
	//定数
	static const int SaveSprite_Max = 4;//アニメーションの数
public:
	//getter
	const XMFLOAT3& GetPosition() { return  m_Position; }

	bool GetAlive() { return  m_Alive; }

	bool GetGameSave() { return  m_GameSave; }
	//setter
	void SetAlive(bool Alive) { this->m_Alive = Alive; }

	void SetGameSave(bool m_GameSave) { this->m_GameSave = m_GameSave; }

	void SetPosition(const XMFLOAT3& m_Position) { this->m_Position = m_Position; }
private:
	unique_ptr<ParticleTex> particletex = nullptr;
	//クラス
	unique_ptr<Player> player = nullptr;
	unique_ptr<MarkEffect> markEffect = nullptr;
	//OBJやモデルなど
	IKEModel* modelSave = nullptr;
	unique_ptr <IKEObject3d> objSave;
	//テクスチャやスプライト
	array<unique_ptr<IKESprite>, SaveSprite_Max> SaveSprite;
	//座標
	XMFLOAT3 m_Position = {0.0f,0.0f,0.0f};
	XMFLOAT3 m_TexPosition = {0.0f,0.0f,0.0f};
	//セーブポイントがあるか
	bool m_Alive = false;
	bool m_GameSave = false;//セーブされたか
	bool m_SaveText = false;//セーブ中と出すか
	bool m_HitSave = false;//セーブポイントに当たっているか
	//アニメーション関係
	int m_SaveTimer = 0;
	int m_SaveCount = 0;
	//sin波に使うもの
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//パーティクル関係
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};