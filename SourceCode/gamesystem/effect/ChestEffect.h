#pragma once
#include "IKESprite.h"
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

//チェスト開けた時エフェクト出ます
class ChestEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ChestEffect();

	void Initialize();//初期化
	void Finalize();//解放
	void Update(XMFLOAT3 StartPos,XMFLOAT3 TargetPos,int ChestState);//更新
	void Draw();//描画
	void EffectMove(XMFLOAT3 StartPos, XMFLOAT3 TargetPos, int ChestState);//エフェクトの動き
private:
	//定数
	static const int ChestEffect_Max = 10;//パーティクルの数
private:
	//テクスチャ
	array<unique_ptr<IKETexture>, ChestEffect_Max> chesteffect;
	//変数
	array<bool, ChestEffect_Max> m_Alive;//生存フラグ
	array<bool, ChestEffect_Max> m_StartEffect;//始まった瞬間
	array<XMFLOAT3,ChestEffect_Max> m_pos;//座標
	array<XMFLOAT3, ChestEffect_Max> m_scale;//大きさ
	array<XMFLOAT4, ChestEffect_Max> m_color;//色
	array<XMFLOAT3, ChestEffect_Max> m_AfterPos;//イージングの後のポジション
	array<float, ChestEffect_Max> m_Angle;//飛ぶ方向
	array<XMFLOAT2, ChestEffect_Max> m_speed;//速さ
	array<float, ChestEffect_Max> m_Frame;//フレーム数
	array<int, ChestEffect_Max> m_TargetTimer;//動き始めるまでの時間
	array<int, ChestEffect_Max> m_MoveNumber;//動き
	enum MoveNumber {
		Wide,
		TargetPlayer,
	};
};