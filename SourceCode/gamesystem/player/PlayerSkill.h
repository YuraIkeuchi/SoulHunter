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
	// setter
	void SetDushSkill(bool s_DushSkill) { this->s_DushSkill = s_DushSkill; }
	void SetLibraSkill(bool s_LibraSkill) { this->s_LibraSkill = s_LibraSkill; }
	void SetCompassSkill(bool s_CompassSkill) { this->s_CompassSkill = s_CompassSkill; }
	void SetHealSkill(bool s_HealSkill) { this->s_HealSkill = s_HealSkill; }

	void ImGuiDraw();
private:
	//静的メンバ変数
	//スキルが手に入ったかどうか
	static bool s_DushSkill;
	static bool s_LibraSkill;
	static bool s_CompassSkill;
	static bool s_HealSkill;
};