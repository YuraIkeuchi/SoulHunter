#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include "Helper.h"
using namespace std;         //  名前空間指定

//手紙やセーブポイントなど目立たせたい場所に出すエフェクト
class MarkEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	MarkEffect();

	void Initialize();//初期化
	void Finalize();//解放
	void Update(XMFLOAT3 StartPos);//更新
	void Draw();//描画
	void EffectMove(XMFLOAT3 StartPos);//エフェクトの動き
private:
	unique_ptr<Helper> helper;
	//テクスチャ
	unique_ptr<IKETexture> markEffect;
	//変数
	XMFLOAT3 m_Position = { 0.0f,0.0f,0.0f };//座標
	XMFLOAT3 m_Scale = { 0.0f,0.0f,0.0f };//大きさ
	XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };//色
	XMFLOAT4 m_InitColor = { 1.0f,1.0f,1.0f,0.0f };//初期化の色

	float m_Frame = 0.0f;//フレーム
	bool a = true;
};