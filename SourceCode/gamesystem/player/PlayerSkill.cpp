#include "PlayerSkill.h"
#include "imgui.h"
//静的メンバ変数の実態

bool PlayerSkill::s_DushSkill = false;
bool PlayerSkill::s_LibraSkill = false;
bool PlayerSkill::s_CompassSkill = false;
bool PlayerSkill::s_HealSkill = false;

bool PlayerSkill::s_UseDush = false;
bool PlayerSkill::s_UseLibra = false;
bool PlayerSkill::s_UseCompass = false;
bool PlayerSkill::s_UseHeal = false;

PlayerSkill* PlayerSkill::GetInstance()
{
	static PlayerSkill instance;

	return &instance;
}

//スキルのリセット
void PlayerSkill::ResetSkill() {
	s_UseLibra = false;
	s_UseDush = false;
	s_UseCompass = false;
	s_UseHeal = false;
	s_DushSkill = false;
	s_LibraSkill = false;
	s_CompassSkill = false;
	s_HealSkill = false;
}

void PlayerSkill::ImGuiDraw() {
	ImGui::Begin("skill");
	ImGui::Text("UseLibra:%d", s_UseLibra);
	ImGui::Text("UseDush:%d", s_UseDush);
	ImGui::Text("UseHeal:%d", s_UseHeal);
	ImGui::Text("UseCompass:%d", s_UseCompass);
	ImGui::Text("GetLibra:%d", s_LibraSkill);
	ImGui::Text("GetDush:%d", s_DushSkill);
	ImGui::Text("GetHeal:%d", s_HealSkill);
	ImGui::Text("GetCompass:%d", s_CompassSkill);
	ImGui::End();
}
