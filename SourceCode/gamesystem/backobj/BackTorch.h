#pragma once
#include "BackObjCommon.h"
class BackTorch :public BackObjCommon {
public:
	//OBJの箱
	BackTorch();
	bool Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
	void BirthParticle();//パーティクル
	void Draw(DirectXCommon* dxCommon) override;//描画
	void ParticleCheck(int StageNumber)override;
private:
	//パーティクル関係
	XMFLOAT3 m_ParticlePos = {};
	int m_ParticleCount = 0;
	bool m_Particle = false;
};