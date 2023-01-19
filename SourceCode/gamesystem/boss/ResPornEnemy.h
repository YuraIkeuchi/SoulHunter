#pragma once
#include "InterBoss.h"
//ボスステージのときにザコ敵がたまに出現する
class ResPornEnemy
{
public:
	void Initialize();
	void Update(InterBoss* boss = nullptr);
	void Finalize();
	const void Draw();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter setter
	bool GetEnemyArgment() { return  m_EnemyArgment; }

	int GetResPornType() { return  m_ResPornType; }

	const XMFLOAT3& GetResPornPosition() { return  m_ResPornPos; }

	void SetEnemyArgment(bool m_EnemyArgment) { this->m_EnemyArgment = m_EnemyArgment; }
private:
	//クラス
	//unique_ptr<ParticleTex> particletex = nullptr;
	//その他変数
	XMFLOAT3 m_ResPornPos = { 0.0f,0.0f,0.0f };//座標
	int m_ResPornTimer = 0;//生成までの時間
	bool m_EnemyArgment = false;//生成されるかどうか
	int m_ParticleCount = 0;//パーティクルの生成までのフレーム
	bool m_ResPornParticle = false;//パーティクルが出るかどうか
	int m_ResPornType = 0;//敵の種類
	//リスポーンスル敵の種類
	enum ResPornEnemyType {
		Normal,
		Wing,
		Bird,
	};
};