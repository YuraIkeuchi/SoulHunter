#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include <array>
using namespace std;         //  名前空間指定
//チュートリアルのクラス(看板)
class TutorialText {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	TutorialText();
	//更新
	void Update();
	//描画
	const void Draw();
	//当たり判定
	bool Collide();
	//マップごとの初期化
	void InitBoard(int StageNumber);
	//テクスチャの動き
	void MoveTex();
	//スプライトの出現
	void SpriteAppear();
	
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//定数
	static const int Tutorial_Max = 6;//チュートリアルの数

public:
	////getter
	//const XMFLOAT3& GetPosition() { return m_BoardPosition; }
	////setter
	//void SetPosition(const XMFLOAT3& m_BoardPosition) { this->m_BoardPosition = m_BoardPosition; }
private:
	//クラス
	unique_ptr<Player> player = nullptr;
	//OBJ
	IKEModel* modelboard = nullptr;
	array<unique_ptr <IKEObject3d>,Tutorial_Max> objboard;
	//テクスチャやスプライト
	//unique_ptr<IKESprite> TutorialSprite[Tutorial_Max][TutorialAnime_Max];
	//その他変数
	//XMFLOAT3 m_TexPosition;//テキストの位置
	array<XMFLOAT3,Tutorial_Max> m_BoardPosition;//看板の位置
	////看板があるか
	array<bool,Tutorial_Max> m_BoardAlive;
	////sin波に使うもの
	//float m_Angle = 0.0f;
	//float m_Angle2 = 0.0f;
	
	////テキストが出るか
	//bool m_TexAlive = false;
	//int m_TextNumber = 0;
	////テキストの変数
	//array<bool, Tutorial_Max> m_ReadTex;
	//array<float, Tutorial_Max> m_Frame;
	//array<bool, Tutorial_Max> m_InCount;
	//array<bool, Tutorial_Max> m_OutCount;
	//array<XMFLOAT2, Tutorial_Max> m_TexSize;
	//
	//int m_AnimeTimer = 0;
	//int m_AnimeCount = 0;


	enum TutorialType {
		Move,
		Rolling,
		Jump,
		Pause,
		Map,
		Attack,
	};
};