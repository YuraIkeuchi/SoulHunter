#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "InterEnemy.h"
#include "IKETexture.h"
#include "Player.h"
#include "Block.h"
#include "ParticleManager.h"
#include <memory> 
using namespace std;         //  名前空間指定
//プレイヤーの魂のクラス
class PlayerSoul {
public:
	void SetBlock(Block* block_) { this->block.reset(block_); }
	void SetPlayer(Player* player) { this->player.reset(player); }
	PlayerSoul();

	void Initialize();//初期化
	void Finalize();//解放
	//諸事情により敵ごとに必要になってしまった
	void Update(InterEnemy* enemy);
	void Draw();//描画
	void SetEffect(InterEnemy* enemy);
	bool Collide();//当たり判定
	void Move();//魂の動き
	void VanishSoul(InterEnemy* enemy);//魂が消える
	bool UpdateCollide();//更新範囲
	bool DrawCollide();//描画範囲
	void BirthParticle();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	void SetEffect(bool m_Effect) { this->m_Effect = m_Effect; }
	
private:
	//テクスチャ
	unique_ptr<IKETexture> soultex;
	//パーティクル
	//クラス
	unique_ptr<Player> player = nullptr;//
	unique_ptr<Block> block = nullptr;
	//変数
	XMFLOAT3 m_Position;//座標
	XMFLOAT3 m_OldPos;//位置フレームずれた座標
	XMFLOAT3 m_AfterPos = { 0.0f,0.0f,0.0f };//イージング後の座標
	XMFLOAT3 m_Scale = {0.0f,0.0f,0.0f};//大きさ
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	float m_BoundPower = 0.0f;//飛びでた瞬間に加わる力
	float m_AddPower = 0.0f;//加わる力
	XMFLOAT2 m_Radius;//マップチップ当たり判定用の大きさ
	bool m_Effect = false;//出現
	bool m_EndSoul = false;//消えたか
	bool m_Jump = false;//地面についているかどうか
	int m_Timer = 0;//時間
	int m_ParticleCount = 0;//パーティクルの出げっb間隔
	bool m_Move = false;//動くかどうか
	float m_Frame = 0.0f;//フレーム
	//unique_ptr<ParticleManager> soulparticle;
public:
	Sphere collider;
};