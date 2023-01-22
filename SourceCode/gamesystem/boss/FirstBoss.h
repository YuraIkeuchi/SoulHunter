#pragma once
#include "InterBoss.h"
#include "FireBall.h"
class FirstBoss :public InterBoss {
public:
	FirstBoss();
	bool Initialize() override;//初期化
	bool BattleInitialize() override;//初期化
	void Spec() override;//ボスの行動
	void Pause() override;//ポーズのとき
	void Dead() override;//ボス死亡
	void End() override;//ボスシーン終了
	void specialDraw(DirectXCommon* dxCommon) override;//このシーンのみの描画
	void specialDrawApp() override;//このシーンのみの描画
	void specialDrawEnd() override;//このシーンのみの描画
	void App() override;//ボス登場
	void DrawOutArea();//アウトラインの描画
	void NotAttack();//攻撃していない
	void BesideAttack();//横移動
	void StabbingAttack();//突き刺してくる攻撃
	void FireAttack();//炎の攻撃
	void SpecialAttack();//必殺アタック
	void StateManager();//HPに応じたステータス
	void FrameMove(XMFLOAT3 AfterPos, XMFLOAT3 AfterRot, float addframe,int TargetTimer);
	void FireBallArgment();//炎の弾の発生
	void AppBossMove(XMFLOAT3 AfterPos, float AddFrame);//ボス登場シーンのイージング関数(座標)
	void AppBossRot(XMFLOAT3 AfterRot, float AddFrame);//ボス登場シーンのイージング関数(回転)
private:
	//攻撃時のエフェクト発生条件
	bool m_FireBallArgment = false;
	std::vector<FireBall*> fireballs;
	//アウトエリアの描画
	unique_ptr<IKETexture> OutAreatexture;
	XMFLOAT3 m_OutPos = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_OutColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT3 m_OutScale = { 0.8f,40.0f,1.0f };
	bool m_DrawArea = false;
	//アニメーション関係
	int m_Number = 0;
	bool m_AnimeLoop = false;
	int m_AnimeTimer = 0;
	int m_AnimeSpeed = 1;
	bool m_AnimationStop = false;
	//登場シーン
	int m_AppTimer = 0;
	int m_AppNumber = 0;
	//終了シーン
	int m_EndTimer = 0;
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	enum AppNumber {
		NoMove,
		FirstMove,
		SecondMove,
		ThirdMove,
		FourthMove,
		FifthMove,
	};
	int m_RandFire = 0;
	int m_FireState = 0;
	enum FireState {
		Set0,
		Set1,
		Set2,
		Set3,
		ShotFire,
		EndFire,
	};

	//炎の攻撃の変数
	int m_FireTimer = 0;
	int m_FireCount = 0;
	float m_AddPowerY = -0.5f;
	//必殺技の変数
	double speedX = 0.0f;
	double speedY = 0.0f;
};