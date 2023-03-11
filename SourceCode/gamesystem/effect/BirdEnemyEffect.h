#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include "Helper.h"
using namespace std;         //  名前空間指定
//ジャンプしたときのエフェクト
class BirdEnemyEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	BirdEnemyEffect();

	void Initialize();
	void Finalize();
	//諸事情により敵ごとに必要になってしまった
	void Update(const XMFLOAT3& pos);
	void Draw();
	void SetEffect(const XMFLOAT3& pos);
private:
	//定数
	static const int JumpEffect_Max = 5;//エフェクトの数

public:
	//getter setter
private:
	unique_ptr<Helper> helper;
	//テクスチャ
	array<unique_ptr<IKETexture>, JumpEffect_Max> JumpDamageEffect;

	//その他変数
	array<XMFLOAT3, JumpEffect_Max> m_Position;//座標
	array<XMFLOAT3, JumpEffect_Max> m_Rotation;//回転
	array<XMFLOAT3, JumpEffect_Max> m_Scale;//大きさ
	array<float, JumpEffect_Max> m_Gravity;//重力
	array<float, JumpEffect_Max> m_AddRot;//加わる回転力
	array<XMFLOAT3, JumpEffect_Max> m_AddPower;//落下速度
	array<bool, JumpEffect_Max> m_Effect;//発生フラグ
	array<bool, JumpEffect_Max> m_Birth;//始まった瞬間
	array<int, JumpEffect_Max> m_Timer;//時間
	array<int, JumpEffect_Max> m_EffectNumber;//エフェクトに加わる力の種類

	//エフェクトに力が加わる方向
	enum EffectNumber {
		No,
		Birth,
		Fall
	};
};