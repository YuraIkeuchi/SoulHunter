#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//背景の柱
	BackRock();
	void Initialize() override;//初期化
	void SetObj() override;//セットしたobj
	void specialDraw() override;
};