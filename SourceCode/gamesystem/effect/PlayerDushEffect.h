#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
using namespace std;         //  名前空間指定
//Vectorで持たなくていいプレイヤーエフェクトのクラス
class PlayerDushEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	PlayerDushEffect();

	void Initialize();//初期化
	void Update();//更新
	const void Draw();//描画

public:

	bool GetDushAlive() { return  m_DushAlive; }

	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }

	void SetDushEffectPosition(const XMFLOAT3& DushEffectpos) { this->m_DushEffectpos = DushEffectpos; }

	//独自の関数
	//ダッシュエフェクトの位置セット
	void DushEffectSet(const XMFLOAT3& pos);

	//ダッシュエフェクトの動き
	void DushEffectMove();
private:
	
private:
	//エフェクト関係
	//ダッシュのエフェクト
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	//IKETexture* ArmPlayerEffecttexture = nullptr;
	XMFLOAT3 m_DushEffectpos = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT4 m_DushEffectcolor = { 0.0f,0.0f,0.0f,1.0f };//色
	XMFLOAT3 m_DushEffectscale = { 0.0f,0.0f,0.0f };//大きさ
	bool m_DushAlive = false;//生存
	bool m_DeleteEffect = false;
};