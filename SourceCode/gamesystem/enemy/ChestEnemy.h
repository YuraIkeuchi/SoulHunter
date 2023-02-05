#pragma once
#include"InterEnemy.h"
#include "Shake.h"
using namespace std;         //  名前空間指定
//上下に動く敵
class ChestEnemy :public InterEnemy {
public:
	ChestEnemy();
	bool Initialize() override;//初期化
	void Action()override;//更新
	void Finalize() override;//開放
	void Pause()override;//ポーズのとき
	void MapDraw(XMFLOAT4 Color) override;//ミニマップのとき
	void ImGuiDraw()override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void ChestMove();
	bool ChestCollision();
	bool VanishChestEnemy();
	void DamageChestAct();//ダメージを受けた時の動き
	void TexMove();//テクスチャが動く
	bool TexCollide();//テクスチャ当たり判定
	bool PlayerCollide();//プレイヤーとの当たり判定
public:
	//gettersetter

private:
	//クラス
	unique_ptr<Shake> shake = nullptr;
	//テクスチャ
	unique_ptr<IKETexture> chestTex = nullptr;
	float m_Frame = 0.0f;
	//宝箱を開けるテキストの変数関係
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition{};
	//敵の変数
	bool m_Hit = false;
	bool m_Attack = false;
	XMFLOAT3 m_AfterPos{};

	int m_MoveNumber = 0;
	//敵の行動パターン
	enum MoveNumber {
		ShakeChest,
		SetChest,
		AttackChest,
		IntervalChest,
		ReturnChest,
	};

	int m_IntervalTimer = 0;

	//シェイク
	XMFLOAT3 m_ShakePos{};

	//色
	XMFLOAT4 m_AfterColor{};
};

