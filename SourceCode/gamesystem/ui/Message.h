#pragma once
#include"Player.h"
#include "PlayerSkill.h"
#include"Pause.h"
#include"MiniMap.h"
#include "MarkEffect.h"
#include "VariableCommon.h"
#include "IKESprite.h"
#include "IKETexture.h"
#include <list> // ヘッダファイルインクルード
#include <array>
using namespace std;         //  名前空間指定
//手紙などのクラス
class Message {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetPlayerSkill(PlayerSkill* playerskill) { this->playerskill.reset(playerskill); }
	void SetPause(Pause* pause) { this->pause.reset(pause); }
	void SetMiniMap(MiniMap* minimap) { this->minimap.reset(minimap); }
	Message();
	void Update();//更新
	void Finalize();//解放
	const void Draw();//描画
	const void ExplainDraw();//説明文の描画
	bool Collide();//当たり判定
	void InitMessage(int StageNumber);//マップごとの初期化
	void TexMove();//テキストの動き
	void Explain();//說明の基礎
	void ReadMessage();//メッセージを読む
	bool LetterExplainRead();////手紙のテキストの動き
public:
	bool GetExplain() { return m_Explain; }
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//定数
	static const int DushLetter_Max = 3;//アニメーションの数
public:
	//getter

private:
	//クラス
	unique_ptr<Player> player = nullptr;
	unique_ptr<PlayerSkill> playerskill = nullptr;
	unique_ptr<Pause> pause = nullptr;
	unique_ptr<MiniMap> minimap = nullptr;
	unique_ptr<MarkEffect> markEffect = nullptr;
	//スプライト
	unique_ptr<IKESprite> ExplainBack;
	array<unique_ptr<IKESprite>, DushLetter_Max> LetterExplain;
	//テクスチャ
	unique_ptr<IKETexture> LetterTex = nullptr;
	unique_ptr<IKETexture> ReadTex = nullptr;
	//その他変数
	//手紙の位置
	XMFLOAT3 m_LetterPos = { 0.0f,0.0f,0.0f };
	//ダッシュのテキスト
	int DushLetterTimer = 0;
	array<bool, DushLetter_Max> m_DushDraw;
	array<XMFLOAT4, DushLetter_Max> m_DushColor;
	array<XMFLOAT2, DushLetter_Max> m_DushTexPos;
	array<XMFLOAT2, DushLetter_Max> m_AfterDushTexPos;
	array<float, DushLetter_Max> m_DushTexframe;
	bool m_ReadText = false;//テキストを読んでいるか
	bool m_Alive = false;//生存フラグ
	bool m_Hit = false;//当たり判定
	bool m_OpenMap = false;
	//開けた後のスキルの説明関係の変数
	bool m_Explain = false;
	int m_ExplainTimer = 0;
	XMFLOAT4 m_BackColor = { 1.0f,1.0f,1.0f,0.0f };
	//宝箱を開けるテキストの変数関係
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	XMFLOAT3 m_TexPosition;
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

	//マジックナンバー解消のための変数
	const float m_ChangeAlpha = 0.05f;//変化する透過度
	const float m_ChangeTexFrame = 0.01f;//テキストの透過度
	const int m_SkillTimerMax = 500;//その他のテキストのフレーム数
};