#pragma once
#include "IKETexture.h"
#include "IKEModel.h"
#include "IkeObject3d.h"
#include <array>   
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//棘のOBJのパーティクル
class ThornParticle {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ThornParticle();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void TexUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ThornDir);
	void ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ThornDir);
	//各方向のパーティクル
	void UpSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void DownSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void RightSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void LeftSmokeParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void UpRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void DownRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void RightRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void LeftRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void ImGuiDraw();
private:
	//定数
	static const int ThornParticleTex_Max = 15;//パーティクルの数
	static const int ThornParticleObj_Max = 15;//パーティクルの数
public:
	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
private:
	array<unique_ptr <IKEObject3d>, ThornParticleObj_Max> particleobj;
	IKEModel* model = nullptr;
	//煙の方
	array<unique_ptr <IKETexture>, ThornParticleTex_Max> particletex;
	array<XMFLOAT3, ThornParticleTex_Max> m_SmokePos;
	array<XMFLOAT3, ThornParticleTex_Max> m_SmokeRandPos;
	array<float, ThornParticleTex_Max> m_Angle;
	array<XMFLOAT4, ThornParticleTex_Max> m_color;
	array<XMFLOAT2, ThornParticleTex_Max> m_speed;
	array<XMFLOAT3, ThornParticleTex_Max> m_scale;
	array<XMFLOAT3, ThornParticleTex_Max> m_SmokeAddPower;
	array<bool, ThornParticleTex_Max> m_ScaleChange;
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };
	array<bool, ThornParticleTex_Max> m_SmokeAlive;
	//岩の方
	array<XMFLOAT3, ThornParticleObj_Max> m_RockPos;
	array<XMFLOAT3, ThornParticleObj_Max> m_Rockscale;
	array<XMFLOAT3, ThornParticleObj_Max> m_RockRandPos;
	array<XMFLOAT3, ThornParticleObj_Max> m_RockAddPower;
	array<float, ThornParticleObj_Max> m_Gravity;
	array<bool, ThornParticleObj_Max> m_RockAlive;
	enum Dir {
		Up,
		Down,
		Right,
		Left
	};
};