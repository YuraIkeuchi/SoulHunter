#pragma once
#include "DirectXCommon.h"
#include "IKETexture.h"

using namespace std;         //  名前空間指定
//プレイヤーの弾のクラス
class FireBall
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	FireBall();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	//プレイヤーの挙動
	void Draw(DirectXCommon* dxCommon);
	//弾の移動
	void Shot();

	//ポーズのとき
	void Pause();

	bool Collide(XMFLOAT3 pos);

public:
	//gettersetter
	bool GetAlive() { return  m_Alive; }

	void SetAlive(bool Alive) { this->m_Alive = Alive; }

	void SetPosition(const XMFLOAT3& position) { m_Position = position; }
	void SetAddSpeed(float AddSpeed) { this->m_AddSpeed = AddSpeed; }
	void SetAddPowerY(float AddPowerY) { this->m_AddPowerY = AddPowerY; }

private:
	//テクスチャ
	unique_ptr<IKETexture> firetex;
	XMFLOAT3 m_Position = {0.0f,0.0f,0.0f};
	XMFLOAT3 m_Rotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_Scale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_Color = { 0.0f,0.0f,0.0f,0.0f };
	//変数
	XMFLOAT3 m_OldPos = { 0.0f,0.0f,0.0f };
	XMFLOAT2 m_Radius = { 0.5f,0.5f };
	float m_AddSpeed = 0.0f;
	float m_AddPowerY = 0.0f;
	bool m_Alive = false;
	int m_ParticleCount = 0;
};

