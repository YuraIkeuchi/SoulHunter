#pragma once
#include"GamePlayer.h"
#include "IKESprite.h"
#include "IKETexture.h"
#include <array>
using namespace std;         //  名前空間指定
//宝箱用のクラス
class Chest {
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(GamePlayer* player) { this->player.reset(player); }
	Chest();
	void Update();//更新
	const void Draw();//描画
	const void SpriteDraw();//説明分描画
	const void MapDraw(int MapType, XMFLOAT4 MapColor,bool Pause,int PauseNumber);//ミニマップの描画
	bool Collide();//当たり判定
	void OpenChest();//宝箱を開ける
	void InitChest(int StageNumber);//ステージごとの初期化
	void TexMove();//テクスチャの動き
	void MapSet();//ミニマップの位置調整
	void Explain();//說明の基礎関数
	//各スキルの説明分
	bool CompassText();
	bool LibraText();
	bool DushText();
	bool HealText();
	bool JumpText();
public:
	bool GetExplain() { return m_Explain; }
private:
	//定数
	static const int Skill_Max = 5;//スキルの数
	static const int CompassExplain_Max = 4;//説明文の数(コンパス)
	static const int LibraExplain_Max = 3;//説明文の数(天秤座)
	static const int DushExplain_Max = 4;//説明文の数(ダッシュ)
	static const int HealExplain_Max = 4;//説明文の数(ヒール)
	static const int JumpExplain_Max = 3;//説明文の数(天秤座)
public:
	//getter
	
private:
	//クラス
	unique_ptr<GamePlayer> player = nullptr;
	array<unique_ptr<IKESprite>, Skill_Max> miniSkill;
	//絶対に必要なOBJ
	//開いてる宝箱
	IKEModel* modelOpenChest = nullptr;
	array<unique_ptr <IKEObject3d>,Skill_Max> objOpenChest;
	//閉じている宝箱
	IKEModel* modelCloseChest = nullptr;
	array<unique_ptr <IKEObject3d>,Skill_Max> objCloseChest;
	//スプライト
	array<unique_ptr<IKESprite>, CompassExplain_Max> CompassExplain;
	array<unique_ptr<IKESprite>, LibraExplain_Max> LibraExplain;
	array<unique_ptr<IKESprite>, DushExplain_Max> DushExplain;
	array<unique_ptr<IKESprite>, HealExplain_Max> HealExplain;
	array<unique_ptr<IKESprite>, JumpExplain_Max> JumpExplain;
	unique_ptr<IKESprite> ExplainBack;
	//テクスチャ
	unique_ptr<IKETexture> chestTex = nullptr;
	//パーティクル関係
	array<int,Skill_Max> m_ParticleCount;//パーティクルの出る間隔
	array<XMFLOAT3, Skill_Max> m_ParticlePos;//パーティクルの位置
	//その他変数
	//宝箱自体の変数
	array<XMFLOAT3, Skill_Max> m_ChestPos;//宝箱の座標
	array<XMFLOAT4, Skill_Max> m_CloseColor;//色
	array<XMFLOAT4, Skill_Max> m_OpenColor;
	array<bool, Skill_Max> m_Alive;//生存フラグ
	array<bool, Skill_Max> m_Hit;//当たり判定
	array<int,Skill_Max> m_ChestState;//宝箱の上歌い
	array<XMFLOAT2, Skill_Max> m_MapPos;//宝箱の座標(ミニマップ)
	//開けた後のスキルの説明関係の変数
	bool m_Explain = false;
	int m_ExplainTimer = 0;
	XMFLOAT4 m_BackColor = { 1.0f,1.0f,1.0f,0.0f };
	//コンパス
	int m_CompassTimer = 0;
	array<bool, CompassExplain_Max> m_CompassDraw;
	array<XMFLOAT4, CompassExplain_Max> m_CompassColor;
	array<XMFLOAT2, CompassExplain_Max> m_CompassTexPos;
	array<XMFLOAT2, CompassExplain_Max> m_AfterCompassTexPos;
	array<float, CompassExplain_Max> m_CompassTexframe;
	//ライブラ
	int m_LibraTimer = 0;
	array<bool, LibraExplain_Max> m_LibraDraw;
	array<XMFLOAT4, LibraExplain_Max> m_LibraColor;
	array<XMFLOAT2, LibraExplain_Max> m_LibraTexPos;
	array<XMFLOAT2, LibraExplain_Max> m_AfterLibraTexPos;
	array<float, LibraExplain_Max> m_LibraTexframe;
	//ダッシュ
	int m_DushTimer = 0;
	array<bool, DushExplain_Max> m_DushDraw;
	array<XMFLOAT4, DushExplain_Max> m_DushColor;
	array<XMFLOAT2, DushExplain_Max> m_DushTexPos;
	array<XMFLOAT2, DushExplain_Max> m_AfterDushTexPos;
	array<float, DushExplain_Max> m_DushTexframe;
	//ヒール
	int m_HealTimer = 0;
	array<bool, HealExplain_Max> m_HealDraw;
	array<XMFLOAT4, HealExplain_Max> m_HealColor;
	array<XMFLOAT2, HealExplain_Max> m_HealTexPos;
	array<XMFLOAT2, HealExplain_Max> m_AfterHealTexPos;
	array<float, HealExplain_Max> m_HealTexframe;
	//ジャンプ
	int m_JumpTimer = 0;
	array<bool, JumpExplain_Max> m_JumpDraw;
	array<XMFLOAT4, JumpExplain_Max> m_JumpColor;
	array<XMFLOAT2, JumpExplain_Max> m_JumpTexPos;
	array<XMFLOAT2, JumpExplain_Max> m_AfterJumpTexPos;
	array<float, JumpExplain_Max> m_JumpTexframe;
	//どのテキストがテキストが出るか
	array<bool, Skill_Max> m_ReadText;
	//宝箱を開けるテキストの変数関係
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition{};
	//宝箱の状態
	enum ChestState {
		Close,
		Open,
	};

	//スキルの中身
	enum InSkill {
		Compass,
		Libra,
		Dush,
		Heal,
		Jump,
	};

	//マジックナンバー解消のための変数
	const float m_ChangeAlpha = 0.05f;//変化する透過度
	const float m_ChangeTexFrame = 0.01f;//テキストの透過度
	const int m_LibraTimerMax = 150;//ライブラのテキストのフレーム数
	const int m_SkillTimerMax = 180;//その他のテキストのフレーム数
};