#pragma once
#include <DirectXMath.h>
#include "GamePlayer.h"
#include "ObjCommon.h"

//背景に置く
//基盤クラス
class BackObjCommon :
	public ObjCommon {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
protected:
	//クラス
	unique_ptr<GamePlayer> player = nullptr;
	
	enum ObjType {
		Piller,
		Rock,
		Wall
	};
public:
	virtual ~BackObjCommon() = default;
	//初期化
	virtual bool Initialize()override;
	//更新
	void Update();
	//描画
	virtual void Draw(DirectXCommon* dxCommon)override;

	virtual void SetObj() = 0;//配置
	virtual void specialDraw() = 0;//その他の描画

	virtual void ParticleCheck(int StageNumber) = 0;

	bool UpdateCollide();//更新範囲

	bool DrawCollide();//描画範囲
};