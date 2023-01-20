#pragma once
#include "BackObjCommon.h"
#include "ParticleTex.h"
class BackTorch :public BackObjCommon {
public:
	//OBJの箱
	BackTorch();
	bool Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
	void BirthParticle();//パーティクル
	void Draw(DirectXCommon* dxCommon) override;//描画
private:
	//クラス
	unique_ptr<ParticleTex> particletex = nullptr;
	//パーティクル関係
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};