#pragma once
#include "BackObjCommon.h"

class BackBox :public BackObjCommon {
public:
	//OBJ‚Ì” 
	BackBox();
	void Initialize() override;//‰Šú‰»
	void SetObj() override;//ƒZƒbƒg‚µ‚½obj
	void specialDraw() override;
};