#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//�w�i�̒�
	BackRock();
	void Initialize() override;//������
	void SetObj() override;//�Z�b�g����obj
	void specialDraw() override;
};