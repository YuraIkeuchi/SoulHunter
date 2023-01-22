#pragma once
#include "IKETexture.h"
#include "IKEModel.h"
#include "IkeObject3d.h"
#include <array>   
#include <memory>
using namespace std;         //  名前空間指定
//棘のOBJのパーティクル
class BossEndParticle {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	BossEndParticle();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void ObjUpdate(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void DownRockParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void ImGuiDraw();
public:
	//gettersetter
private:
	//定数
	static const int BossEndParticle_Max = 40;//パーティクルの数
private:
	array<unique_ptr <IKEObject3d>, BossEndParticle_Max> particleobj;
	IKEModel* model = nullptr;
	//岩の方
	array<XMFLOAT3, BossEndParticle_Max> m_RockPos;
	array<XMFLOAT3, BossEndParticle_Max> m_Rockscale;
	array<XMFLOAT3, BossEndParticle_Max> m_RockRandPos;
	array<XMFLOAT3, BossEndParticle_Max> m_RockAddPower;
	array<float, BossEndParticle_Max> m_Gravity;
	array<bool, BossEndParticle_Max> m_RockAlive;
	enum Dir {
		Up,
		Down,
		Right,
		Left
	};


};