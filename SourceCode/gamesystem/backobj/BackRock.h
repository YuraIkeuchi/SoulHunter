#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//OBJの箱
	BackRock();
	bool Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void ParticleCheck(int StageNumber)override;
};