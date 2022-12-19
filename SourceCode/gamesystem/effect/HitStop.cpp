#include "HitStop.h"

void HitStop::Update() {
	if (m_StopTimer > 0) {
		m_StopTimer--;
		if (m_StopTimer == 8) {
			m_HitStop = true;
		}
	}
	else {
		m_StopTimer = 0;
		m_HitStop = false;
	}
}