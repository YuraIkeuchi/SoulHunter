#pragma once
#include "BackObjCommon.h"

class BackBox :public BackObjCommon {
public:
	//OBJ‚Ì” 
	BackBox();
	bool Initialize() override;//‰Šú‰»
	void SetObj() override;//ƒZƒbƒg‚µ‚½obj
	void specialDraw() override;
	void Draw(DirectXCommon* dxCommon) override;//•`‰æ
};