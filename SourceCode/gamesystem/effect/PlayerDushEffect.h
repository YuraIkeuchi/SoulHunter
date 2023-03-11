#pragma once
#include <DirectXMath.h>
#include "IKETexture.h"
#include <memory> 
#include "Helper.h"
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
	//独自の関数
	//ダッシュエフェクトの位置セット
	void DushEffectSet(const XMFLOAT3& pos);

	//ダッシュエフェクトの動き
	void DushEffectMove();
private:
	
private:
	unique_ptr<Helper> helper;
	//エフェクト関係
	//ダッシュのエフェクト
	unique_ptr<IKETexture> DushEffecttexture = nullptr;
	XMFLOAT3 m_Position = {};//座標
	XMFLOAT3 m_Scale = {};//大きさ
	bool m_DushAlive = false;//生存
	bool m_DeleteEffect = false;
};