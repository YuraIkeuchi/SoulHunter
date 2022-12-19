#pragma once
#include <DirectXMath.h>
#include "IKESprite.h"
#include "IKETexture.h"
#include "Player.h"
#include "AllArray.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//Vectorで持たなくていいプレイヤーエフェクトのクラス
class PlayerEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	PlayerEffect();

	void Initialize();//初期化
	void Update();//更新
	const void Draw();//描画

public:

	bool GetDushAlive() { return  m_DushAlive; }

	const XMFLOAT3& GetSpecialPosition() { return  m_SpecialEffectpos; }

	bool GetSpecialAlive() { return  m_SpecialAlive; }

	float GetSpecialRadius() { return  m_SpecialRadius; }
	
	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }

	void SetDushEffectPosition(const XMFLOAT3& DushEffectpos) { this->m_DushEffectpos = DushEffectpos; }

	//独自の関数
	//ダッシュエフェクトの位置セット
	void DushEffectSet();
	//ダメージ時のエフェクトセット
	void DamageEffectSet();
	//ヒットエフェクト
	void SetHitEffect();
	//必殺技時のエフェクトセット
	void SpecialEffectSet();

private:
	//クラス
	unique_ptr<Player> player = nullptr;
	//エフェクト関係
	//ダッシュのエフェクト
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	//IKETexture* ArmPlayerEffecttexture = nullptr;
	XMFLOAT3 m_DushEffectpos = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT4 m_DushEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//色
	XMFLOAT3 m_DushEffectscale = { 0.0f,0.0f,0.0f };//大きさ
	bool m_DushAlive = false;//生存
	
	//ダメージ時
	array<unique_ptr<IKETexture>, DamageEffect_Max> damagetex;
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectpos;//座標
	array<XMFLOAT4, DamageEffect_Max> m_DamageEffectcolor;//色
	array<XMFLOAT3, DamageEffect_Max> m_DamageEffectscale;//大きさ
	array<XMFLOAT3, DamageEffect_Max> m_BoundPower;//加わる力
	array<bool, DamageEffect_Max> m_DamageAlive;//生存
	
	//必殺技のエフェクト
	unique_ptr<IKETexture> SpecialEffecttexture = nullptr;
	XMFLOAT3 m_SpecialEffectpos = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT4 m_SpecialEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//色
	XMFLOAT3 m_SpecialEffectscale = { 0.0f,0.0f,0.0f };//大きさ
	bool m_SpecialAlive = false;//生存
	//ヒットエフェクト
	unique_ptr<IKETexture> HitEffectTexture;
	//ヒットエフェクト変数
	XMFLOAT3 m_HitPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HitScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HitColor = { 0.0f,0.0f,0.0f,0.0f };
	bool m_HitEffect = false;
	bool m_DeleteHitEffect = false;
	//攻撃範囲
	float m_SpecialRadius = 0.0f;
};