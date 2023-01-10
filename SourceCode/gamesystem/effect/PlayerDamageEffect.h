#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//Vectorで持たなくていいプレイヤーエフェクトのクラス
class PlayerDamageEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	PlayerDamageEffect();

	void Initialize();//初期化
	void Update(const XMFLOAT3& pos, bool& Effect);//更新
	const void Draw();//描画

public:
	//ダメージ時のエフェクトセット
	void DamageEffectSet(const XMFLOAT3& pos, bool& Effect);
	//ヒットエフェクト
	void SetHitEffect(const XMFLOAT3& pos, bool& Effect);
private:
	//定数
	static const int DamageEffect_Max = 20;//エフェクトの数
private:
	//ダメージ時
	array<unique_ptr<IKETexture>, DamageEffect_Max> damagetex;
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectpos;//座標
	array<XMFLOAT4, DamageEffect_Max> m_DamageEffectcolor;//色
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectscale;//大きさ
	array<XMFLOAT3, DamageEffect_Max> m_BoundPower;//加わる力
	array<bool, DamageEffect_Max> m_DamageAlive;//生存
	//ヒットエフェクト
	unique_ptr<IKETexture> HitEffectTexture;
	//ヒットエフェクト変数
	XMFLOAT3 m_HitPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HitScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
	bool m_HitEffect = false;
	bool m_DeleteHitEffect = false;
	bool m_DeleteEffect = false;
};