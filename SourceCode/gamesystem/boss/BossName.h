#pragma once
#include"IKESprite.h"
#include "AllArray.h"
#include "VariableCommon.h" 
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class BossName {
public:
	BossName();
	//更新
	void Update();
	//描画
	const void Draw();
	//徐々に文字が出てくる
	void AddColor();
	//徐々に文字が消える
	void SubColor();

	//setter
	void SetAddStartChange(bool m_AddStartChange) { this->m_AddStartChange = m_AddStartChange; }
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
	
private:
	//スプライト
	unique_ptr<IKESprite> bossname = nullptr;

	//変数
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,0.0f };//色
	XMFLOAT2 m_pos = { 640.0f,360.0f, };//座標
	bool m_AddStartChange = false;//色の加算フラグ
	bool m_DrawName = true;//描画するかどうか
	int m_AlphaNumber = 0;//透過度が減るか増えるか
	enum Alpha {
		Add,
		Sub,
	};

	//マジックナンバー解消のための変数
	const float m_ChangeTexFrame = 0.01f;//テキストの透過度
};

