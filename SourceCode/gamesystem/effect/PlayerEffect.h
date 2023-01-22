#pragma once
#include <DirectXMath.h>
#include <memory> 
#include "AttackEffect.h"
#include "WallAttackEffect.h"
#include "PlayerDamageEffect.h"
#include "PlayerDushEffect.h"
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//攻撃エフェクト
class PlayerEffect {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlayerEffect();
	//エフェクトの生成
	void CreateEffect(const std::string& newname, XMFLOAT3 pos, int dir);
	void Initialize();//初期化
	void Update();//更新
	void Draw();//描画
	
public:
private:
	vector<AttackEffect*> attackeffects;
	vector<WallAttackEffect*>walleffects;
	vector<PlayerDushEffect*> dusheffects;
	vector<PlayerDamageEffect*> damageeffects;
};