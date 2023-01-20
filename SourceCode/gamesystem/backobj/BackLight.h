#pragma once
#include "IKETexture.h"
#include <memory>
using namespace std;         //  名前空間指定
//背景の光テクスチャ用のクラス
class BackLight {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();//初期化
	void Update();//更新
	const void Draw();//描画

private:
	//テクスチャ
	unique_ptr<IKETexture> backlightTex = nullptr;
	//変数
	XMFLOAT3 m_BackLightPos = { 139.0f,-120.0f,200.0f };
	XMFLOAT3 m_BackLightScale = { 15.0f,70.0f,1.0f };
};