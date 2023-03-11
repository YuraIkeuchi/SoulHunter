#pragma once
#include "ObjCommon.h"
#include "SwordParticle.h"
#include "Helper.h"
//剣のクラス
class PlayerSword : public
	ObjCommon {
public:
	static PlayerSword* GetInstance();

	//初期化
	bool Initialize() override;
	//更新
	void Update()override;
	//描画
	void Draw(DirectXCommon* dxCommon)override;
	void ImGuiDraw();
	//剣の更新
	void SwordUpdate();
	//パーティクルの更新
	void ParticleUpdate();
	//パーティクルの描画
	void ParticleDraw();
	//剣の出現
	void SwordBirth();
	//剣の終了
	void SwordFinish();
public:
	//gettersetter
	XMMATRIX GetSwordMatrot() { return m_SwordMatRot; }

	void SetHandMat(XMMATRIX HandMat) { this->m_HandMat = HandMat; }

	void SetSwordParticleNum(int SwordParticleNum) { this->m_SwordParticleNum = SwordParticleNum; }
private:
	unique_ptr<Helper> helper;
	//パーティクル
	unique_ptr<SwordParticle> swordparticle = nullptr;

	//剣のパーティクル
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