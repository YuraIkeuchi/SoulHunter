#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
using namespace std;         //  名前空間指定
//攻撃エフェクト
class AttackEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	AttackEffect();

	void Initialize();//初期化
	void Update();//更新
	void Draw();//描画
	void SetEffect(const XMFLOAT3& pos,int Dir);//エフェクトの出現
	void EffectMove();//エフェクトの動き

public:
	//getter setter
	bool GetAttackAlive() { return  m_AttackAlive; }
private:
	unique_ptr<Helper> helper;
	//攻撃エフェクト
	unique_ptr<IKETexture> AttackEffecttexture;
	XMFLOAT3 m_Position = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT4 m_Color = { 0.0f,0.0f,0.0f,1.0f };//色
	XMFLOAT3 m_Scale = { 1.0f,1.0f,1.0f };//大きさ
	XMFLOAT4 m_BirthColor = { 1.0f,1.0f,1.0f,1.0f };//誕生した瞬間の色
	XMFLOAT3 m_BirthScale = { 0.5f,0.5f,0.5f };//誕生した瞬間の大きさ
	float m_AddPower = 0.0f;//加わる力
	bool m_AttackAlive = false;//描画するか
};