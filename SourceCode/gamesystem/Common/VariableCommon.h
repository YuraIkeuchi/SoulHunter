#pragma once
//共通の変数はまとめる(主にマジックナンバー)
const float m_ColorMax = 1.0f;//透過度の最大
const float m_ColorMin = 0.0f;//透過度の最小

//フレームの最大と最小(イージングのためのやつ)
const float m_FrameMax = 1.0f;
const float m_FrameMin = 0.0f;

//ステージナンバー
enum StageNumber {
	Map1,
	Map2,
	Map3,
	Map4,
	Map5,
	Map6,
	BossMap,
	TutoRial,
};
//攻撃を食らった向き
enum HitDir {
	HitRight,
	HitLeft,
};
