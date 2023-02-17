#include "PlayerSkill.h"
#include "imgui.h"
//�ÓI�����o�ϐ��̎���

bool PlayerSkill::s_DushSkill = false;
bool PlayerSkill::s_LibraSkill = false;
bool PlayerSkill::s_CompassSkill = false;
bool PlayerSkill::s_HealSkill = false;

PlayerSkill* PlayerSkill::GetInstance()
{
	static PlayerSkill instance;

	return &instance;
}

//�X�L���̃��Z�b�g
void PlayerSkill::ResetSkill() {
	s_DushSkill = false;
	s_LibraSkill = false;
	s_CompassSkill = false;
	s_HealSkill = false;
}

//�X�L���S�擾
void PlayerSkill::AllGetSkill() {
	s_DushSkill = true;
	s_LibraSkill = true;
	s_CompassSkill = true;
	s_HealSkill = true;
}

void PlayerSkill::ImGuiDraw() {
}
