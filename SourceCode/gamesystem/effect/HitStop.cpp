#include "HitStop.h"
#include "VariableCommon.h"
void HitStop::Update() {
	if (m_StopTimer > m_ResetNumber) {
		m_StopTimer--;
		if (m_StopTimer == 8) {
			m_HitStop = true;
		}
	}
	else {
		m_StopTimer = m_ResetNumber;
		m_HitStop = false;
	}
}