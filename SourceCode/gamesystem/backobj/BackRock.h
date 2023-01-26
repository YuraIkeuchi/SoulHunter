#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//OBJ‚Ì” 
	BackRock();
	bool Initialize() override;//‰Šú‰»
	void SetObj() override;//ƒZƒbƒg‚µ‚½obj
	void specialDraw() override;
	void Draw(DirectXCommon* dxCommon) override;//•`‰æ
	void ParticleCheck(int StageNumber)override;
};