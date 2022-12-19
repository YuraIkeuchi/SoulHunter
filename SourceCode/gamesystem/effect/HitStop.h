#pragma once
//ヒットストップようなのでリソースは要らない
class HitStop {
public:
	//更新処理のみ
	void Update();
public:
	//getter setter
	bool GetHitStop() { return  m_HitStop; }
	bool GetStopTimer() { return  m_StopTimer; }
	void SetStopTimer(int m_StopTimer) { this->m_StopTimer = m_StopTimer; }
private:
	bool m_HitStop = false;//ヒットストップ
	int m_StopTimer = 0;//ヒットストップの時間
};