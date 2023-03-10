#pragma once
#include "BackObjCommon.h"

class BackBox :public BackObjCommon {
public:
	//OBJの箱
	BackBox();
	bool Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
	void Draw(DirectXCommon* dxCommon) override;//描画
	void ParticleCheck(int StageNumber)override;
};