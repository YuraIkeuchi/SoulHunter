#pragma once
#include "BackObjCommon.h"
#include "ParticleManager.h"
class BackTorch :public BackObjCommon {
public:
	//OBJ�̔�
	BackTorch();
	bool Initialize() override;//������
	void SetObj() override;//�Z�b�g����obj
	void specialDraw() override;
	void BirthParticle();//�p�[�e�B�N��
	void Draw(DirectXCommon* dxCommon) override;//�`��
private:
	//�N���X
	unique_ptr<ParticleManager> fire;
	//�p�[�e�B�N���֌W
	XMFLOAT3 m_ParticlePos = { 0.0f,0.0f,0.0f };
	int m_ParticleCount = 0;
};