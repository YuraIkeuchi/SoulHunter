#pragma once
#include"InterEnemy.h"
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
	void FollowMove();
	bool FollowCollision();
	bool VanishChestEnemy();
	void TexMove();//テクスチャが動く
	bool TexCollide();//テクスチャ当たり判定
public:
	//gettersetter

private:
	//テクスチャ
	unique_ptr<IKETexture> chestTex = nullptr;
	bool m_Follow = false;
	int m_FollowTimer = 0;
	//回転のための変数
	XMFLOAT3 m_AfterRot = { 0.0f,0.0f,0.0f };
	float m_Frame = 0.0f;

	//追従関係
	int m_TargetTimer = 0;
	XMFLOAT2 m_FollowVel{};
	XMFLOAT2 m_Rebound{};
	XMFLOAT2 m_Distance{};
	XMFLOAT3 m_TargetPos{};
	//宝箱を開けるテキストの変数関係
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition{};
	bool m_Hit = false;
};

