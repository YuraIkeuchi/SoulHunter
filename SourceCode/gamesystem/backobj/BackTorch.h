#pragma once
#include "BackObjCommon.h"
#include "ParticleTex.h"
class BackTorch :public BackObjCommon {
public:
	//OBJ�̔�
	BackTorch();
	void Initialize() override;//������
	void SetObj() override;//�Z�b�g����obj
	void specialDraw() override;
private:
	//�N���X
	//unique_ptr<ParticleTex> particletex = nullptr;
	//�p�[�e�B�N���֌W
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};