#pragma once
//�q�b�g�X�g�b�v�悤�Ȃ̂Ń��\�[�X�͗v��Ȃ�
class HitStop {
public:
	//�X�V�����̂�
	void Update();
public:
	//getter setter
	bool GetHitStop() { return  m_HitStop; }
	bool GetStopTimer() { return  m_StopTimer; }
	void SetStopTimer(int m_StopTimer) { this->m_StopTimer = m_StopTimer; }
private:
	bool m_HitStop = false;//�q�b�g�X�g�b�v
	int m_StopTimer = 0;//�q�b�g�X�g�b�v�̎���
};