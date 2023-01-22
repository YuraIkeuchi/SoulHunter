#pragma once
#include <DirectXMath.h>
#include "IKEModel.h"
#include "IkeObject3d.h"
#include <array>   
#include <memory> 
using namespace std;         //  名前空間指定
class WallAttackEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	WallAttackEffect();

	void Initialize();
	void Finalize();
	void Update(const XMFLOAT3& pos, int HitDir);
	void Draw();
	void SetEffect(const XMFLOAT3& pos,int HitDir);
private:
	//定数
	static const int Effect_Max = 5;//エフェクトの数
public:
	//getter setter
private:
	array<unique_ptr <IKEObject3d>, Effect_Max> particleobj;
	IKEModel* model = nullptr;
	//その他変数
	//パーティクル変数
	array<XMFLOAT3, Effect_Max> m_Pos;//座標
	array<XMFLOAT4, Effect_Max> m_Color;//色
	array<XMFLOAT3, Effect_Max> m_Scale;//大きさ
	array<XMFLOAT3, Effect_Max> m_BoundPower;//加わる力
	array<float, Effect_Max> m_AddScale;
	array<bool, Effect_Max> m_ScaleChange;//大きさの変更
	array<bool, Effect_Max> m_Effect;//生存
	array<float, Effect_Max> m_Gravity;//重力
	bool m_DeleteEffect = false;//エフェクトが消えたか
};