#pragma once
#include <DirectXMath.h>
#include "DirectXCommon.h"
using namespace std;         //  名前空間指定
//Actorクラスの既定
class BaseActor
{
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//仮想デストラクタ
	virtual ~BaseActor() = default;

	//初期化
	virtual void Initialize(DirectXCommon* dxCommon) = 0;
	//開放
	virtual void Finalize() = 0;
	//更新
	virtual void Update(DirectXCommon* dxCommon) = 0;
	//描画
	virtual void Draw(DirectXCommon* dxCommon) = 0;
public:
};