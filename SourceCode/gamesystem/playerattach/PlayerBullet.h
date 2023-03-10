//#pragma once
//#pragma once
//#include "IKEObject3d.h"
//#include"IKEModel.h"
//#include "Block.h"
//#include "IKEFBXModel.h"
//#include "IKEFBXObject3d.h"
//#include "DirectXCommon.h"
//#include "ObjCommon.h"
//#include "ParticleTex.h"
//#include <memory>
//#include <list> // ヘッダファイルインクルード
//using namespace std;         //  名前空間指定
////プレイヤーの弾のクラス
//class PlayerBullet :
//	public ObjCommon
//{
//public:
//	void SetBlock(Block* block) { this->block.reset(block); }
//	PlayerBullet();
//public:
//
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	/// <returns>成否</returns>
//	bool Initialize() override;
//
//	void StateInitialize();
//	/// <summary>
//	/// 毎フレーム処理
//	/// </summary>
//	void Update() override;
//	//プレイヤーの挙動
//	void Draw(DirectXCommon* dxCommon);
//	//弾の移動
//	void Shot();
//
//	//ポーズのとき
//	void Pause();
//
//public:
//	bool GetAlive() { return  m_Alive; }
//
//	void SetAlive(bool Alive) { this->m_Alive = Alive; }
//
//	void SetAddSpeed(float AddSpeed) { this->m_AddSpeed = AddSpeed; }
//
//private:
//	//クラス
//	unique_ptr<Block> block = nullptr;
//	unique_ptr<ParticleTex> particletex = nullptr;
//	//変数
//	XMFLOAT3 m_OldPos = { 0.0f,0.0f,0.0f };
//	XMFLOAT2 m_Radius = { 0.5f,0.5f };
//	float m_AddSpeed = 0.0f;
//	
//	bool m_Alive = false;
//	int m_ParticleCount = 0;
//};
//
