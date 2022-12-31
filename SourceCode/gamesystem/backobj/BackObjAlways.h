#pragma once
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "VariableCommon.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//背景の岩など共通背景のクラス
class BackObjAlways {
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
	void InitRock(int StageNumber);//ステージごとの配置
private:
	//定数
	static const int BackRock_Max = 11;//OBJの数
private:
	//OBJ
	IKEModel* modelskydome = nullptr;
	unique_ptr <IKEObject3d> objskydome;
	IKEModel* modelground = nullptr;
	unique_ptr <IKEObject3d> objground[BackRock_Max];
	
};