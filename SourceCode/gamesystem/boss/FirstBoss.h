#pragma once
#include "InterBoss.h"

class FirstBoss :public InterBoss {
public:
	FirstBoss();
	bool Initialize() override;//初期化
	void Spec() override;//ボスの行動
	void End() override;//ボス死亡
	void specialDraw() override;//このシーンのみの描画
	void specialDrawApp() override;//このシーンのみの描画
	void App() override;//ボス登場
	void DrawOutArea();//アウトラインの描画
	void NotAttack();//攻撃していない
	void BesideAttack();//横移動
	void StabbingAttack();//突き刺してくる攻撃
private:
	//アウトエリアの描画
	unique_ptr<IKETexture> OutAreatexture;
	XMFLOAT3 m_OutPos = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_OutColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT3 m_OutScale = { 0.5f,10.0f,1.0f };
	bool m_DrawArea = false;
	//アニメーション関係
	int m_Number = 0;
	bool m_AnimeLoop = false;
	int m_AnimeTimer = 0;
	int m_AnimeSpeed = 1;
	bool m_AnimationStop = false;
};