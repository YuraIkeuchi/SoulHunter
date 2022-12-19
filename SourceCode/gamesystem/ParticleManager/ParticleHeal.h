#pragma once
#include "IKETexture.h"
#include "AllArray.h"
#include <array>   
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//回復のパーティクル
class ParticleHeal {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ParticleHeal();
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(const XMFLOAT3& StartPos, int Timer, int TargetTimer);
	void ParticleMove(const XMFLOAT3& StartPos, int Timer, int TargetTimer);//パーティクルの動き
	void HealEffect(const XMFLOAT3& StartPos);//回復した瞬間のエフェクト
	void Draw();//描画
	void ImGuiDraw();//ImGui
public:
	//gettersetter
	bool GetHeal() { return  m_Heal; }

	void SetStartColor(const XMFLOAT4& m_color) { this->m_StartColor = m_color; }
	void SetHeal(bool m_Heal) { this->m_Heal = m_Heal; }
private:
	//テクスチャ
	unique_ptr<IKETexture> healeffecttex;
	array<unique_ptr <IKETexture>, ParticleHeal_Max> particletex;
	//変数
	array<XMFLOAT3, ParticleHeal_Max> m_pos;//座標
	array<float, ParticleHeal_Max> m_Angle;//角度
	array<XMFLOAT4, ParticleHeal_Max> m_color;//色
	array<XMFLOAT2, ParticleHeal_Max> m_speed;//移動速度
	array<XMFLOAT3, ParticleHeal_Max> m_scale;//大きさ
	array<XMFLOAT3, ParticleHeal_Max> m_AddPower;//加わる力
	XMFLOAT4 m_StartColor = { 1.0f,1.0f,1.0f,1.0f };//始まりの色
	
	
	array<bool, ParticleHeal_Max> m_Alive;//生存しているか
	array<bool, ParticleHeal_Max> m_ScaleChange;//大きさの変更
	array<int, ParticleHeal_Max> m_Number;
	array<int, ParticleHeal_Max> m_Timer;
	XMFLOAT3 m_StartPos = { 0.0f,0.0f,0.0f };
	//広がるエフェクト
	bool m_Heal = false;
	bool m_HealStart = false;
	XMFLOAT3 m_HealPos = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealRot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_HealScale = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_HealColor = { 1.0f,1.0f,1.0f,0.0f };
	enum HealEffectNumber {
		Appear,
		Disappear
	};
	HealEffectNumber m_HealEffectNumber;
};