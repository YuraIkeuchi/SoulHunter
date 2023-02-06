#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include <array>
#include "CollisionPrimitive.h"
#include "PlayerEffect.h"
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
	const void SpriteDraw();//説明分描画
	void ImGuiDraw();
	//当たり判定
	bool Collide();
	//マップごとの初期化
	void InitBoard(int StageNumber);
	//チュートリアルの状況
	void Mission();
	//看板の動き
	void MoveBoard();
	//スプライトの動き
	void ChangeSprite();
	//岩と剣の当たり判定
	bool RockCollide();
	//岩の状態
	void RockState();
	//ロードゲーム時の場合
	void LoadGame();
	//パーティクル
	void BirthParticle();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//定数
	static const int Tutorial_Max = 7;//チュートリアルの数

public:

private:
	//クラス
	vector<PlayerEffect*> effects;
	unique_ptr<Player> player = nullptr;
	//OBB
	OBB OBB1 = {};
	OBB OBB2 = {};
	//OBJ
	IKEModel* modelboard = nullptr;
	array<unique_ptr <IKEObject3d>,Tutorial_Max> objboard;

	IKEModel* modelblock = nullptr;
	unique_ptr<IKEObject3d> objblock;
	XMFLOAT3 m_blockPosition = {83.0f,-280.0f,5.0f};
	XMFLOAT3 m_blockScale = {1.0f,1.5f,2.5f};
	XMFLOAT4 m_blockColor = {1.0f,1.0f,1.0f,1.0f};
	//テクスチャやスプライト
	array<unique_ptr<IKESprite>,Tutorial_Max> TutorialSprite;
	//その他変数
	//XMFLOAT3 m_TexPosition;//テキストの位置
	array<XMFLOAT3,Tutorial_Max> m_BoardPosition;//看板の位置
	////看板があるか
	array<bool,Tutorial_Max> m_BoardAlive;
	array<bool, Tutorial_Max> m_BoardDraw;
	array<int, Tutorial_Max> m_ParticleCount;
	//チュートリアルの進行状況
	int m_TutorialMission = 0;
	//看板の動き方
	array<int, Tutorial_Max> m_BoardState;
	//看板の位置(Y軸のみ)
	array<float, Tutorial_Max> m_AfterPosY;
	//フレーム
	array<float, Tutorial_Max> m_Frame;
	////テキストの変数
	array<int, Tutorial_Max> m_SpriteState;
	array<XMFLOAT2, Tutorial_Max> m_TexSize;
	array<XMFLOAT2, Tutorial_Max> m_AfterTexSize;

	bool m_Damage = false;
	int m_DamageTimer = 0;
	int m_ClearCount = 0;
	enum TutorialType {
		Move,
		CameraMove,
		Jump,
		Rolling,
		Pause,
		Map,
		Attack,
	};

	enum TutorialMission {
		FirstMission,
		SecondMission,
		ThirdMission,
		FinishMission,
	};

	enum BoardState {
		NoMove,
		UpBoard,
		DownBoard
	};

	enum SpriteState {
		NoSize,
		WideSprite,
		ShrinkSprite
	};

	//チュートリアルの状況
	int m_MoveCount = 0;

	//岩を叩いた回数
	int m_AttackCount = 0;
};