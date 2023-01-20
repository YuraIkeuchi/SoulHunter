#pragma once
#include "Player.h"
#include "IKETexture.h"
//プレイヤーのスキルのクラス
class PlayerSkill {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	
	//スキルをゲットしたかどうか
	void Dush();
	void Libra();
	void Compass();
	void Heal();
	void ResetSkill();
	//スキル使用中かどうか
	void UseLibraSkill();
	void UseDushSkill();
	void UseCompassSkill();
	void UseHealSkill();
	//スキルのリセット
	void ResetLibraSkill();
	void ResetCompassSkill();
	void ResetDushSkill();
	void ResetHealSkill();
	//getter
	bool GetDushSkill() { return s_DushSkill; }
	bool GetLibraSkill() { return s_LibraSkill; }
	bool GetCompassSkill() { return s_CompassSkill; }
	bool GetHealSkill() { return s_HealSkill; }
	bool GetUseDush() { return s_UseDush; }
	bool GetUseLibra() { return s_UseLibra; }
	bool GetUseCompass() { return s_UseCompass; }
	bool GetUseHeal() { return s_UseHeal; }
	// setter
	void SetDushAlive(bool DushAlive) { this->m_DushAlive = DushAlive; }
	void SetLibraAlive(bool LibraAlive) { this->m_LibraAlive = LibraAlive; }
	void SetCompassAlive(bool CompassAlive) { this->m_CompassAlive = CompassAlive; }
	void SetHealAlive(bool HealAlive) { this->m_HealAlive = HealAlive; }
	void SetDushSkill(bool s_DushSkill) { this->s_DushSkill = s_DushSkill; }
	void SetLibraSkill(bool s_LibraSkill) { this->s_LibraSkill = s_LibraSkill; }
	void SetCompassSkill(bool s_CompassSkill) { this->s_CompassSkill = s_CompassSkill; }
	void SetHealSkill(bool s_HealSkill) { this->s_HealSkill = s_HealSkill; }
	void SetUseDush(bool UseDush) { this->s_UseDush = UseDush; }
	void SetUseLibra(bool UseLibra) { this->s_UseLibra = UseLibra; }
	void SetUseCompass(bool UseCompass) { this->s_UseCompass = UseCompass; }
	void SetUseHeal(bool UseHeal) { this->s_UseHeal = UseHeal; }

private:
	//静的メンバ変数
	//スキルが手に入ったかどうか
	static bool s_DushSkill;
	static bool s_LibraSkill;
	static bool s_CompassSkill;
	static bool s_HealSkill;
	//スキルを使っているかどうか
	static bool s_UseLibra;
	static bool s_UseDush;
	static bool s_UseCompass;
	static bool s_UseHeal;
private:
	Player* player = nullptr;
	//スキルそのステージに落ちているか
	bool m_DushAlive = false;
	bool m_LibraAlive = false;
	bool m_CompassAlive = false;
	bool m_HealAlive = false;
	//各スキルの座標
	XMFLOAT3 m_DushPos = { 0.0f,0.0,0.0f };
	XMFLOAT3 m_LibraPos = { 0.0f,0.0,0.0f };
	XMFLOAT3 m_HealPos = { 0.0f,0.0,0.0f };
	XMFLOAT3 m_CompassPos = { 0.0f,0.0,0.0f };
};