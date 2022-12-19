#pragma once
#include"Player.h"
#include "PlayerSkill.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "AllArray.h"
#include "VariableCommon.h"
#include "IKESprite.h"
#include "IKETexture.h"
#include <list>
#include <array>
#include "ParticleTex.h"
#include "ChestEffect.h"
using namespace std;         //  名前空間指定
//宝箱用のクラス
class Chest {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
	//void SetTextBoard(TextBoard* textboard) { this->textboard.reset(textboard); }
	Chest();
	void Update();//更新
	const void Draw();//描画
	const void ExplainDraw();//説明分描画
	bool Collide();//当たり判定
	void OpenChest();//宝箱を開ける
	void InitChest(int StageNumber);//ステージごとの初期化
	void TexMove();//テクスチャの動き
	void Explain();//說明の基礎関数
	//各スキルの説明分
	bool CompassText();
	bool LibraText();
	bool DushText();
	bool HealText();
public:
	bool GetExplain() { return m_Explain; }
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter
	
private:
	//クラス
	unique_ptr<Player> player = nullptr;
	unique_ptr<PlayerSkill> playerskill = nullptr;
	array<unique_ptr<ParticleTex>, SkillMax> particletex;
	array<unique_ptr<ChestEffect>, SkillMax> chesteffect;
	//絶対に必要なOBJ
	//開いてる宝箱
	IKEModel* modelOpenChest = nullptr;
	array<unique_ptr <IKEObject3d>,SkillMax> objOpenChest;
	//閉じている宝箱
	IKEModel* modelCloseChest = nullptr;
	array<unique_ptr <IKEObject3d>,SkillMax> objCloseChest;
	//スプライト
	array<unique_ptr<IKESprite>, CompassExplain_Max> CompassExplain;
	array<unique_ptr<IKESprite>, LibraExplain_Max> LibraExplain;
	array<unique_ptr<IKESprite>, DushExplain_Max> DushExplain;
	array<unique_ptr<IKESprite>, HealExplain_Max> HealExplain;
	unique_ptr<IKESprite> ExplainBack;
	//テクスチャ
	unique_ptr<IKETexture> chestTex = nullptr;
	//パーティクル関係
	array<int,SkillMax> m_ParticleCount;//パーティクルの出る間隔
	array<XMFLOAT3, SkillMax> m_ParticlePos;//パーティクルの位置
	//その他変数
	//宝箱自体の変数
	array<XMFLOAT3, SkillMax> m_ChestPos;//宝箱の座標
	array<XMFLOAT4, SkillMax> m_CloseColor;//色
	array<XMFLOAT4, SkillMax> m_OpenColor;
	array<bool, SkillMax> m_Alive;//生存フラグ
	array<bool, SkillMax> m_Hit;//当たり判定
	array<int,SkillMax> m_ChestState;//宝箱の上歌い
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
	//どのテキストがテキストが出るか
	array<bool, SkillMax> m_ReadText;
	//宝箱を開けるテキストの変数関係
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition;
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
	};

	//マジックナンバー解消のための変数
	const float m_ChangeAlpha = 0.05f;//変化する透過度
	const float m_ChangeTexFrame = 0.01f;//テキストの透過度
	const int m_LibraTimerMax = 500;//ライブラのテキストのフレーム数
	const int m_SkillTimerMax = 600;//その他のテキストのフレーム数
};