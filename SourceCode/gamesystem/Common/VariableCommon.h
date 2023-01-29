#pragma once
//共通の変数はまとめる(主にマジックナンバー)
const float m_ColorMax = 1.0f;//透過度の最大
const float m_ColorMin = 0.0f;//透過度の最小

//フレームの最大と最小(イージングのためのやつ)
const float m_FrameMax = 1.0f;
const float m_FrameMin = 0.0f;
//サイズ切り取りサイズ
//フルスクリーン
const int FullWidth_Cut = 1280;
const int FullHeight_Cut = 720;
//ロード画面
const int LoadWidth_Cut = 712;
const int LoadHeight_Cut = 128;
//説明画面
const int ExplainWidth_Cut = 1028;
const int ExplainHeight_Cut = 128;
//セーブ画面
const int SaveWidth_Cut = 512;
const int SaveHeight_Cut = 64;
//チュートリアル画面
const int TutorialWidth_Cut = 256;
const int TutorialHeight_Cut = 128;
//タイトルやオプションのパーツ画面
const int PartsWidth_Cut = 640;
const int PartsHeight_Cut = 128;

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
	NoHit,
	HitRight,
	HitLeft,
	HitUp,
	HitDown,
};
//ブレンドタイプ
enum BlendType
{
	AlphaBlendType,
	AddBlendType,
	SubBlendType,
};


//敵の種類
enum EnemyType {
	Normal,
	Thorn,
	Bound,
	Bird,
	Follow,
};

//背景OBJの種類
enum BackObjType {
	Rock,
	Box,
	Torch,
};

