#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//”wŒi‚Ì’Œ
	BackRock();
	void Initialize() override;//‰Šú‰»
	void SetObj() override;//ƒZƒbƒg‚µ‚½obj
	void specialDraw() override;
};