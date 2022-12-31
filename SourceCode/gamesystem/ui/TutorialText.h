#pragma once
#include"IKESprite.h"
#include "IKETexture.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "VariableCommon.h"
#include <list> // ヘッダファイルインクルード
#include <array>
using namespace std;         //  名前空間指定
//チュートリアルのクラス(看板)
class TutorialText {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	TutorialText();
	//更新
	void Update(int TexNumber);
	//描画
	const void Draw();
	//当たり判定
	bool Collide(int TexNumber);
	//マップごとの初期化
	void InitBoard(int StageNumber,int TexNumber);
	//テクスチャの動き
	void MoveTex();
	//スプライトの出現
	void SpriteAppear(int TexNumber);
	
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//定数
	static const int Tutorial_Max = 5;//チュートリアルの数
	static const int TutorialAnime_Max = 2;//チュートリアルのアニメの数
public:
	//getter
	const XMFLOAT3& GetPosition() { return m_BoardPosition; }
	bool GetAlive() { return m_BoardAlive; }
	//setter
	void SetPosition(const XMFLOAT3& m_BoardPosition) { this->m_BoardPosition = m_BoardPosition; }
	void SetBoardAlive(bool m_BoardAlive) { this->m_BoardAlive = m_BoardAlive; }
private:
	//クラス
	unique_ptr<Player> player = nullptr;
	//unique_ptr<TextBoard> textboard = nullptr;
	//OBJ
	IKEModel* modelboard = nullptr;
	unique_ptr <IKEObject3d> objboard;
	//テクスチャやスプライト
	unique_ptr<IKETexture> tutorialPointTex;
	//array<array<unique_ptr<IKESprite>,Tutorial_Max>> TutorialSprite;
	unique_ptr<IKESprite> TutorialSprite[Tutorial_Max][TutorialAnime_Max];
	//その他変数
	XMFLOAT3 m_TexPosition;//テキストの位置
	XMFLOAT3 m_BoardPosition;//看板の位置
	//sin波に使うもの
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//看板があるか
	bool m_BoardAlive = true;
	//テキストが出るか
	bool m_TexAlive = false;
	int m_TextNumber = 0;
	//テキストの変数
	array<bool, Tutorial_Max> m_ReadTex;
	array<float, Tutorial_Max> m_Frame;
	array<bool, Tutorial_Max> m_InCount;
	array<bool, Tutorial_Max> m_OutCount;
	array<XMFLOAT2, Tutorial_Max> m_TexSize;
	
	int m_AnimeTimer = 0;
	int m_AnimeCount = 0;
};