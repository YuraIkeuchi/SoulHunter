#pragma once
#include "IKETexture.h"
#include <array>   
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//パーティクルタイプ
enum Type {
	NormalPart,
	UpPart,
	EndPart,
	ChestPart,
	SavePart,
	BossEndPart,
};
//テクスチャのパーティクル
class ParticleTex {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ParticleTex();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer, int ParticleType);

	//各パーティクルの種類
	void NormalParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void UpParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void EndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void ChestParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void SaveParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);

	void BossEndParticle(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void ImGuiDraw();
public:
	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetParticleType(int m_ParticleType) { this->m_ParticleType = m_ParticleType; }
	void SetParticleBreak(bool m_ParticleBreak) { this->m_ParticleBreak = m_ParticleBreak; }
	void SetParticleBillboard(bool m_ParticleBillboard) { this->m_ParticleBillboard = m_ParticleBillboard; }
	void SetStartScale(float m_StartScale) { this->m_StartScale = m_StartScale; }
	void SetAddScale(float m_AddScale) { this->m_AddScale = m_AddScale; }
private:
	//定数
	static const int ParticleTex_Max = 40;//パーティクルの数
private:
	//テクスチャ
	array<unique_ptr <IKETexture>, ParticleTex_Max> particletex;

	//変数
	array<XMFLOAT3, ParticleTex_Max> m_pos;//座標
	array<float, ParticleTex_Max> m_Angle;//角度
	array<XMFLOAT4, ParticleTex_Max> m_color;//色
	array<XMFLOAT2, ParticleTex_Max> m_speed;//移動速度
	array<XMFLOAT3, ParticleTex_Max> m_scale;//大きさ
	array<XMFLOAT3, ParticleTex_Max> m_AddPower;//加わる力
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//始まりの色

	array<bool, ParticleTex_Max> m_Alive;//生存しているか
	array<bool, ParticleTex_Max> m_End;//生存しているか
	array<bool, ParticleTex_Max> m_ScaleChange;//大きさの変更
	array<int, ParticleTex_Max> m_Number;//パーティクルの動く方向
	array<int, ParticleTex_Max> m_Timer;//パーティクルの時間
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };

	bool m_ParticleBreak = false;//パーティクルを個々にだすか
	float m_StartScale = 0.1f;//始まりの大きさ
	float m_AddScale = 0.02f;//大きさに加算する量
	int m_ParticleType = 0;//パーティクルのタイプ
	bool m_ParticleBillboard = false;//ビルボード
	
};