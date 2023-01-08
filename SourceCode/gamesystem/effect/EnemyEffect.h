#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include "VariableCommon.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class EnemyEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	EnemyEffect();

	void Initialize();
	void Finalize();
	void Update(const XMFLOAT3& pos, bool& Effect);
	void Draw();
	void SetEffect(const XMFLOAT3& pos, bool& Effect);
	void SetHitEffect(const XMFLOAT3& pos, bool& Effect);
private:
	//定数
	static const int Effect_Max = 20;//エフェクトの数
public:
	//getter setter
private:
	//テクスチャ
	array<unique_ptr<IKETexture>, Effect_Max> ParticleEffect;
	unique_ptr<IKETexture> HitEffectTexture;
	//その他変数
	//パーティクル変数
	array<XMFLOAT3, Effect_Max> m_Pos;//座標
	array<XMFLOAT4, Effect_Max> m_Color;//色
	array<XMFLOAT3, Effect_Max> m_Scale;//大きさ
	array<XMFLOAT3, Effect_Max> m_BoundPower;//加わる力
	array<float, Effect_Max> m_AddScale;
	array<bool, Effect_Max> m_ScaleChange;//大きさの変更
	array<bool, Effect_Max> m_Effect;//生存
	bool m_DeleteEffect = false;//エフェクトが消えたか
	//ヒットエフェクト変数
	XMFLOAT3 m_HitPos = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT3 m_HitScale = { 0.0f,0.0f,0.0f };//大きさ
	XMFLOAT4 m_HitColor = { 0.0f,0.0f,0.0f,0.0f };//色
	bool m_HitEffect = false;//生存
	bool m_DeleteHitEffect = false;//消えたかどうか
};