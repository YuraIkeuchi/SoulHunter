#pragma once
#include "BackObjCommon.h"

class BackRock :public BackObjCommon {
public:
	//OBJ�̔�
	BackRock();
	bool Initialize() override;//������
	void SetObj() override;//�Z�b�g����obj
	void specialDraw() override;
	void Draw(DirectXCommon* dxCommon) override;//�`��
	void ParticleCheck(int StageNumber)override;
};