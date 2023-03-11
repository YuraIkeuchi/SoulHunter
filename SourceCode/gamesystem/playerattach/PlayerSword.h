#pragma once
#include "ObjCommon.h"
#include "SwordParticle.h"
#include "Helper.h"
//���̃N���X
class PlayerSword : public
	ObjCommon {
public:
	static PlayerSword* GetInstance();

	//������
	bool Initialize() override;
	//�X�V
	void Update()override;
	//�`��
	void Draw(DirectXCommon* dxCommon)override;
	void ImGuiDraw();
	//���̍X�V
	void SwordUpdate();
	//�p�[�e�B�N���̍X�V
	void ParticleUpdate();
	//�p�[�e�B�N���̕`��
	void ParticleDraw();
	//���̏o��
	void SwordBirth();
	//���̏I��
	void SwordFinish();
public:
	//gettersetter
	XMMATRIX GetSwordMatrot() { return m_SwordMatRot; }

	void SetHandMat(XMMATRIX HandMat) { this->m_HandMat = HandMat; }

	void SetSwordParticleNum(int SwordParticleNum) { this->m_SwordParticleNum = SwordParticleNum; }
private:
	unique_ptr<Helper> helper;
	//�p�[�e�B�N��
	unique_ptr<SwordParticle> swordparticle = nullptr;

	//���̃p�[�e�B�N��
	int m_SwordParticleCount = 0;
	XMFLOAT3 m_SwordParticlePos = { 0.0f,0.0f,0.0f };

	float m_SwordFrame = 0.0f;
	bool m_SwordEase = false;
	int m_SwordType = 0;
	int m_SwordParticleNum = 0;
	float m_SwordAfterAlpha = 0.0f;
	XMMATRIX m_SwordMatRot;
	XMMATRIX m_HandMat;
	enum SwordType {
		NoSword,
		ArgSword,
		DeleteSword,
	};

};