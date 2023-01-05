#include "Shake.h"

void Shake::ShakePos(float& pos, const int ShakeMax, const int ShakeMin, const int TargetTimer, const int Division) {

	if (m_ShakeStart) {
		if (m_ShakeTimer < TargetTimer) {
			pos = (float)(rand() % ShakeMax - ShakeMin) / Division;
			m_ShakeTimer++;
		}
		else {
			m_ShakeStart = false;
			m_ShakeTimer = 0;
			pos = 0.0f;
		}
	}
}