#pragma once
#include "IKEModel.h"
#include "IKEObject3d.h"
#include <array>   
#include <memory>
using namespace std;         //  名前空間指定
class SwordParticle {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	SwordParticle();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(XMFLOAT3 StartPos, int Timer, int TargetTimer, XMMATRIX matrix);

	void NormalParticle(int Timer, int TargetTimer, XMMATRIX matrix);

	void SetParticle(int Timer, int TargetTimer, XMMATRIX matrix);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void ImGuiDraw();
	void ChangeShader(int DrawNumber);
	void SetMatrix(XMMATRIX matrix);
public:
	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetShaderChange(bool m_ShaderChange) { this->m_ShaderChange = m_ShaderChange; }
private:
	//定数
	static const int Particle_Max = 40;//パーティクルの数
private:

	IKEModel* model = nullptr;
	array<unique_ptr <IKEObject3d>, Particle_Max> object;

	array<XMFLOAT3, Particle_Max> m_pos;
	array<float, Particle_Max> m_angle;
	array<XMFLOAT2, Particle_Max> m_speed;
	array<XMFLOAT3, Particle_Max> m_scale;
	array<XMFLOAT3, Particle_Max> m_addPower;
	array<XMFLOAT3, Particle_Max> m_RandPos;
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//始まりの色
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
	bool m_ShaderChange = false;
	array<bool, Particle_Max> m_Alive;
	array<bool, Particle_Max> m_ScaleChange;
	array<float, Particle_Max> m_power;
	array<int, Particle_Max> m_Number;
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };
};