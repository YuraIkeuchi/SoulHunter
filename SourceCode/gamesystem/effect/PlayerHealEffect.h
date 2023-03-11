#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
using namespace std;         //  名前空間指定
//攻撃エフェクト
class PlayerHealEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlayerHealEffect();

	void Initialize();//初期化
	void Update();//更新
	void Draw();//描画
	void SetEffect(const XMFLOAT3& StartPos);//回復した瞬間のエフェクト
	void EffectMove();//エフェクトの動き
public:
private:
	unique_ptr<Helper> helper;
	unique_ptr<IKETexture> healeffecttex;
	//広がるエフェクト
	bool m_HealStart = false;
	bool m_DeleteEffect = false;
	XMFLOAT3 m_HealPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HealColor = { 1.0f,1.0f,1.0f,0.0f };
	enum HealEffectNumber {
		Appear,
		Disappear
	};
	HealEffectNumber m_HealEffectNumber;
};