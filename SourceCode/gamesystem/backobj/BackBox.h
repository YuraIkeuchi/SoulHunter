#pragma once
#include "BackObjCommon.h"

class BackBox :public BackObjCommon {
public:
	//OBJの箱
	BackBox();
	void Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
};