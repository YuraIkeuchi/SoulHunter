#include "PlayerSkill.h"
#include "ImageManager.h"
#include "imgui.h"
#include "Collision.h"
//静的メンバ変数の実態

bool PlayerSkill::s_DushSkill = false;
bool PlayerSkill::s_LibraSkill = false;
bool PlayerSkill::s_CompassSkill = false;
bool PlayerSkill::s_HealSkill = false;

bool PlayerSkill::s_UseDush = false;
bool PlayerSkill::s_UseLibra = false;
bool PlayerSkill::s_UseCompass = false;
bool PlayerSkill::s_UseHeal = false;

//スキルが手に入ったかどうか
void PlayerSkill::Dush() {
	s_DushSkill = true;
	m_DushAlive = false;
}

void PlayerSkill::Libra() {
	s_LibraSkill = true;
	m_LibraAlive = false;
}

void PlayerSkill::Compass() {
	s_CompassSkill = true;
	m_CompassAlive = false;
}

void PlayerSkill::Heal() {
	s_HealSkill = true;
	m_HealAlive = false;
}

//スキルを使っているかどうか
void PlayerSkill::UseLibraSkill() {
	s_UseLibra = true;
}

void PlayerSkill::UseDushSkill() {
	s_UseDush = true;
}

void PlayerSkill::UseCompassSkill() {
	s_UseCompass = true;
}

void PlayerSkill::UseHealSkill() {
	s_UseHeal = true;
}

//スキルを使っていない
void PlayerSkill::ResetLibraSkill() {
	s_UseLibra = false;
}

void PlayerSkill::ResetDushSkill() {
	s_UseDush = false;
}

void PlayerSkill::ResetCompassSkill() {
	s_UseCompass = false;
}

void PlayerSkill::ResetHealSkill() {
	s_UseHeal = false;
}

void PlayerSkill::Initialize() {
}
//更新
void PlayerSkill::Update() {
}
//描画
void PlayerSkill::Draw() {
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
