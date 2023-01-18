#pragma once
#include "BackObjCommon.h"
#include "ParticleTex.h"
class BackTorch :public BackObjCommon {
public:
	//OBJの箱
	BackTorch();
	void Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
private:
	//クラス
	//unique_ptr<ParticleTex> particletex = nullptr;
	//パーティクル関係
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};