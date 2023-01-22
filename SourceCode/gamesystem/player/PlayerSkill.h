#pragma once

//プレイヤーのスキルのクラス
class PlayerSkill {
public:
	static PlayerSkill* GetInstance();
	//スキルをゲットしたかどうか
	void ResetSkill();
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
	void SetDushSkill(bool s_DushSkill) { this->s_DushSkill = s_DushSkill; }
	void SetLibraSkill(bool s_LibraSkill) { this->s_LibraSkill = s_LibraSkill; }
	void SetCompassSkill(bool s_CompassSkill) { this->s_CompassSkill = s_CompassSkill; }
	void SetHealSkill(bool s_HealSkill) { this->s_HealSkill = s_HealSkill; }
	void SetUseDush(bool UseDush) { this->s_UseDush = UseDush; }
	void SetUseLibra(bool UseLibra) { this->s_UseLibra = UseLibra; }
	void SetUseCompass(bool UseCompass) { this->s_UseCompass = UseCompass; }
	void SetUseHeal(bool UseHeal) { this->s_UseHeal = UseHeal; }

	void ImGuiDraw();
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
};