#pragma once
#include "BackObjCommon.h"

class BackBox :public BackObjCommon {
public:
	//OBJ�̔�
	BackBox();
	void Initialize() override;//������
	void SetObj() override;//�Z�b�g����obj
	void specialDraw() override;
};